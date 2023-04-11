#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <random>
#include <vector>
#include <algorithm>
#include <complex>
#include <omp.h>

#include <fftw3.h>

#include "iubench.h"

template<typename T>
inline void copy_mt(T *dst, const T *src, int64_t m, int64_t n) {
    #pragma omp parallel for
    for (int64_t mm = 0; mm < m; ++mm) {
        auto __d = dst + mm * n;
        auto __s = src + mm * n;
        for (int64_t nn = 0; nn < n; ++nn) {
            __d[nn] = __s[nn];
        }
    }
}

template<typename T>
inline void copy(T *dst, const T *src, int64_t m, int64_t n) {
    #pragma omp parallel for
    for (int64_t mm = 0; mm < m; ++mm) {
        auto __d = dst + mm * n;
        auto __s = src + mm * n;
        for (int64_t nn = 0; nn < n; ++nn) {
            __d[nn] = __s[nn];
        }
    }
}

template<typename T>
inline void trans_mt(T *dst, const T *src, int64_t m, int64_t n) {
    #pragma omp parallel for
    for (int64_t nn = 0; nn < n; ++nn) {
        auto __d = dst + nn * m;
        auto __s = src + nn;
        for (int64_t mm = 0; mm < m; ++mm) {
            __d[mm] = __s[mm * n];
        }
    }
}

template<typename T>
inline void trans(T *dst, const T *src, int64_t m, int64_t n) {
    for (int64_t nn = 0; nn < n; ++nn) {
        auto __d = dst + nn * m;
        auto __s = src + nn;
        for (int64_t mm = 0; mm < m; ++mm) {
            __d[mm] = __s[mm * n];
        }
    }
}

struct BallFFTParam {
    int ns;
    int nz;
    int nx;
    int ny;
    int nplane;
    int lixy;
    int rixy;
};

class BallFFT3DForwardLatency : public IUbench {
public:
    BallFFT3DForwardLatency(const BallFFTParam &param) : p_(param) {
        instruction_count_ = 1;
        ops_count_ = 1;

        p_.nplane = p_.nz;

        auto max_grids = std::max((int64_t)p_.ns * p_.nz, (int64_t)p_.nx * p_.ny * p_.nplane);

        i_ = new std::complex<double>[max_grids];
        o_ = new std::complex<double>[max_grids];

        r_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);

        auto dis = std::uniform_real_distribution<double>(-1, 1);
        std::default_random_engine eng;

        for (int64_t i = 0; i < (int64_t)p_.nx * p_.ny * p_.nplane; ++i) {
            i_[i].real(dis(eng));
            i_[i].imag(dis(eng));
        }

        plan_ = fftw_plan_dft_3d(
            p_.nx, p_.ny, p_.nz,
            (fftw_complex *)r_,
            (fftw_complex *)r_,
            FFTW_FORWARD,  FFTW_MEASURE);
    }

    virtual ~BallFFT3DForwardLatency() {
        delete [] i_;
        delete [] o_;

        fftw_free(r_);
        fftw_destroy_plan(plan_);
    }

private:
    BallFFTParam p_;
    std::complex<double> *i_ = nullptr;
    std::complex<double> *o_ = nullptr;
    std::complex<double> *r_ = nullptr;
    fftw_plan plan_;

    void BenchImpl() override {
        copy_mt(r_, i_, (int64_t)p_.nx * p_.ny * p_.nplane, 1);
        fftw_execute_dft(plan_, (fftw_complex *)r_, (fftw_complex *)r_);
        copy_mt(o_, r_, (int64_t)p_.ns * p_.nz, 1);
    }
};

class BallFFT3DBackwardLatency : public IUbench {
public:
    BallFFT3DBackwardLatency(const BallFFTParam &param) : p_(param) {
        instruction_count_ = 1;
        ops_count_ = 1;

        p_.nplane = p_.nz;

        auto max_grids = std::max((int64_t)p_.ns * p_.nz, (int64_t)p_.nx * p_.ny * p_.nplane);

        i_ = new std::complex<double>[max_grids];
        o_ = new std::complex<double>[max_grids];

        r_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);

        auto dis = std::uniform_real_distribution<double>(-1, 1);
        std::default_random_engine eng;

        for (int64_t i = 0; i < (int64_t)p_.ns * p_.nz; ++i) {
            i_[i].real(dis(eng));
            i_[i].imag(dis(eng));
        }

        plan_ = fftw_plan_dft_3d(
            p_.nx, p_.ny, p_.nz,
            (fftw_complex *)r_,
            (fftw_complex *)r_,
            FFTW_BACKWARD,  FFTW_MEASURE);
    }

    virtual ~BallFFT3DBackwardLatency() {
        delete [] i_;
        delete [] o_;

        fftw_free(r_);
        fftw_destroy_plan(plan_);
    }

private:
    BallFFTParam p_;
    std::complex<double> *i_ = nullptr;
    std::complex<double> *o_ = nullptr;
    std::complex<double> *r_ = nullptr;
    fftw_plan plan_;

    void BenchImpl() override {
        copy_mt(r_, i_,(int64_t)p_.ns * p_.nz, 1);
        fftw_execute_dft(plan_, (fftw_complex *)r_, (fftw_complex *)r_);
        copy_mt(o_, r_, (int64_t)p_.nx * p_.ny * p_.nplane, 1);
    }
};

class BallFFTForwardLatency : public IUbench {
public:
    BallFFTForwardLatency(const BallFFTParam &param) : p_(param) {
        instruction_count_ = 1;
        ops_count_ = 1;

        p_.nplane = p_.nz;

        auto max_grids = std::max((int64_t)p_.ns * p_.nz, (int64_t)p_.nx * p_.ny * p_.nplane);

        i_ = new std::complex<double>[max_grids];
        o_ = new std::complex<double>[max_grids];

        g_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);
        r_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);

        auto dis = std::uniform_real_distribution<double>(-1, 1);
        std::default_random_engine eng;

        for (int64_t i = 0; i < (int64_t)p_.nx * p_.ny * p_.nplane; ++i) {
            i_[i].real(dis(eng));
            i_[i].imag(dis(eng));
        }

        plan_z_ = fftw_plan_many_dft(
            1, &p_.nz, p_.ns,
            (fftw_complex *)g_, &p_.nz, 1, p_.nz,
            (fftw_complex *)g_, &p_.nz, 1, p_.nz,
            FFTW_FORWARD,  FFTW_MEASURE);

        plan_y_ = fftw_plan_many_dft(
            1, &p_.ny, p_.nplane,
            (fftw_complex *)r_, nullptr, p_.nplane, 1,
            (fftw_complex *)r_, nullptr, p_.nplane, 1,
            FFTW_FORWARD,  FFTW_MEASURE);

        plan_x_ = fftw_plan_many_dft(
            1, &p_.nx, p_.nplane * p_.ny,
            (fftw_complex *)r_, nullptr, p_.nplane * p_.ny, 1,
            (fftw_complex *)r_, nullptr, p_.nplane * p_.ny, 1,
            FFTW_FORWARD,  FFTW_MEASURE);
    }

    virtual ~BallFFTForwardLatency() {
        delete [] i_;
        delete [] o_;

        fftw_free(g_);
        fftw_free(r_);
        fftw_destroy_plan(plan_x_);
        fftw_destroy_plan(plan_y_);
        fftw_destroy_plan(plan_z_);
    }

private:
    BallFFTParam p_;
    std::complex<double> *i_ = nullptr;
    std::complex<double> *o_ = nullptr;
    std::complex<double> *g_ = nullptr;
    std::complex<double> *r_ = nullptr;
    fftw_plan plan_x_;
    fftw_plan plan_y_;
    fftw_plan plan_z_;

    void BenchImpl() override {
        copy_mt(r_, i_, (int64_t)p_.nx * p_.ny * p_.nplane, 1);

        fftw_execute_dft(plan_x_, (fftw_complex *)r_, (fftw_complex *)r_);

        for (int i = 0; i < p_.nx; ++i) {
            fftw_execute_dft(plan_y_, (fftw_complex *)&r_[i * p_.nplane * p_.ny], (fftw_complex *)&r_[i * p_.nplane * p_.ny]);
        }

        copy_mt(g_, r_, (int64_t)p_.ns, p_.nz);

        fftw_execute_dft(plan_z_, (fftw_complex *)g_, (fftw_complex *)g_);

        copy_mt(o_, g_, (int64_t)p_.ns * p_.nz, 1);
    }
};

class OptBallFFTForwardLatency : public IUbench {
public:
    OptBallFFTForwardLatency(const BallFFTParam &param) : p_(param) {
        instruction_count_ = 1;
        ops_count_ = 1;

        p_.nplane = p_.nz;

        auto max_grids = std::max((int64_t)p_.ns * p_.nz, (int64_t)p_.nx * p_.ny * p_.nplane);

        i_ = new std::complex<double>[max_grids];
        o_ = new std::complex<double>[max_grids];

        g_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);
        rx_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);
        ry_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);

        auto dis = std::uniform_real_distribution<double>(-1, 1);
        std::default_random_engine eng;

        for (int64_t i = 0; i < (int64_t)p_.nx * p_.ny * p_.nplane; ++i) {
            i_[i].real(dis(eng));
            i_[i].imag(dis(eng));
        }

        plan_z_ = fftw_plan_many_dft(
            1, &p_.nz, p_.ns,
            (fftw_complex *)g_, &p_.nz, 1, p_.nz,
            (fftw_complex *)g_, &p_.nz, 1, p_.nz,
            FFTW_FORWARD,  FFTW_MEASURE);

        plan_y_ = fftw_plan_many_dft(
            1, &p_.ny, p_.nplane * p_.nx,
            (fftw_complex *)rx_, nullptr, p_.nplane * p_.nx, 1,
            (fftw_complex *)ry_, nullptr, 1, p_.ny,
            FFTW_FORWARD,  FFTW_MEASURE);

        plan_x_ = fftw_plan_many_dft(
            1, &p_.nx, p_.ny * p_.nplane,
            (fftw_complex *)rx_, nullptr, 1, p_.nx,
            (fftw_complex *)rx_, nullptr, 1, p_.nx,
            FFTW_FORWARD,  FFTW_MEASURE);
    }

    virtual ~OptBallFFTForwardLatency() {
        delete [] i_;
        delete [] o_;

        fftw_free(g_);
        fftw_free(rx_);
        fftw_free(ry_);
        fftw_destroy_plan(plan_x_);
        fftw_destroy_plan(plan_y_);
        fftw_destroy_plan(plan_z_);
    }

private:
    BallFFTParam p_;
    std::complex<double> *i_ = nullptr;
    std::complex<double> *o_ = nullptr;
    std::complex<double> *g_ = nullptr;
    std::complex<double> *rx_ = nullptr;
    std::complex<double> *ry_ = nullptr;
    fftw_plan plan_x_;
    fftw_plan plan_y_;
    fftw_plan plan_z_;

    void BenchImpl() override {
        trans_mt(rx_, i_, p_.nx, (int64_t)p_.ny * p_.nplane);
        fftw_execute_dft(plan_x_, (fftw_complex *)rx_, (fftw_complex *)rx_);
        fftw_execute_dft(plan_y_, (fftw_complex *)rx_, (fftw_complex *)ry_);
        trans_mt(g_, ry_, p_.nplane, (int64_t)p_.nx * p_.ny);
        fftw_execute_dft(plan_z_, (fftw_complex *)g_, (fftw_complex *)g_);
        copy_mt(o_, g_, (int64_t)p_.ns * p_.nz, 1);
    }
};

class SimMPIBallFFTForwardLatency : public IUbench {
public:
    SimMPIBallFFTForwardLatency(const BallFFTParam &param) : p_(param) {
        instruction_count_ = 1;
        ops_count_ = 1;

        p_.ns = (p_.ns + omp_get_max_threads() - 1) / omp_get_max_threads();
        p_.nplane = (p_.nz + omp_get_max_threads() - 1) / omp_get_max_threads();

        pp_ = new ProcParam[omp_get_max_threads()];

        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            auto &i_ = pp_[tid].i;
            auto &o_ = pp_[tid].o;
            auto &g_ = pp_[tid].g;
            auto &r_ = pp_[tid].r;

            auto max_grids = std::max((int64_t)p_.ns * p_.nz, (int64_t)p_.nx * p_.ny * p_.nplane);

            i_ = new std::complex<double>[max_grids];
            o_ = new std::complex<double>[max_grids];

            g_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);
            r_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);

            auto dis = std::uniform_real_distribution<double>(-1, 1);
            std::default_random_engine eng;

            for (int64_t i = 0; i < (int64_t)p_.nx * p_.ny * p_.nplane; ++i) {
                i_[i].real(dis(eng));
                i_[i].imag(dis(eng));
            }
        }

        plan_z_ = fftw_plan_many_dft(
            1, &p_.nz, p_.ns,
            (fftw_complex *)pp_->g, &p_.nz, 1, p_.nz,
            (fftw_complex *)pp_->g, &p_.nz, 1, p_.nz,
            FFTW_FORWARD,  FFTW_MEASURE);

        plan_y_ = fftw_plan_many_dft(
            1, &p_.ny, p_.nplane,
            (fftw_complex *)pp_->r, nullptr, p_.nplane, 1,
            (fftw_complex *)pp_->r, nullptr, p_.nplane, 1,
            FFTW_FORWARD,  FFTW_MEASURE);

        plan_x_ = fftw_plan_many_dft(
            1, &p_.nx, p_.nplane * p_.ny,
            (fftw_complex *)pp_->r, nullptr, p_.nplane * p_.ny, 1,
            (fftw_complex *)pp_->r, nullptr, p_.nplane * p_.ny, 1,
            FFTW_FORWARD,  FFTW_MEASURE);
    }

    virtual ~SimMPIBallFFTForwardLatency() {
        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            auto &i_ = pp_[tid].i;
            auto &o_ = pp_[tid].o;
            auto &g_ = pp_[tid].g;
            auto &r_ = pp_[tid].r;
            delete [] i_;
            delete [] o_;
            fftw_free(g_);
            fftw_free(r_);
        }
        fftw_destroy_plan(plan_x_);
        fftw_destroy_plan(plan_y_);
        fftw_destroy_plan(plan_z_);

        delete [] pp_;
    }

private:
    struct ProcParam {
        std::complex<double> *i = nullptr;
        std::complex<double> *o = nullptr;
        std::complex<double> *g = nullptr;
        std::complex<double> *r = nullptr;
    };

    BallFFTParam p_;
    fftw_plan plan_x_;
    fftw_plan plan_y_;
    fftw_plan plan_z_;
    ProcParam *pp_;

    void BenchImpl() override {
        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            auto &i_ = pp_[tid].i;
            auto &o_ = pp_[tid].o;
            auto &g_ = pp_[tid].g;
            auto &r_ = pp_[tid].r;

            copy(r_, i_, (int64_t)p_.nx * p_.ny * p_.nplane, 1);

            fftw_execute_dft(plan_x_, (fftw_complex *)r_, (fftw_complex *)r_);

            for (int i = 0; i < p_.nx; ++i) {
                fftw_execute_dft(plan_y_, (fftw_complex *)&r_[i * p_.nplane * p_.ny], (fftw_complex *)&r_[i * p_.nplane * p_.ny]);
            }

            copy(g_, r_, (int64_t)p_.ns, p_.nz);

            fftw_execute_dft(plan_z_, (fftw_complex *)g_, (fftw_complex *)g_);

            copy(o_, g_, (int64_t)p_.ns * p_.nz, 1);
        }
    }
};

class OptSimMPIBallFFTForwardLatency : public IUbench {
public:
    OptSimMPIBallFFTForwardLatency(const BallFFTParam &param) : p_(param) {
        instruction_count_ = 1;
        ops_count_ = 1;

        p_.ns = (p_.ns + omp_get_max_threads() - 1) / omp_get_max_threads();
        p_.nplane = (p_.nz + omp_get_max_threads() - 1) / omp_get_max_threads();

        pp_ = new ProcParam[omp_get_max_threads()];

        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            auto &i_ = pp_[tid].i;
            auto &o_ = pp_[tid].o;
            auto &g_ = pp_[tid].g;
            auto &rx_ = pp_[tid].rx;
            auto &ry_ = pp_[tid].ry;

            auto max_grids = std::max((int64_t)p_.ns * p_.nz, (int64_t)p_.nx * p_.ny * p_.nplane);

            i_ = new std::complex<double>[max_grids];
            o_ = new std::complex<double>[max_grids];

            g_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);
            rx_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);
            ry_ = (std::complex<double>*)fftw_malloc(sizeof(fftw_complex) * max_grids);

            auto dis = std::uniform_real_distribution<double>(-1, 1);
            std::default_random_engine eng;

            for (int64_t i = 0; i < (int64_t)p_.nx * p_.ny * p_.nplane; ++i) {
                i_[i].real(dis(eng));
                i_[i].imag(dis(eng));
            }
        }

        plan_z_ = fftw_plan_many_dft(
            1, &p_.nz, p_.ns,
            (fftw_complex *)pp_->g, &p_.nz, 1, p_.nz,
            (fftw_complex *)pp_->g, &p_.nz, 1, p_.nz,
            FFTW_FORWARD,  FFTW_MEASURE);

        plan_y_ = fftw_plan_many_dft(
            1, &p_.ny, p_.nplane * p_.nx,
            (fftw_complex *)pp_->rx, nullptr, p_.nplane * p_.nx, 1,
            (fftw_complex *)pp_->ry, nullptr, 1, p_.ny,
            FFTW_FORWARD,  FFTW_MEASURE);

        plan_x_ = fftw_plan_many_dft(
            1, &p_.nx, p_.ny * p_.nplane,
            (fftw_complex *)pp_->rx, nullptr, 1, p_.nx,
            (fftw_complex *)pp_->rx, nullptr, 1, p_.nx,
            FFTW_FORWARD,  FFTW_MEASURE);
    }

    virtual ~OptSimMPIBallFFTForwardLatency() {
        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            auto &i_ = pp_[tid].i;
            auto &o_ = pp_[tid].o;
            auto &g_ = pp_[tid].g;
            auto &rx_ = pp_[tid].rx;
            auto &ry_ = pp_[tid].ry;
            delete [] i_;
            delete [] o_;
            fftw_free(g_);
            fftw_free(rx_);
            fftw_free(ry_);
        }
        fftw_destroy_plan(plan_x_);
        fftw_destroy_plan(plan_y_);
        fftw_destroy_plan(plan_z_);

        delete [] pp_;
    }

private:
    struct ProcParam {
        std::complex<double> *i = nullptr;
        std::complex<double> *o = nullptr;
        std::complex<double> *g = nullptr;
        std::complex<double> *rx = nullptr;
        std::complex<double> *ry = nullptr;
    };

    BallFFTParam p_;
    fftw_plan plan_x_;
    fftw_plan plan_y_;
    fftw_plan plan_z_;
    ProcParam *pp_;

    void BenchImpl() override {
        #pragma omp parallel
        {
            int tid = omp_get_thread_num();
            auto &i_ = pp_[tid].i;
            auto &o_ = pp_[tid].o;
            auto &g_ = pp_[tid].g;
            auto &rx_ = pp_[tid].rx;
            auto &ry_ = pp_[tid].ry;
            trans(rx_, i_, p_.nx, (int64_t)p_.ny * p_.nplane);
            fftw_execute_dft(plan_x_, (fftw_complex *)rx_, (fftw_complex *)rx_);
            fftw_execute_dft(plan_y_, (fftw_complex *)rx_, (fftw_complex *)ry_);
            trans(g_, ry_, p_.nplane, (int64_t)p_.nx * p_.ny);
            fftw_execute_dft(plan_z_, (fftw_complex *)g_, (fftw_complex *)g_);
            copy(o_, g_, (int64_t)p_.ns * p_.nz, 1);
        }
    }
};

int main(int argc, const char **argv) {
    BallFFTParam param_list[] {
        {437, 100, 45, 45, 0, 11, 34},
        {1757, 108, 48, 48, 0, 23, 25},
        {91693, 192, 375, 375, 0, 183, 192},
    };

    double ms = 1000;
    int64_t warm = 10;
    int64_t iter = 50;
    int64_t run = 0;

    fprintf(stderr, "SimMPI Forward:\n");
    for (auto p : param_list) {
        SimMPIBallFFTForwardLatency t(p); 
        run = t.BenchLimitTime(warm, iter, ms);
        fprintf(stderr,
            "Ns=%d, Nz=%d, Nx=%d, Ny=%d, Lat: %.3f ms, x1.2: %.3f ms\n",
            p.ns, p.nz, p.nx, p.ny, t.GetNs() / 1e6 / run, t.GetNs() / 1e6 / run * 1.2);
    }

    fprintf(stderr, "Optimize(?) SimMPI Forward:\n");
    for (auto p : param_list) {
        OptSimMPIBallFFTForwardLatency t(p);
        run = t.BenchLimitTime(warm, iter, ms);
        fprintf(stderr,
            "Ns=%d, Nz=%d, Nx=%d, Ny=%d, Lat: %.3f ms, x1.2: %.3f ms\n",
            p.ns, p.nz, p.nx, p.ny, t.GetNs() / 1e6 / run, t.GetNs() / 1e6 / run * 1.2);
    }

    if (omp_get_max_threads() > 1) {
        fftw_init_threads();
        fftw_plan_with_nthreads(omp_get_max_threads());
    }

    fprintf(stderr, "OpenMP Forward:\n");
    for (auto p : param_list) {
        BallFFTForwardLatency t(p);
        run = t.BenchLimitTime(warm, iter, ms);
        fprintf(stderr,
            "Ns=%d, Nz=%d, Nx=%d, Ny=%d, Lat: %.3f ms\n",
            p.ns, p.nz, p.nx, p.ny, t.GetNs() / 1e6 / run);
    }

    fprintf(stderr, "Optimize OpenMP Forward:\n");
    for (auto p : param_list) {
        OptBallFFTForwardLatency t(p);
        run = t.BenchLimitTime(warm, iter, ms);
        fprintf(stderr,
            "Ns=%d, Nz=%d, Nx=%d, Ny=%d, Lat: %.3f ms\n",
            p.ns, p.nz, p.nx, p.ny, t.GetNs() / 1e6 / run);
    }

    fprintf(stderr, "3D OpenMP Forward:\n");
    for (auto p : param_list) {
        BallFFT3DForwardLatency t(p);
        run = t.BenchLimitTime(warm, iter, ms);
        fprintf(stderr,
            "Ns=%d, Nz=%d, Nx=%d, Ny=%d, Lat: %.3f ms\n",
            p.ns, p.nz, p.nx, p.ny, t.GetNs() / 1e6 / run);
    }

    fprintf(stderr, "3D OpenMP Backward:\n");
    for (auto p : param_list) {
        BallFFT3DBackwardLatency t(p);
        run = t.BenchLimitTime(warm, iter, ms);
        fprintf(stderr,
            "Ns=%d, Nz=%d, Nx=%d, Ny=%d, Lat: %.3f ms\n",
            p.ns, p.nz, p.nx, p.ny, t.GetNs() / 1e6 / run);
    }

    if (omp_get_max_threads() > 1) {
        fftw_cleanup_threads();
    }

    return 0;
}
