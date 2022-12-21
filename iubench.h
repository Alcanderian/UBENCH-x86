#ifndef _IUBENCH_H_
#define _IUBENCH_H_

#include <chrono>
#include <stdint.h>

#define _1K() (1000LL)
#define _1M() (_1K() * 1000LL)
#define _1G() (_1M() * 1000LL)

class IUbench {
public:
    virtual double CalNsPerInstruction() {
        return (double)ns_ / (instruction_count_ * iter_);
    }

    virtual double CalInstructionPerNs() {
        return ((double)instruction_count_ * iter_) / ns_;
    }

    virtual double CalOpsPerNs() {
        return ((double)ops_count_ * iter_) / ns_;
    }

    virtual void Bench(const int64_t warm_up, const int64_t iter) {
        warm_up_ = warm_up;
        iter_ = iter;
        int64_t l = warm_up;
        while (l--) {
            BenchImpl();
        }
        l = iter;
        auto t0 = std::chrono::high_resolution_clock::now();
        while (l--) {
            BenchImpl();
        }
        auto t1 = std::chrono::high_resolution_clock::now();
        ns_ = (t1 - t0).count();
    }

    int64_t GetWarmUp() { return warm_up_; }
    int64_t GetIter() { return iter_; }
    int64_t GetNs() { return ns_; }

    int64_t GetInstructionCount() { return instruction_count_; }
    int64_t GetOpsCount() { return ops_count_; }
    int64_t GetBytesCount() { return bytes_count_; }

protected:
    int64_t warm_up_;
    int64_t iter_;
    int64_t ns_ = 0;

    int64_t instruction_count_;
    int64_t ops_count_;
    int64_t bytes_count_;

    virtual void BenchImpl() = 0;
};

#endif
