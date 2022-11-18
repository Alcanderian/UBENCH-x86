#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "iubench.h"

#define YMM_INIT() \
    "vxorps %%ymm0, %%ymm0, %%ymm0\n"\
    "vxorps %%ymm1, %%ymm1, %%ymm1\n"\
    "vxorps %%ymm2, %%ymm2, %%ymm2\n"\
    "vxorps %%ymm3, %%ymm3, %%ymm3\n"\
    "vxorps %%ymm4, %%ymm4, %%ymm4\n"\
    "vxorps %%ymm5, %%ymm5, %%ymm5\n"\
    "vxorps %%ymm6, %%ymm6, %%ymm6\n"\
    "vxorps %%ymm7, %%ymm7, %%ymm7\n"\
    "vxorps %%ymm8, %%ymm8, %%ymm8\n"\
    "vxorps %%ymm9, %%ymm9, %%ymm9\n"\
    "vxorps %%ymm10, %%ymm10, %%ymm10\n"\
    "vxorps %%ymm11, %%ymm11, %%ymm11\n"\
    "vxorps %%ymm12, %%ymm12, %%ymm12\n"\
    "vxorps %%ymm13, %%ymm13, %%ymm13\n"\
    "vxorps %%ymm14, %%ymm14, %%ymm14\n"\
    "vxorps %%ymm15, %%ymm15, %%ymm15\n"

class FMAMacLatency : public IUbench {
public:
    FMAMacLatency() {
        instruction_count_ = _1G() / 40 * 16;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"

            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"

            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"

            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class FMAMacThroughput : public IUbench {
public:
    FMAMacThroughput() {
        instruction_count_ = _1G() / 20 * 16;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm1, %%ymm1, %%ymm1\n"
            "vfmadd231ps %%ymm2, %%ymm2, %%ymm2\n"
            "vfmadd231ps %%ymm3, %%ymm3, %%ymm3\n"

            "vfmadd231ps %%ymm4, %%ymm4, %%ymm4\n"
            "vfmadd231ps %%ymm5, %%ymm5, %%ymm5\n"
            "vfmadd231ps %%ymm6, %%ymm6, %%ymm6\n"
            "vfmadd231ps %%ymm7, %%ymm7, %%ymm7\n"

            "vfmadd231ps %%ymm8, %%ymm8, %%ymm8\n"
            "vfmadd231ps %%ymm9, %%ymm9, %%ymm9\n"
            "vfmadd231ps %%ymm10, %%ymm10, %%ymm10\n"
            "vfmadd231ps %%ymm11, %%ymm11, %%ymm11\n"

            "vfmadd231ps %%ymm12, %%ymm12, %%ymm12\n"
            "vfmadd231ps %%ymm13, %%ymm13, %%ymm13\n"
            "vfmadd231ps %%ymm14, %%ymm14, %%ymm14\n"
            "vfmadd231ps %%ymm15, %%ymm15, %%ymm15\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class FMAMacAddThroughput : public IUbench {
public:
    FMAMacAddThroughput() {
        instruction_count_ = _1G() / 20 * 32;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm1, %%ymm1, %%ymm1\n"
            "vaddps %%ymm1, %%ymm1, %%ymm1\n"
            "vfmadd231ps %%ymm2, %%ymm2, %%ymm2\n"
            "vaddps %%ymm2, %%ymm2, %%ymm2\n"
            "vfmadd231ps %%ymm3, %%ymm3, %%ymm3\n"
            "vaddps %%ymm3, %%ymm3, %%ymm3\n"

            "vfmadd231ps %%ymm4, %%ymm4, %%ymm4\n"
            "vaddps %%ymm4, %%ymm4, %%ymm4\n"
            "vfmadd231ps %%ymm5, %%ymm5, %%ymm5\n"
            "vaddps %%ymm5, %%ymm5, %%ymm5\n"
            "vfmadd231ps %%ymm6, %%ymm6, %%ymm6\n"
            "vaddps %%ymm6, %%ymm6, %%ymm6\n"
            "vfmadd231ps %%ymm7, %%ymm7, %%ymm7\n"
            "vaddps %%ymm7, %%ymm7, %%ymm7\n"

            "vfmadd231ps %%ymm8, %%ymm8, %%ymm8\n"
            "vaddps %%ymm8, %%ymm8, %%ymm8\n"
            "vfmadd231ps %%ymm9, %%ymm9, %%ymm9\n"
            "vaddps %%ymm9, %%ymm9, %%ymm9\n"
            "vfmadd231ps %%ymm10, %%ymm10, %%ymm10\n"
            "vaddps %%ymm10, %%ymm10, %%ymm10\n"
            "vfmadd231ps %%ymm11, %%ymm11, %%ymm11\n"
            "vaddps %%ymm11, %%ymm11, %%ymm11\n"

            "vfmadd231ps %%ymm12, %%ymm12, %%ymm12\n"
            "vaddps %%ymm12, %%ymm12, %%ymm12\n"
            "vfmadd231ps %%ymm13, %%ymm13, %%ymm13\n"
            "vaddps %%ymm13, %%ymm13, %%ymm13\n"
            "vfmadd231ps %%ymm14, %%ymm14, %%ymm14\n"
            "vaddps %%ymm14, %%ymm14, %%ymm14\n"
            "vfmadd231ps %%ymm15, %%ymm15, %%ymm15\n"
            "vaddps %%ymm15, %%ymm15, %%ymm15\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 32 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class FMAMacMulThroughput : public IUbench {
public:
    FMAMacMulThroughput() {
        instruction_count_ = _1G() / 20 * 32;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm1, %%ymm1, %%ymm1\n"
            "vmulps %%ymm1, %%ymm1, %%ymm1\n"
            "vfmadd231ps %%ymm2, %%ymm2, %%ymm2\n"
            "vmulps %%ymm2, %%ymm2, %%ymm2\n"
            "vfmadd231ps %%ymm3, %%ymm3, %%ymm3\n"
            "vmulps %%ymm3, %%ymm3, %%ymm3\n"

            "vfmadd231ps %%ymm4, %%ymm4, %%ymm4\n"
            "vmulps %%ymm4, %%ymm4, %%ymm4\n"
            "vfmadd231ps %%ymm5, %%ymm5, %%ymm5\n"
            "vmulps %%ymm5, %%ymm5, %%ymm5\n"
            "vfmadd231ps %%ymm6, %%ymm6, %%ymm6\n"
            "vmulps %%ymm6, %%ymm6, %%ymm6\n"
            "vfmadd231ps %%ymm7, %%ymm7, %%ymm7\n"
            "vmulps %%ymm7, %%ymm7, %%ymm7\n"

            "vfmadd231ps %%ymm8, %%ymm8, %%ymm8\n"
            "vmulps %%ymm8, %%ymm8, %%ymm8\n"
            "vfmadd231ps %%ymm9, %%ymm9, %%ymm9\n"
            "vmulps %%ymm9, %%ymm9, %%ymm9\n"
            "vfmadd231ps %%ymm10, %%ymm10, %%ymm10\n"
            "vmulps %%ymm10, %%ymm10, %%ymm10\n"
            "vfmadd231ps %%ymm11, %%ymm11, %%ymm11\n"
            "vmulps %%ymm11, %%ymm11, %%ymm11\n"

            "vfmadd231ps %%ymm12, %%ymm12, %%ymm12\n"
            "vmulps %%ymm12, %%ymm12, %%ymm12\n"
            "vfmadd231ps %%ymm13, %%ymm13, %%ymm13\n"
            "vmulps %%ymm13, %%ymm13, %%ymm13\n"
            "vfmadd231ps %%ymm14, %%ymm14, %%ymm14\n"
            "vmulps %%ymm14, %%ymm14, %%ymm14\n"
            "vfmadd231ps %%ymm15, %%ymm15, %%ymm15\n"
            "vmulps %%ymm15, %%ymm15, %%ymm15\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 32 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class FMAMacDepth8Throughput : public IUbench {
public:
    FMAMacDepth8Throughput() {
        instruction_count_ = _1G() / 20 * 16;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm1, %%ymm1, %%ymm1\n"
            "vfmadd231ps %%ymm2, %%ymm2, %%ymm2\n"
            "vfmadd231ps %%ymm3, %%ymm3, %%ymm3\n"

            "vfmadd231ps %%ymm4, %%ymm4, %%ymm4\n"
            "vfmadd231ps %%ymm5, %%ymm5, %%ymm5\n"
            "vfmadd231ps %%ymm6, %%ymm6, %%ymm6\n"
            "vfmadd231ps %%ymm7, %%ymm7, %%ymm7\n"

            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm1, %%ymm1, %%ymm1\n"
            "vfmadd231ps %%ymm2, %%ymm2, %%ymm2\n"
            "vfmadd231ps %%ymm3, %%ymm3, %%ymm3\n"

            "vfmadd231ps %%ymm4, %%ymm4, %%ymm4\n"
            "vfmadd231ps %%ymm5, %%ymm5, %%ymm5\n"
            "vfmadd231ps %%ymm6, %%ymm6, %%ymm6\n"
            "vfmadd231ps %%ymm7, %%ymm7, %%ymm7\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 16 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class FMAMacDepth10Throughput : public IUbench {
public:
    FMAMacDepth10Throughput() {
        instruction_count_ = _1G() / 20 * 20;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm1, %%ymm1, %%ymm1\n"
            "vfmadd231ps %%ymm2, %%ymm2, %%ymm2\n"
            "vfmadd231ps %%ymm3, %%ymm3, %%ymm3\n"

            "vfmadd231ps %%ymm4, %%ymm4, %%ymm4\n"
            "vfmadd231ps %%ymm5, %%ymm5, %%ymm5\n"
            "vfmadd231ps %%ymm6, %%ymm6, %%ymm6\n"
            "vfmadd231ps %%ymm7, %%ymm7, %%ymm7\n"

            "vfmadd231ps %%ymm8, %%ymm8, %%ymm8\n"
            "vfmadd231ps %%ymm9, %%ymm9, %%ymm9\n"

            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm1, %%ymm1, %%ymm1\n"
            "vfmadd231ps %%ymm2, %%ymm2, %%ymm2\n"
            "vfmadd231ps %%ymm3, %%ymm3, %%ymm3\n"

            "vfmadd231ps %%ymm4, %%ymm4, %%ymm4\n"
            "vfmadd231ps %%ymm5, %%ymm5, %%ymm5\n"
            "vfmadd231ps %%ymm6, %%ymm6, %%ymm6\n"
            "vfmadd231ps %%ymm7, %%ymm7, %%ymm7\n"

            "vfmadd231ps %%ymm8, %%ymm8, %%ymm8\n"
            "vfmadd231ps %%ymm9, %%ymm9, %%ymm9\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 20 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class FMAMacDepth12Throughput : public IUbench {
public:
    FMAMacDepth12Throughput() {
        instruction_count_ = _1G() / 20 * 24;
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm1, %%ymm1, %%ymm1\n"
            "vfmadd231ps %%ymm2, %%ymm2, %%ymm2\n"
            "vfmadd231ps %%ymm3, %%ymm3, %%ymm3\n"

            "vfmadd231ps %%ymm4, %%ymm4, %%ymm4\n"
            "vfmadd231ps %%ymm5, %%ymm5, %%ymm5\n"
            "vfmadd231ps %%ymm6, %%ymm6, %%ymm6\n"
            "vfmadd231ps %%ymm7, %%ymm7, %%ymm7\n"

            "vfmadd231ps %%ymm8, %%ymm8, %%ymm8\n"
            "vfmadd231ps %%ymm9, %%ymm9, %%ymm9\n"
            "vfmadd231ps %%ymm10, %%ymm10, %%ymm10\n"
            "vfmadd231ps %%ymm11, %%ymm11, %%ymm11\n"

            "vfmadd231ps %%ymm0, %%ymm0, %%ymm0\n"
            "vfmadd231ps %%ymm1, %%ymm1, %%ymm1\n"
            "vfmadd231ps %%ymm2, %%ymm2, %%ymm2\n"
            "vfmadd231ps %%ymm3, %%ymm3, %%ymm3\n"

            "vfmadd231ps %%ymm4, %%ymm4, %%ymm4\n"
            "vfmadd231ps %%ymm5, %%ymm5, %%ymm5\n"
            "vfmadd231ps %%ymm6, %%ymm6, %%ymm6\n"
            "vfmadd231ps %%ymm7, %%ymm7, %%ymm7\n"

            "vfmadd231ps %%ymm8, %%ymm8, %%ymm8\n"
            "vfmadd231ps %%ymm9, %%ymm9, %%ymm9\n"
            "vfmadd231ps %%ymm10, %%ymm10, %%ymm10\n"
            "vfmadd231ps %%ymm11, %%ymm11, %%ymm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class FMAGemmNoAThroughput : public IUbench {
public:
    FMAGemmNoAThroughput() {
        instruction_count_ = _1G() / 20 * 12;
        memset(B_, 0, sizeof(B_));
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "vmovups 0(%[B]), %%ymm14\n"
            "vmovups 32(%[B]), %%ymm15\n"

            "vfmadd231ps %%ymm12, %%ymm14, %%ymm0\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm1\n"

            "vfmadd231ps %%ymm12, %%ymm14, %%ymm2\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm3\n"

            "vfmadd231ps %%ymm12, %%ymm14, %%ymm4\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm5\n"

            "vfmadd231ps %%ymm12, %%ymm14, %%ymm6\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm7\n"

            "vfmadd231ps %%ymm12, %%ymm14, %%ymm8\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm9\n"

            "vfmadd231ps %%ymm12, %%ymm14, %%ymm10\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 12 / 10),
            [B]    "r" (B_)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };

    char B_[2 * 8 * sizeof(float)] __attribute__ ((aligned(64)));
};

class FMAGemmM6N16Throughput : public IUbench {
public:
    FMAGemmM6N16Throughput() {
        instruction_count_ = _1G() / 20 * 12;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "vmovups 0(%[B]), %%ymm14\n"
            "vmovups 32(%[B]), %%ymm15\n"

            "vbroadcastss 0(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm0\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm1\n"

            "vbroadcastss 4(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm2\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm3\n"

            "vbroadcastss 8(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm4\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm5\n"

            "vbroadcastss 12(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm6\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm7\n"

            "vbroadcastss 16(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm8\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm9\n"

            "vbroadcastss 20(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm10\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 12 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };

    char B_[2 * 8 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[6 * sizeof(float)] __attribute__ ((aligned(64)));
};

class FMAGemmM4N24Throughput : public IUbench {
public:
    FMAGemmM4N24Throughput() {
        instruction_count_ = _1G() / 20 * 12;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "vmovups 0(%[B]), %%ymm13\n"
            "vmovups 32(%[B]), %%ymm14\n"
            "vmovups 64(%[B]), %%ymm15\n"

            "vbroadcastss 0(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm13, %%ymm0\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm1\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm2\n"

            "vbroadcastss 4(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm13, %%ymm4\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm5\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm6\n"

            "vbroadcastss 8(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm13, %%ymm7\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm8\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm9\n"

            "vbroadcastss 12(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm13, %%ymm10\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm11\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm12\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 12 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };

    char B_[3 * 8 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[4 * sizeof(float)] __attribute__ ((aligned(64)));
};

class FMAGemmM3N32Throughput : public IUbench {
public:
    FMAGemmM3N32Throughput() {
        instruction_count_ = _1G() / 20 * 12;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "vbroadcastss 0(%[A]), %%ymm13\n"
            "vbroadcastss 4(%[A]), %%ymm14\n"
            "vbroadcastss 8(%[A]), %%ymm15\n"

            "vmovups 0(%[B]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm13, %%ymm0\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm1\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm2\n"

            "vmovups 32(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm13, %%ymm4\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm5\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm6\n"

            "vmovups 64(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm13, %%ymm7\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm8\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm9\n"

            "vmovups 96(%[A]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm13, %%ymm10\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm11\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm12\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 12 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };

    char B_[4 * 8 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[3 * sizeof(float)] __attribute__ ((aligned(64)));
};

class FMAGemmM2N48Throughput : public IUbench {
public:
    FMAGemmM2N48Throughput() {
        instruction_count_ = _1G() / 20 * 12;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    virtual void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "vbroadcastss 0(%[A]), %%ymm14\n"
            "vbroadcastss 4(%[A]), %%ymm15\n"

            "vmovups 0(%[B]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm0\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm1\n"

            "vmovups 32(%[B]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm2\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm3\n"

            "vmovups 64(%[B]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm4\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm5\n"

            "vmovups 96(%[B]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm6\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm7\n"

            "vmovups 128(%[B]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm8\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm9\n"

            "vmovups 160(%[B]), %%ymm12\n"
            "vfmadd231ps %%ymm12, %%ymm14, %%ymm10\n"
            "vfmadd231ps %%ymm12, %%ymm15, %%ymm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 12 / 10),
            [B]    "r" (B_),
            [A]    "r" (A_)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };

    char B_[6 * 8 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[2 * sizeof(float)] __attribute__ ((aligned(64)));
};

int main(int argc, const char **argv) {

    fprintf(stderr, "FMA Mac Latency       :\t%.3f NanoS\n", FMAMacLatency().BenchNsPI(1, 3));
    fprintf(stderr, "FMA Mac Throughput    :\t%.3f /NanoS\n", FMAMacThroughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA Mac+Add Throughput:\t%.3f /NanoS\n", FMAMacAddThroughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA Mac+Mul Throughput:\t%.3f /NanoS\n", FMAMacMulThroughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA 8x Mac Throughput :\t%.3f /NanoS\n", FMAMacDepth8Throughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA 10x Mac Throughput:\t%.3f /NanoS\n", FMAMacDepth10Throughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA 12x Mac Throughput:\t%.3f /NanoS\n", FMAMacDepth12Throughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA Gemm w/o A Mac Throughput:\t%.3f /NanoS\n", FMAGemmNoAThroughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA Gemm M6N16 Mac Throughput:\t%.3f /NanoS\n", FMAGemmM6N16Throughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA Gemm M4N24 Mac Throughput:\t%.3f /NanoS\n", FMAGemmM4N24Throughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA Gemm M3N32 Mac Throughput:\t%.3f /NanoS\n", FMAGemmM3N32Throughput().BenchIPNs(1, 3));
    fprintf(stderr, "FMA Gemm M2N48 Mac Throughput:\t%.3f /NanoS\n", FMAGemmM2N48Throughput().BenchIPNs(1, 3));

    return 0;
}
