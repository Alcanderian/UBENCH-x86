#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <omp.h>
#include <thread>

#include "iubench.h"

#define XMM_INIT() \
    "pxor %%xmm0, %%xmm0\n"\
    "pxor %%xmm1, %%xmm1\n"\
    "pxor %%xmm2, %%xmm2\n"\
    "pxor %%xmm3, %%xmm3\n"\
    "pxor %%xmm4, %%xmm4\n"\
    "pxor %%xmm5, %%xmm5\n"\
    "pxor %%xmm6, %%xmm6\n"\
    "pxor %%xmm7, %%xmm7\n"\
    "pxor %%xmm8, %%xmm8\n"\
    "pxor %%xmm9, %%xmm9\n"\
    "pxor %%xmm10, %%xmm10\n"\
    "pxor %%xmm11, %%xmm11\n"\
    "pxor %%xmm12, %%xmm12\n"\
    "pxor %%xmm13, %%xmm13\n"\
    "pxor %%xmm14, %%xmm14\n"\
    "pxor %%xmm15, %%xmm15\n"

class OMPMaxThreadPerf : public IUbench {
public:
    OMPMaxThreadPerf() {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 4;
    };
    double CalOpsPerNs() override {
        return ((double)ops_count_ * iter_) / ns_ * omp_get_max_threads();
    }
private:
    void BenchImpl() override {
        #pragma omp parallel
        {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm1, %%xmm1\n"
            "mulps %%xmm2, %%xmm2\n"
            "mulps %%xmm3, %%xmm3\n"

            "mulps %%xmm4, %%xmm4\n"
            "mulps %%xmm5, %%xmm5\n"
            "mulps %%xmm6, %%xmm6\n"
            "mulps %%xmm7, %%xmm7\n"

            "mulps %%xmm8, %%xmm8\n"
            "mulps %%xmm9, %%xmm9\n"
            "mulps %%xmm10, %%xmm10\n"
            "mulps %%xmm11, %%xmm11\n"

            "mulps %%xmm12, %%xmm12\n"
            "mulps %%xmm13, %%xmm13\n"
            "mulps %%xmm14, %%xmm14\n"
            "mulps %%xmm15, %%xmm15\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
        }
    };
};

template<int M>
class OMPMThreadPerf : public IUbench {
public:
    OMPMThreadPerf() {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 4;
    };
    double CalOpsPerNs() override {
        return ((double)ops_count_ * iter_) / ns_ * M;
    }
private:
    void BenchImpl() override {
        #pragma omp parallel num_threads(M)
        {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm1, %%xmm1\n"
            "mulps %%xmm2, %%xmm2\n"
            "mulps %%xmm3, %%xmm3\n"

            "mulps %%xmm4, %%xmm4\n"
            "mulps %%xmm5, %%xmm5\n"
            "mulps %%xmm6, %%xmm6\n"
            "mulps %%xmm7, %%xmm7\n"

            "mulps %%xmm8, %%xmm8\n"
            "mulps %%xmm9, %%xmm9\n"
            "mulps %%xmm10, %%xmm10\n"
            "mulps %%xmm11, %%xmm11\n"

            "mulps %%xmm12, %%xmm12\n"
            "mulps %%xmm13, %%xmm13\n"
            "mulps %%xmm14, %%xmm14\n"
            "mulps %%xmm15, %%xmm15\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
        }
    };
};

template<int N>
class STDNThreadPerf : public IUbench {
public:
    STDNThreadPerf() {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 4;
    };
    double CalOpsPerNs() override {
        return ((double)ops_count_ * iter_) / ns_ * N;
    }
private:
    void BenchImpl() override {
        auto kernel = [this]() {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm1, %%xmm1\n"
            "mulps %%xmm2, %%xmm2\n"
            "mulps %%xmm3, %%xmm3\n"

            "mulps %%xmm4, %%xmm4\n"
            "mulps %%xmm5, %%xmm5\n"
            "mulps %%xmm6, %%xmm6\n"
            "mulps %%xmm7, %%xmm7\n"

            "mulps %%xmm8, %%xmm8\n"
            "mulps %%xmm9, %%xmm9\n"
            "mulps %%xmm10, %%xmm10\n"
            "mulps %%xmm11, %%xmm11\n"

            "mulps %%xmm12, %%xmm12\n"
            "mulps %%xmm13, %%xmm13\n"
            "mulps %%xmm14, %%xmm14\n"
            "mulps %%xmm15, %%xmm15\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
        };

        std::thread thrs[N];
        for (int i = 0; i < N; ++i) {
            thrs[i] = std::thread(kernel);
        }
        for (int i = 0; i < N; ++i) {
            thrs[i].join();
        }
    };
};

template<int N>
class STDOMPCombineNxMaxThreadPerf : public IUbench {
public:
    STDOMPCombineNxMaxThreadPerf() {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 4;
    };
    double CalOpsPerNs() override {
        return ((double)ops_count_ * iter_) / ns_ * N * omp_get_max_threads();
    }
private:
    void BenchImpl() override {
        auto kernel = [this]() {
        #pragma omp parallel
        {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm1, %%xmm1\n"
            "mulps %%xmm2, %%xmm2\n"
            "mulps %%xmm3, %%xmm3\n"

            "mulps %%xmm4, %%xmm4\n"
            "mulps %%xmm5, %%xmm5\n"
            "mulps %%xmm6, %%xmm6\n"
            "mulps %%xmm7, %%xmm7\n"

            "mulps %%xmm8, %%xmm8\n"
            "mulps %%xmm9, %%xmm9\n"
            "mulps %%xmm10, %%xmm10\n"
            "mulps %%xmm11, %%xmm11\n"

            "mulps %%xmm12, %%xmm12\n"
            "mulps %%xmm13, %%xmm13\n"
            "mulps %%xmm14, %%xmm14\n"
            "mulps %%xmm15, %%xmm15\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
        }
        };

        std::thread thrs[N];
        for (int i = 0; i < N; ++i) {
            thrs[i] = std::thread(kernel);
        }
        for (int i = 0; i < N; ++i) {
            thrs[i].join();
        }
    };
};

template<int N, int M>
class STDOMPCombineNxMThreadPerf : public IUbench {
public:
    STDOMPCombineNxMThreadPerf() {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 4;
    };
    double CalOpsPerNs() override {
        return ((double)ops_count_ * iter_) / ns_ * N * M;
    }
private:
    void BenchImpl() override {
        auto kernel = [this]() {
        #pragma omp parallel num_threads(M)
        {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm1, %%xmm1\n"
            "mulps %%xmm2, %%xmm2\n"
            "mulps %%xmm3, %%xmm3\n"

            "mulps %%xmm4, %%xmm4\n"
            "mulps %%xmm5, %%xmm5\n"
            "mulps %%xmm6, %%xmm6\n"
            "mulps %%xmm7, %%xmm7\n"

            "mulps %%xmm8, %%xmm8\n"
            "mulps %%xmm9, %%xmm9\n"
            "mulps %%xmm10, %%xmm10\n"
            "mulps %%xmm11, %%xmm11\n"

            "mulps %%xmm12, %%xmm12\n"
            "mulps %%xmm13, %%xmm13\n"
            "mulps %%xmm14, %%xmm14\n"
            "mulps %%xmm15, %%xmm15\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
        }
        };

        std::thread thrs[N];
        for (int i = 0; i < N; ++i) {
            thrs[i] = std::thread(kernel);
        }
        for (int i = 0; i < N; ++i) {
            thrs[i].join();
        }
    };
};


int main(int argc, const char **argv) {
    std::pair<const char*, IUbench*> time_list[] {
        {"    OMP    1   Thread : %.3f ms\t GFLOPs: %.3f \n", new OMPMThreadPerf<1>},
        {"STD      1     Thread : %.3f ms\t GFLOPs: %.3f \n", new STDNThreadPerf<1>},
        {"    OMP    2   Thread : %.3f ms\t GFLOPs: %.3f \n", new OMPMThreadPerf<2>},
        {"STD      2     Thread : %.3f ms\t GFLOPs: %.3f \n", new STDNThreadPerf<2>},
        {"    OMP    4   Thread : %.3f ms\t GFLOPs: %.3f \n", new OMPMThreadPerf<4>},
        {"STD      4     Thread : %.3f ms\t GFLOPs: %.3f \n", new STDNThreadPerf<4>},
        {"    OMP    8   Thread : %.3f ms\t GFLOPs: %.3f \n", new OMPMThreadPerf<8>},
        {"STD      8     Thread : %.3f ms\t GFLOPs: %.3f \n", new STDNThreadPerf<8>},
        {"    OMP    16  Thread : %.3f ms\t GFLOPs: %.3f \n", new OMPMThreadPerf<16>},
        {"STD     16     Thread : %.3f ms\t GFLOPs: %.3f \n", new STDNThreadPerf<16>},
        {"    OMP    32  Thread : %.3f ms\t GFLOPs: %.3f \n", new OMPMThreadPerf<32>},
        {"STD     32     Thread : %.3f ms\t GFLOPs: %.3f \n", new STDNThreadPerf<32>},
        {"    OMP    64  Thread : %.3f ms\t GFLOPs: %.3f \n", new OMPMThreadPerf<64>},
        {"STD     64     Thread : %.3f ms\t GFLOPs: %.3f \n", new STDNThreadPerf<64>},
        {"    OMP    Max Thread : %.3f ms\t GFLOPs: %.3f \n", new OMPMaxThreadPerf},
        {"STDxOMP  2x2   Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<2, 2>},
        {"STDxOMP  2x4   Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<2, 4>},
        {"STDxOMP  2x8   Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<2, 8>},
        {"STDxOMP  2x16  Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<2, 16>},
        {"STDxOMP  2xMax Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMaxThreadPerf<2>},
        {"STDxOMP  4x2   Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<4, 2>},
        {"STDxOMP  4x4   Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<4, 4>},
        {"STDxOMP  4x8   Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<4, 8>},
        {"STDxOMP  4x16  Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<4, 16>},
        {"STDxOMP  4xMax Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMaxThreadPerf<4>},
        {"STDxOMP  8x2   Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<8, 2>},
        {"STDxOMP  8x4   Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<8, 4>},
        {"STDxOMP  8x8   Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMThreadPerf<8, 8>},
        {"STDxOMP  8xMax Thread : %.3f ms\t GFLOPs: %.3f \n", new STDOMPCombineNxMaxThreadPerf<8>},
        
    };

    fprintf(stderr, "OMP Max Threads: %d\n", omp_get_max_threads());
    fprintf(stderr, "OMP Thread Limit: %d\n", omp_get_thread_limit());

    for (auto p : time_list) {
        p.second->Bench(2, 5);
        fprintf(stderr, p.first, p.second->GetNs() / 1e6, p.second->CalOpsPerNs());
        delete p.second;
    }

    return 0;
}
