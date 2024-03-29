#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>

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
    SSEMulLatency() {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 4;
    };
private:
    void BenchImpl() override {
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
    SSEMulThroughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 4;
    };
private:
    void BenchImpl() override {
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
    SSEAddLatency() {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 4;
    };
private:
    void BenchImpl() override {
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
    SSEAddThroughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 4;
    };
private:
    void BenchImpl() override {
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
    SSEMulAddIndepenDepth8Throughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 4;
    };
private:
    void BenchImpl() override {
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
    SSEMulAddDepenDepth8Throughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 4;
    };
private:
    void BenchImpl() override {
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
    SSEMulAddDepenDepth10Throughput() {
        instruction_count_ = _1G() / 20 * 20;
        ops_count_ = instruction_count_ * 4;
    };
private:
    void BenchImpl() override {
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
    SSEMulAddDepenDepth12Throughput() {
        instruction_count_ = _1G() / 20 * 24;
        ops_count_ = instruction_count_ * 4;
    };
private:
    void BenchImpl() override {
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

class SSEGemmNoAThroughput : public IUbench {
public:
    SSEGemmNoAThroughput() {
        instruction_count_ = _1G() / 20 * 24;
        ops_count_ = instruction_count_ * 4;
        memset(B_, 0, sizeof(B_));
    };
private:
    void BenchImpl() override {
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

    char B_[4 * 4 * sizeof(float)] __attribute__ ((aligned(64)));
};

class SSEGemmM4N8Throughput : public IUbench {
public:
    SSEGemmM4N8Throughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 4;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            "movups 0(%[A]), %%xmm12\n"
            "movups 0(%[B]), %%xmm13\n"
            "movups 16(%[B]), %%xmm14\n"
            ".rep 10\n"
            "pshufd $0xb1, %%xmm12, %%xmm8\n"
            "movaps %%xmm12, %%xmm9\n"
            "mulps %%xmm13, %%xmm12\n"
            "mulps %%xmm14, %%xmm9\n"
            "addps %%xmm12, %%xmm0\n"
            "addps %%xmm9, %%xmm1\n"

            "pshufd $0x1b, %%xmm8, %%xmm12\n"
            "movaps %%xmm8, %%xmm9\n"
            "mulps %%xmm13, %%xmm8\n"
            "mulps %%xmm14, %%xmm9\n"
            "addps %%xmm8, %%xmm2\n"
            "addps %%xmm9, %%xmm3\n"

            "pshufd $0xb1, %%xmm12, %%xmm8\n"
            "movaps %%xmm12, %%xmm9\n"
            "mulps %%xmm13, %%xmm12\n"
            "mulps %%xmm14, %%xmm9\n"
            "addps %%xmm12, %%xmm4\n"
            "movups 0(%[A]), %%xmm12\n"
            "addps %%xmm9, %%xmm5\n"

            "movaps %%xmm8, %%xmm9\n"
            "mulps %%xmm13, %%xmm8\n"
            "movups 0(%[B]), %%xmm13\n"
            "mulps %%xmm14, %%xmm9\n"
            "movups 16(%[B]), %%xmm14\n"
            "addps %%xmm8, %%xmm6\n"
            "addps %%xmm9, %%xmm7\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };

    char B_[2 * 4 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[4 * sizeof(float)] __attribute__ ((aligned(64)));
};

class SSEGemmM3N16Throughput : public IUbench {
public:
    SSEGemmM3N16Throughput() {
        instruction_count_ = _1G() / 20 * 24;
        ops_count_ = instruction_count_ * 4;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    void BenchImpl() override {
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

    char B_[4 * 4 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[3 * sizeof(float)] __attribute__ ((aligned(64)));
};

class SSEGemmM2N24Throughput : public IUbench {
public:
    SSEGemmM2N24Throughput() {
        instruction_count_ = _1G() / 20 * 24;
        ops_count_ = instruction_count_ * 4;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    void BenchImpl() override {
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

    char B_[4 * 6 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[2 * sizeof(float)] __attribute__ ((aligned(64)));
};

class SSEGemmM1N48Throughput : public IUbench {
public:
    SSEGemmM1N48Throughput() {
        instruction_count_ = _1G() / 20 * 24;
        ops_count_ = instruction_count_ * 4;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    void BenchImpl() override {
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

    char B_[4 * 12 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[1 * sizeof(float)] __attribute__ ((aligned(64)));
};

class SSEGemmM1N56Throughput : public IUbench {
public:
    SSEGemmM1N56Throughput() {
        instruction_count_ = _1G() / 20 * 28;
        ops_count_ = instruction_count_ * 4;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "movss 0(%[A]), %%xmm14\n"
            "shufps $0, %%xmm14, %%xmm14\n"

            "movups 0(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm0\n"
            "movups 16(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm1\n"

            "movups 32(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm2\n"
            "movups 48(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm3\n"

            "movups 64(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm4\n"
            "movups 80(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm5\n"

            "movups 96(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm6\n"
            "movups 112(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm7\n"

            "movups 128(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm8\n"
            "movups 144(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm9\n"

            "movups 160(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm10\n"
            "movups 176(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm11\n"

            "movups 192(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm11\n"
            "movups 208(%[B]), %%xmm15\n"
            "mulps %%xmm14, %%xmm15\n"
            "addps %%xmm15, %%xmm12\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 28 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };

    char B_[4 * 14 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[1 * sizeof(float)] __attribute__ ((aligned(64)));
};

class SSEGemmM2N16Throughput : public IUbench {
public:
    SSEGemmM2N16Throughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 4;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            XMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "movups 0(%[B]), %%xmm12\n"
            "movups 16(%[B]), %%xmm13\n"
            "movups 32(%[B]), %%xmm14\n"
            "movups 48(%[B]), %%xmm15\n"

            "movss 0(%[A]), %%xmm8\n"
            "shufps $0, %%xmm8, %%xmm8\n"
            "movss 4(%[A]), %%xmm9\n"
            "shufps $0, %%xmm9, %%xmm9\n"

            "movaps %%xmm12, %%xmm10\n"
            "movaps %%xmm13, %%xmm11\n"
            "mulps %%xmm8, %%xmm10\n"
            "mulps %%xmm8, %%xmm11\n"
            "addps %%xmm10, %%xmm0\n"
            "addps %%xmm11, %%xmm1\n"

            "movaps %%xmm14, %%xmm10\n"
            "movaps %%xmm15, %%xmm11\n"
            "mulps %%xmm8, %%xmm10\n"
            "mulps %%xmm8, %%xmm11\n"
            "addps %%xmm10, %%xmm2\n"
            "addps %%xmm11, %%xmm3\n"

            "mulps %%xmm9, %%xmm12\n"
            "mulps %%xmm9, %%xmm13\n"
            "addps %%xmm12, %%xmm4\n"
            "addps %%xmm13, %%xmm5\n"

            "mulps %%xmm9, %%xmm14\n"
            "mulps %%xmm9, %%xmm15\n"
            "addps %%xmm14, %%xmm6\n"
            "addps %%xmm15, %%xmm7\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "xmm0" , "xmm1" , "xmm2" , "xmm3" , "xmm4" , "xmm5" , "xmm6" , "xmm7" ,
            "xmm8" , "xmm9" , "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"
        );
    };

    char B_[4 * 4 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[2 * sizeof(float)] __attribute__ ((aligned(64)));
};

int main(int argc, const char **argv) {
    std::pair<const char*, IUbench*> lat_list[] = {
        {"SSE Mul Latency                   : %.3f ns\n", new SSEMulLatency},
        {"SSE Add Latency                   : %.3f ns\n", new SSEAddLatency},
    };
    std::pair<const char*, IUbench*> tp_list[] {
        {"SSE Mul Throughput                : %.3f /ns,\t GFLOPs: %.3f\n", new SSEMulThroughput},
        {"SSE Add Throughput                : %.3f /ns,\t GFLOPs: %.3f\n", new SSEAddThroughput},
        {"SSE 8x  Mul-Add w/o Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new SSEMulAddIndepenDepth8Throughput},
        {"SSE 8x  Mul-Add w/  Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new SSEMulAddDepenDepth8Throughput},
        {"SSE 10x Mul-Add w/  Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new SSEMulAddDepenDepth10Throughput},
        {"SSE 12x Mul-Add w/  Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new SSEMulAddDepenDepth12Throughput},
        {"SSE Gemm w/o A Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new SSEGemmNoAThroughput},
        {"SSE Gemm M4N8  Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new SSEGemmM4N8Throughput},
        {"SSE Gemm M3N16 Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new SSEGemmM3N16Throughput},
        {"SSE Gemm M2N24 Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new SSEGemmM2N24Throughput},
        {"SSE Gemm M1N48 Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new SSEGemmM1N48Throughput},
        {"SSE Gemm M1N56 Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new SSEGemmM1N56Throughput},
        {"SSE Gemm M2N16 Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new SSEGemmM2N16Throughput},
    };

    for (auto p : lat_list) {
        p.second->Bench(1, 3);
        fprintf(stderr, p.first, p.second->CalNsPerInstruction());
        delete p.second;
    }

    for (auto p : tp_list) {
        p.second->Bench(1, 3);
        fprintf(stderr, p.first, p.second->CalInstructionPerNs(), p.second->CalOpsPerNs());
        delete p.second;
    }

    return 0;
}
