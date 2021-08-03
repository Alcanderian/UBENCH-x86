#ifndef _IUBENCH_H_
#define _IUBENCH_H_

#include <chrono>
#include <stdint.h>

#define _1K() (1000LL)
#define _1M() (_1K() * 1000LL)
#define _1G() (_1M() * 1000LL)

class IUbench {
public:
    virtual double BenchNsPI(const int64_t warm, const int64_t loop) {
        int64_t l = warm;
        while (l--) {
            BenchImpl();
        }
        l = loop;
        auto t0 = std::chrono::high_resolution_clock::now();
        while (l--) {
            BenchImpl();
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        const double ns = (t1 - t0).count();
        return ns / (instruction_count_ * loop);
    }

    virtual double BenchIPNs(const int64_t warm, const int64_t loop) {
        int64_t l = warm;
        while (l--) {
            BenchImpl();
        }
        l = loop;
        auto t0 = std::chrono::high_resolution_clock::now();
        while (l--) {
            BenchImpl();
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        const double ns = (t1 - t0).count();
        return (instruction_count_ * loop) / ns;
    }

    int64_t GetInstructionCount() { return instruction_count_; };

protected:
    int64_t instruction_count_;

    virtual void BenchImpl() = 0;
};

#endif
