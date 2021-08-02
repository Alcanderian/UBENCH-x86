#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

class SSEMulLatency : public IUbench {
public:
    SSEMulLatency(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 40 * 16;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"

            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"

            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"

            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"
            "mulps %%xmm0, %%xmm0\n"
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
};

class SSEMulThroughput : public IUbench {
public:
    SSEMulThroughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 16;
    };
private:
    virtual void BenchImpl() override {
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
};

class SSEAddLatency : public IUbench {
public:
    SSEAddLatency(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 40 * 16;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"

            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"

            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"

            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm0, %%xmm0\n"
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
};

class SSEAddThroughput : public IUbench {
public:
    SSEAddThroughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 16;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm1, %%xmm1\n"
            "addps %%xmm2, %%xmm2\n"
            "addps %%xmm3, %%xmm3\n"

            "addps %%xmm4, %%xmm4\n"
            "addps %%xmm5, %%xmm5\n"
            "addps %%xmm6, %%xmm6\n"
            "addps %%xmm7, %%xmm7\n"

            "addps %%xmm8, %%xmm8\n"
            "addps %%xmm9, %%xmm9\n"
            "addps %%xmm10, %%xmm10\n"
            "addps %%xmm11, %%xmm11\n"

            "addps %%xmm12, %%xmm12\n"
            "addps %%xmm13, %%xmm13\n"
            "addps %%xmm14, %%xmm14\n"
            "addps %%xmm15, %%xmm15\n"
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
};

class SSEMulAddIndepenDepth8Throughput : public IUbench {
public:
    SSEMulAddIndepenDepth8Throughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 16;
    };
private:
    virtual void BenchImpl() override {
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

            "addps %%xmm8, %%xmm8\n"
            "addps %%xmm9, %%xmm9\n"
            "addps %%xmm10, %%xmm10\n"
            "addps %%xmm11, %%xmm11\n"

            "addps %%xmm12, %%xmm12\n"
            "addps %%xmm13, %%xmm13\n"
            "addps %%xmm14, %%xmm14\n"
            "addps %%xmm15, %%xmm15\n"
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
};

class SSEMulAddDepenDepth8Throughput : public IUbench {
public:
    SSEMulAddDepenDepth8Throughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 16;
    };
private:
    virtual void BenchImpl() override {
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

            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm1, %%xmm1\n"
            "addps %%xmm2, %%xmm2\n"
            "addps %%xmm3, %%xmm3\n"

            "addps %%xmm4, %%xmm4\n"
            "addps %%xmm5, %%xmm5\n"
            "addps %%xmm6, %%xmm6\n"
            "addps %%xmm7, %%xmm7\n"
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
};

class SSEMulAddDepenDepth10Throughput : public IUbench {
public:
    SSEMulAddDepenDepth10Throughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 20;
    };
private:
    virtual void BenchImpl() override {
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

            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm1, %%xmm1\n"
            "addps %%xmm2, %%xmm2\n"
            "addps %%xmm3, %%xmm3\n"

            "addps %%xmm4, %%xmm4\n"
            "addps %%xmm5, %%xmm5\n"
            "addps %%xmm6, %%xmm6\n"
            "addps %%xmm7, %%xmm7\n"

            "addps %%xmm8, %%xmm8\n"
            "addps %%xmm9, %%xmm9\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 20 / 10)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };
};

class SSEMulAddDepenDepth12Throughput : public IUbench {
public:
    SSEMulAddDepenDepth12Throughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 24;
    };
private:
    virtual void BenchImpl() override {
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

            "addps %%xmm0, %%xmm0\n"
            "addps %%xmm1, %%xmm1\n"
            "addps %%xmm2, %%xmm2\n"
            "addps %%xmm3, %%xmm3\n"

            "addps %%xmm4, %%xmm4\n"
            "addps %%xmm5, %%xmm5\n"
            "addps %%xmm6, %%xmm6\n"
            "addps %%xmm7, %%xmm7\n"

            "addps %%xmm8, %%xmm8\n"
            "addps %%xmm9, %%xmm9\n"
            "addps %%xmm10, %%xmm10\n"
            "addps %%xmm11, %%xmm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };
};

class SSEMulAddDepenDepth12SameSrcThroughput : public IUbench {
public:
    SSEMulAddDepenDepth12SameSrcThroughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 24;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "mulps %%xmm15, %%xmm0\n"
            "mulps %%xmm15, %%xmm1\n"
            "mulps %%xmm15, %%xmm2\n"
            "mulps %%xmm15, %%xmm3\n"

            "mulps %%xmm15, %%xmm4\n"
            "mulps %%xmm15, %%xmm5\n"
            "mulps %%xmm15, %%xmm6\n"
            "mulps %%xmm15, %%xmm7\n"

            "mulps %%xmm15, %%xmm8\n"
            "mulps %%xmm15, %%xmm9\n"
            "mulps %%xmm15, %%xmm10\n"
            "mulps %%xmm15, %%xmm11\n"

            "addps %%xmm15, %%xmm0\n"
            "addps %%xmm15, %%xmm1\n"
            "addps %%xmm15, %%xmm2\n"
            "addps %%xmm15, %%xmm3\n"

            "addps %%xmm15, %%xmm4\n"
            "addps %%xmm15, %%xmm5\n"
            "addps %%xmm15, %%xmm6\n"
            "addps %%xmm15, %%xmm7\n"

            "addps %%xmm15, %%xmm8\n"
            "addps %%xmm15, %%xmm9\n"
            "addps %%xmm15, %%xmm10\n"
            "addps %%xmm15, %%xmm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };
};

class SSEGemmNoAThroughput : public IUbench {
public:
    SSEGemmNoAThroughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 24;
        memset(B_, 0, sizeof(B_));
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "movups 0(%[B]), %%xmm14\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm0\n"
            "addps %%xmm15, %%xmm1\n"

            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm2\n"
            "addps %%xmm15, %%xmm3\n"

            "movups 0(%[B]), %%xmm14\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm13, %%xmm14\n"
            "mulps %%xmm13, %%xmm15\n"
            "addps %%xmm14, %%xmm4\n"
            "addps %%xmm15, %%xmm5\n"

            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm13, %%xmm14\n"
            "mulps %%xmm13, %%xmm15\n"
            "addps %%xmm14, %%xmm6\n"
            "addps %%xmm15, %%xmm7\n"

            "movups 0(%[B]), %%xmm14\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm8\n"
            "addps %%xmm15, %%xmm9\n"

            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm10\n"
            "addps %%xmm15, %%xmm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10),
            [B]    "r" (B_)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };

    char B_[4 * 4 * sizeof(float)];
};

class SSEGemmM3N16Throughput : public IUbench {
public:
    SSEGemmM3N16Throughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 24;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "movss 0(%[A]), %%xmm12\n"
            "shufps $0, %%xmm12, %%xmm12\n"
            "movss 4(%[A]), %%xmm13\n"
            "shufps $0, %%xmm13, %%xmm13\n"

            "movups 0(%[B]), %%xmm14\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm0\n"
            "addps %%xmm15, %%xmm1\n"

            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm2\n"
            "addps %%xmm15, %%xmm3\n"

            "movups 0(%[B]), %%xmm14\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm13, %%xmm14\n"
            "mulps %%xmm13, %%xmm15\n"
            "addps %%xmm14, %%xmm4\n"
            "addps %%xmm15, %%xmm5\n"

            "movss 8(%[A]), %%xmm12\n"
            "shufps $0, %%xmm12, %%xmm12\n"

            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm13, %%xmm14\n"
            "mulps %%xmm13, %%xmm15\n"
            "addps %%xmm14, %%xmm6\n"
            "addps %%xmm15, %%xmm7\n"

            "movups 0(%[B]), %%xmm14\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm8\n"
            "addps %%xmm15, %%xmm9\n"

            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm10\n"
            "addps %%xmm15, %%xmm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };

    char B_[4 * 4 * sizeof(float)];
    char A_[3 * sizeof(float)];
};

class SSEGemmM2N24Throughput : public IUbench {
public:
    SSEGemmM2N24Throughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 24;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "movss 0(%[A]), %%xmm12\n"
            "shufps $0, %%xmm12, %%xmm12\n"
            "movss 4(%[A]), %%xmm13\n"
            "shufps $0, %%xmm13, %%xmm13\n"

            "movups 0(%[B]), %%xmm14\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm0\n"
            "addps %%xmm15, %%xmm1\n"

            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm2\n"
            "addps %%xmm15, %%xmm3\n"

            "movups 64(%[B]), %%xmm14\n"
            "movups 80(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm4\n"
            "addps %%xmm15, %%xmm5\n"

            "movups 0(%[B]), %%xmm14\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm13, %%xmm14\n"
            "mulps %%xmm13, %%xmm15\n"
            "addps %%xmm14, %%xmm6\n"
            "addps %%xmm15, %%xmm7\n"

            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm13, %%xmm14\n"
            "mulps %%xmm13, %%xmm15\n"
            "addps %%xmm14, %%xmm8\n"
            "addps %%xmm15, %%xmm9\n"

            "movups 64(%[B]), %%xmm14\n"
            "movups 80(%[B]), %%xmm15\n"
            "mulps %%xmm13, %%xmm14\n"
            "mulps %%xmm13, %%xmm15\n"
            "addps %%xmm14, %%xmm10\n"
            "addps %%xmm15, %%xmm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };

    char B_[4 * 6 * sizeof(float)];
    char A_[2 * sizeof(float)];
};

class SSEGemmM1N48Throughput : public IUbench {
public:
    SSEGemmM1N48Throughput(const int64_t freq) : IUbench(freq) {
        instruction_count_ = _1G() / 20 * 24;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "movss 0(%[A]), %%xmm12\n"
            "shufps $0, %%xmm12, %%xmm12\n"

            "movups 0(%[B]), %%xmm14\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm0\n"
            "addps %%xmm15, %%xmm1\n"

            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm2\n"
            "addps %%xmm15, %%xmm3\n"

            "movups 64(%[B]), %%xmm14\n"
            "movups 80(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm4\n"
            "addps %%xmm15, %%xmm5\n"

            "movups 96(%[B]), %%xmm14\n"
            "movups 112(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm6\n"
            "addps %%xmm15, %%xmm7\n"

            "movups 128(%[B]), %%xmm14\n"
            "movups 144(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm8\n"
            "addps %%xmm15, %%xmm9\n"

            "movups 160(%[B]), %%xmm14\n"
            "movups 176(%[B]), %%xmm15\n"
            "mulps %%xmm12, %%xmm14\n"
            "mulps %%xmm12, %%xmm15\n"
            "addps %%xmm14, %%xmm10\n"
            "addps %%xmm15, %%xmm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };

    char B_[4 * 12 * sizeof(float)];
    char A_[1 * sizeof(float)];
};

#define USAGE() "usage: %s <freq by MHz>\n"

int main(int argc, const char **argv) {
    if (argc != 2) {
        fprintf(stderr, USAGE(), argv[0]);
        return 0;
    }

    int64_t freq = atoi(argv[1]);
    fprintf(stderr, "Freq: %ld MHz\n", freq);
    if (freq == 0) {
        fprintf(stderr, "Invalid Freq\n");
        return 0;
    }
    freq *= _1M();

    fprintf(stderr, "SSE Mul Latency   :\t%.3f cycle\n", SSEMulLatency(freq).BenchCPI(1, 3));
    fprintf(stderr, "SSE Mul Throughput:\t%.3f per cycle\n", SSEMulThroughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE Add Latency   :\t%.3f cycle\n", SSEAddLatency(freq).BenchCPI(1, 3));
    fprintf(stderr, "SSE Add Throughput:\t%.3f per cycle\n", SSEAddThroughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE 8x Mul-Add w/o Dep Throughput:\t%.3f per cycle\n", SSEMulAddIndepenDepth8Throughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE 8x Mul-Add w/ Dep Throughput :\t%.3f per cycle\n", SSEMulAddDepenDepth8Throughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE 10x Mul-Add w/ Dep Throughput:\t%.3f per cycle\n", SSEMulAddDepenDepth10Throughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE 12x Mul-Add w/ Dep Throughput:\t%.3f per cycle\n", SSEMulAddDepenDepth12Throughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE 12x Mul-Add w/ Dep SameSrc Throughput:\t%.3f per cycle\n", SSEMulAddDepenDepth12Throughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE Gemm w/o A Mul-Add Throughput:\t%.3f per cycle\n", SSEGemmNoAThroughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE Gemm M3N16 Mul-Add Throughput:\t%.3f per cycle\n", SSEGemmM3N16Throughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE Gemm M2N24 Mul-Add Throughput:\t%.3f per cycle\n", SSEGemmM2N24Throughput(freq).BenchIPC(1, 3));
    fprintf(stderr, "SSE Gemm M1N48 Mul-Add Throughput:\t%.3f per cycle\n", SSEGemmM1N48Throughput(freq).BenchIPC(1, 3));

    return 0;
}
