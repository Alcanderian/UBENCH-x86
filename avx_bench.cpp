#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>

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

class AVXMulLatency : public IUbench {
public:
    AVXMulLatency() {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"

            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"

            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"

            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
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

class AVXMulThroughput : public IUbench {
public:
    AVXMulThroughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm1, %%ymm1, %%ymm1\n"
            "vmulps %%ymm2, %%ymm2, %%ymm2\n"
            "vmulps %%ymm3, %%ymm3, %%ymm3\n"

            "vmulps %%ymm4, %%ymm4, %%ymm4\n"
            "vmulps %%ymm5, %%ymm5, %%ymm5\n"
            "vmulps %%ymm6, %%ymm6, %%ymm6\n"
            "vmulps %%ymm7, %%ymm7, %%ymm7\n"

            "vmulps %%ymm8, %%ymm8, %%ymm8\n"
            "vmulps %%ymm9, %%ymm9, %%ymm9\n"
            "vmulps %%ymm10, %%ymm10, %%ymm10\n"
            "vmulps %%ymm11, %%ymm11, %%ymm11\n"

            "vmulps %%ymm12, %%ymm12, %%ymm12\n"
            "vmulps %%ymm13, %%ymm13, %%ymm13\n"
            "vmulps %%ymm14, %%ymm14, %%ymm14\n"
            "vmulps %%ymm15, %%ymm15, %%ymm15\n"
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

class AVXAddLatency : public IUbench {
public:
    AVXAddLatency() {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"

            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"

            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"

            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
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

class AVXAddThroughput : public IUbench {
public:
    AVXAddThroughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm1, %%ymm1, %%ymm1\n"
            "vaddps %%ymm2, %%ymm2, %%ymm2\n"
            "vaddps %%ymm3, %%ymm3, %%ymm3\n"

            "vaddps %%ymm4, %%ymm4, %%ymm4\n"
            "vaddps %%ymm5, %%ymm5, %%ymm5\n"
            "vaddps %%ymm6, %%ymm6, %%ymm6\n"
            "vaddps %%ymm7, %%ymm7, %%ymm7\n"

            "vaddps %%ymm8, %%ymm8, %%ymm8\n"
            "vaddps %%ymm9, %%ymm9, %%ymm9\n"
            "vaddps %%ymm10, %%ymm10, %%ymm10\n"
            "vaddps %%ymm11, %%ymm11, %%ymm11\n"

            "vaddps %%ymm12, %%ymm12, %%ymm12\n"
            "vaddps %%ymm13, %%ymm13, %%ymm13\n"
            "vaddps %%ymm14, %%ymm14, %%ymm14\n"
            "vaddps %%ymm15, %%ymm15, %%ymm15\n"
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

class AVXMulAddIndepenDepth4Throughput : public IUbench {
public:
    AVXMulAddIndepenDepth4Throughput() {
        instruction_count_ = _1G() / 20 * 8;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm1, %%ymm1, %%ymm1\n"
            "vmulps %%ymm2, %%ymm2, %%ymm2\n"
            "vmulps %%ymm3, %%ymm3, %%ymm3\n"

            "vaddps %%ymm4, %%ymm4, %%ymm4\n"
            "vaddps %%ymm5, %%ymm5, %%ymm5\n"
            "vaddps %%ymm6, %%ymm6, %%ymm6\n"
            "vaddps %%ymm7, %%ymm7, %%ymm7\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 8 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class AVXMulAddDepenDepth4Throughput : public IUbench {
public:
    AVXMulAddDepenDepth4Throughput() {
        instruction_count_ = _1G() / 20 * 8;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm1, %%ymm1, %%ymm1\n"
            "vmulps %%ymm2, %%ymm2, %%ymm2\n"
            "vmulps %%ymm3, %%ymm3, %%ymm3\n"

            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm1, %%ymm1, %%ymm1\n"
            "vaddps %%ymm2, %%ymm2, %%ymm2\n"
            "vaddps %%ymm3, %%ymm3, %%ymm3\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 8 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class AVXMulAddDepenDepth6Throughput : public IUbench {
public:
    AVXMulAddDepenDepth6Throughput() {
        instruction_count_ = _1G() / 20 * 12;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm1, %%ymm1, %%ymm1\n"
            "vmulps %%ymm2, %%ymm2, %%ymm2\n"
            "vmulps %%ymm3, %%ymm3, %%ymm3\n"

            "vmulps %%ymm4, %%ymm4, %%ymm4\n"
            "vmulps %%ymm5, %%ymm5, %%ymm5\n"

            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm1, %%ymm1, %%ymm1\n"
            "vaddps %%ymm2, %%ymm2, %%ymm2\n"
            "vaddps %%ymm3, %%ymm3, %%ymm3\n"

            "vaddps %%ymm4, %%ymm4, %%ymm4\n"
            "vaddps %%ymm5, %%ymm5, %%ymm5\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 12 / 10)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };
};

class AVXMulAddDepenDepth8Throughput : public IUbench {
public:
    AVXMulAddDepenDepth8Throughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm1, %%ymm1, %%ymm1\n"
            "vmulps %%ymm2, %%ymm2, %%ymm2\n"
            "vmulps %%ymm3, %%ymm3, %%ymm3\n"

            "vmulps %%ymm4, %%ymm4, %%ymm4\n"
            "vmulps %%ymm5, %%ymm5, %%ymm5\n"
            "vmulps %%ymm6, %%ymm6, %%ymm6\n"
            "vmulps %%ymm7, %%ymm7, %%ymm7\n"

            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm1, %%ymm1, %%ymm1\n"
            "vaddps %%ymm2, %%ymm2, %%ymm2\n"
            "vaddps %%ymm3, %%ymm3, %%ymm3\n"

            "vaddps %%ymm4, %%ymm4, %%ymm4\n"
            "vaddps %%ymm5, %%ymm5, %%ymm5\n"
            "vaddps %%ymm6, %%ymm6, %%ymm6\n"
            "vaddps %%ymm7, %%ymm7, %%ymm7\n"
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

class AVXMulAddIndepenDepth8Throughput : public IUbench {
public:
    AVXMulAddIndepenDepth8Throughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm1, %%ymm1, %%ymm1\n"
            "vmulps %%ymm2, %%ymm2, %%ymm2\n"
            "vmulps %%ymm3, %%ymm3, %%ymm3\n"

            "vmulps %%ymm4, %%ymm4, %%ymm4\n"
            "vmulps %%ymm5, %%ymm5, %%ymm5\n"
            "vmulps %%ymm6, %%ymm6, %%ymm6\n"
            "vmulps %%ymm7, %%ymm7, %%ymm7\n"

            "vaddps %%ymm8, %%ymm8, %%ymm8\n"
            "vaddps %%ymm9, %%ymm9, %%ymm9\n"
            "vaddps %%ymm10, %%ymm10, %%ymm10\n"
            "vaddps %%ymm11, %%ymm11, %%ymm11\n"

            "vaddps %%ymm12, %%ymm12, %%ymm12\n"
            "vaddps %%ymm13, %%ymm13, %%ymm13\n"
            "vaddps %%ymm14, %%ymm14, %%ymm14\n"
            "vaddps %%ymm15, %%ymm15, %%ymm15\n"
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

class AVXMulAddDepenDepth10Throughput : public IUbench {
public:
    AVXMulAddDepenDepth10Throughput() {
        instruction_count_ = _1G() / 20 * 20;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm1, %%ymm1, %%ymm1\n"
            "vmulps %%ymm2, %%ymm2, %%ymm2\n"
            "vmulps %%ymm3, %%ymm3, %%ymm3\n"

            "vmulps %%ymm4, %%ymm4, %%ymm4\n"
            "vmulps %%ymm5, %%ymm5, %%ymm5\n"
            "vmulps %%ymm6, %%ymm6, %%ymm6\n"
            "vmulps %%ymm7, %%ymm7, %%ymm7\n"

            "vmulps %%ymm8, %%ymm8, %%ymm8\n"
            "vmulps %%ymm9, %%ymm9, %%ymm9\n"

            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm1, %%ymm1, %%ymm1\n"
            "vaddps %%ymm2, %%ymm2, %%ymm2\n"
            "vaddps %%ymm3, %%ymm3, %%ymm3\n"

            "vaddps %%ymm4, %%ymm4, %%ymm4\n"
            "vaddps %%ymm5, %%ymm5, %%ymm5\n"
            "vaddps %%ymm6, %%ymm6, %%ymm6\n"
            "vaddps %%ymm7, %%ymm7, %%ymm7\n"

            "vaddps %%ymm8, %%ymm8, %%ymm8\n"
            "vaddps %%ymm9, %%ymm9, %%ymm9\n"
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

class AVXMulAddDepenDepth12Throughput : public IUbench {
public:
    AVXMulAddDepenDepth12Throughput() {
        instruction_count_ = _1G() / 20 * 24;
        ops_count_ = instruction_count_ * 8;
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rept 10\n"
            "vmulps %%ymm0, %%ymm0, %%ymm0\n"
            "vmulps %%ymm1, %%ymm1, %%ymm1\n"
            "vmulps %%ymm2, %%ymm2, %%ymm2\n"
            "vmulps %%ymm3, %%ymm3, %%ymm3\n"

            "vmulps %%ymm4, %%ymm4, %%ymm4\n"
            "vmulps %%ymm5, %%ymm5, %%ymm5\n"
            "vmulps %%ymm6, %%ymm6, %%ymm6\n"
            "vmulps %%ymm7, %%ymm7, %%ymm7\n"

            "vmulps %%ymm8, %%ymm8, %%ymm8\n"
            "vmulps %%ymm9, %%ymm9, %%ymm9\n"
            "vmulps %%ymm10, %%ymm10, %%ymm10\n"
            "vmulps %%ymm11, %%ymm11, %%ymm11\n"

            "vaddps %%ymm0, %%ymm0, %%ymm0\n"
            "vaddps %%ymm1, %%ymm1, %%ymm1\n"
            "vaddps %%ymm2, %%ymm2, %%ymm2\n"
            "vaddps %%ymm3, %%ymm3, %%ymm3\n"

            "vaddps %%ymm4, %%ymm4, %%ymm4\n"
            "vaddps %%ymm5, %%ymm5, %%ymm5\n"
            "vaddps %%ymm6, %%ymm6, %%ymm6\n"
            "vaddps %%ymm7, %%ymm7, %%ymm7\n"

            "vaddps %%ymm8, %%ymm8, %%ymm8\n"
            "vaddps %%ymm9, %%ymm9, %%ymm9\n"
            "vaddps %%ymm10, %%ymm10, %%ymm10\n"
            "vaddps %%ymm11, %%ymm11, %%ymm11\n"
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

class AVXGemmNoAThroughput : public IUbench {
public:
    AVXGemmNoAThroughput() {
        instruction_count_ = _1G() / 20 * 24;
        ops_count_ = instruction_count_ * 8;
        memset(B_, 0, sizeof(B_));
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "vmovups 0(%[B]), %%ymm14\n"
            "vmovups 32(%[B]), %%ymm15\n"

            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm0, %%ymm0\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm1, %%ymm1\n"

            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm2, %%ymm2\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm3, %%ymm3\n"

            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm4, %%ymm4\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm5, %%ymm5\n"

            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm6, %%ymm6\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm7, %%ymm7\n"

            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm8, %%ymm8\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm9, %%ymm9\n"

            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm10, %%ymm10\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm11, %%ymm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10),
            [B]    "r" (B_)
            :
            "cc", "memory",
            "ymm0" , "ymm1" , "ymm2" , "ymm3" , "ymm4" , "ymm5" , "ymm6" , "ymm7" ,
            "ymm8" , "ymm9" , "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"
        );
    };

    char B_[2 * 8 * sizeof(float)] __attribute__ ((aligned(64)));
};

class AVXGemmM6N16Throughput : public IUbench {
public:
    AVXGemmM6N16Throughput() {
        instruction_count_ = _1G() / 20 * 24;
        ops_count_ = instruction_count_ * 8;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "vmovups 0(%[B]), %%ymm14\n"
            "vmovups 32(%[B]), %%ymm15\n"

            "vbroadcastss 0(%[A]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm0, %%ymm0\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm1, %%ymm1\n"

            "vbroadcastss 4(%[A]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm2, %%ymm2\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm3, %%ymm3\n"

            "vbroadcastss 8(%[A]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm4, %%ymm4\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm5, %%ymm5\n"

            "vbroadcastss 12(%[A]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm6, %%ymm6\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm7, %%ymm7\n"

            "vbroadcastss 16(%[A]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm8, %%ymm8\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm9, %%ymm9\n"

            "vbroadcastss 20(%[A]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm10, %%ymm10\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm11, %%ymm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10),
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

class AVXGemmM2N48Throughput : public IUbench {
public:
    AVXGemmM2N48Throughput() {
        instruction_count_ = _1G() / 20 * 24;
        ops_count_ = instruction_count_ * 8;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));
    };
private:
    void BenchImpl() override {
        __asm__ __volatile__ (
            YMM_INIT()
            "1:\n"
            "sub $1, %[LOOP]\n"
            ".rep 10\n"
            "vbroadcastss 0(%[A]), %%ymm14\n"
            "vbroadcastss 4(%[A]), %%ymm15\n"

            "vmovups 0(%[B]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm0, %%ymm0\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm1, %%ymm1\n"

            "vmovups 32(%[B]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm2, %%ymm2\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm3, %%ymm3\n"

            "vmovups 64(%[B]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm4, %%ymm4\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm5, %%ymm5\n"

            "vmovups 96(%[B]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm6, %%ymm6\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm7, %%ymm7\n"

            "vmovups 128(%[B]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm8, %%ymm8\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm9, %%ymm9\n"

            "vmovups 160(%[B]), %%ymm12\n"
            "vmulps %%ymm12, %%ymm14, %%ymm13\n"
            "vaddps %%ymm13, %%ymm10, %%ymm10\n"
            "vmulps %%ymm12, %%ymm15, %%ymm13\n"
            "vaddps %%ymm13, %%ymm11, %%ymm11\n"
            ".endr\n"
            "jne 1b\n"
            :
            :
            [LOOP] "r" (instruction_count_ / 24 / 10),
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
    std::pair<const char*, IUbench*> lat_list[] = {
        {"AVX Mul Latency                   : %.3f ns\n", new AVXMulLatency},
        {"AVX Add Latency                   : %.3f ns\n", new AVXAddLatency},
    };
    std::pair<const char*, IUbench*> tp_list[] {
        {"AVX Mul Throughput                : %.3f /ns,\t GFLOPs: %.3f\n", new AVXMulThroughput},
        {"AVX Add Throughput                : %.3f /ns,\t GFLOPs: %.3f\n", new AVXAddThroughput},
        {"AVX 4x  Mul-Add w/o Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new AVXMulAddIndepenDepth4Throughput},
        {"AVX 4x  Mul-Add w/  Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new AVXMulAddDepenDepth4Throughput},
        {"AVX 6x  Mul-Add w/  Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new AVXMulAddDepenDepth6Throughput},
        {"AVX 8x  Mul-Add w/o Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new AVXMulAddIndepenDepth8Throughput},
        {"AVX 8x  Mul-Add w/  Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new AVXMulAddDepenDepth8Throughput},
        {"AVX 10x Mul-Add w/  Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new AVXMulAddDepenDepth10Throughput},
        {"AVX 12x Mul-Add w/  Dep Throughput: %.3f /ns,\t GFLOPs: %.3f\n", new AVXMulAddDepenDepth12Throughput},
        {"AVX Gemm w/o A Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new AVXGemmNoAThroughput},
        {"AVX Gemm M6N16 Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new AVXGemmM6N16Throughput},
        {"AVX Gemm M2N48 Mul-Add Throughput : %.3f /ns,\t GFLOPs: %.3f\n", new AVXGemmM2N48Throughput},
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
