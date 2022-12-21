#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>

#include "xbyak/xbyak.h"
#include "iubench.h"

typedef void(*jit_ker_t)(int64_t*);

// from oneDNN
Xbyak::Operand::Code abi_save_gpr_regs[] = {
        Xbyak::Operand::RBP,
        Xbyak::Operand::R15,
        Xbyak::Operand::R14,
        Xbyak::Operand::R13,
        Xbyak::Operand::R12,
        Xbyak::Operand::RBX,
#ifdef _WIN32
        Xbyak::Operand::RDI,
        Xbyak::Operand::RSI,
#endif
};

Xbyak::Operand::Code abi_param_regs[] = {
#ifdef _WIN32
        Xbyak::Operand::RCX, Xbyak::Operand::RDX, Xbyak::Operand::R8,
        Xbyak::Operand::R9
#else
        Xbyak::Operand::RDI, Xbyak::Operand::RSI, Xbyak::Operand::RDX,
        Xbyak::Operand::RCX, Xbyak::Operand::R8, Xbyak::Operand::R9
#endif
};

class jit_base : public Xbyak::MmapAllocator, public Xbyak::CodeGenerator {
private:
    const uint32_t xmm_len_ = 16;
#ifdef _WIN32
    const uint32_t xmm_to_preserve_start_ = 6;
    const uint32_t xmm_to_preserve_ = 10;
#else
    const uint32_t xmm_to_preserve_start_ = 0;
    const uint32_t xmm_to_preserve_ = 0;
#endif

    const uint32_t num_abi_save_gpr_regs_
            = sizeof(abi_save_gpr_regs) / sizeof(abi_save_gpr_regs[0]);

    const uint32_t size_of_abi_save_regs_
            = num_abi_save_gpr_regs_ * rax.getBit() / 8
            + xmm_to_preserve_ * xmm_len_;

    const int sse_only_ = false;

public:
    void preamble() {
        for (uint32_t i = 0; i < num_abi_save_gpr_regs_; ++i)
            push(Xbyak::Reg64(abi_save_gpr_regs[i]));
        // enable some backtrace
        mov(rbp, rsp);
        if (xmm_to_preserve_) {
            sub(rsp, xmm_to_preserve_ * xmm_len_);
            for (uint32_t i = 0; i < xmm_to_preserve_; ++i) {
                if (sse_only_)
                    movdqu(ptr[rsp + i * xmm_len_], Xbyak::Xmm(xmm_to_preserve_start_ + i));
                else
                    vmovdqu(ptr[rsp + i * xmm_len_], Xbyak::Xmm(xmm_to_preserve_start_ + i));
            }
        }
#ifdef _WIN32
        mov(uni_param_ptr_reg_, Xbyak::Reg64(abi_param_regs[0]));
#endif
    }

    void postamble() {
        if (!sse_only_)
            vzeroupper();
        if (xmm_to_preserve_) {
            for (uint32_t i = 0; i < xmm_to_preserve_; ++i) {
                if (sse_only_)
                    movdqu(Xbyak::Xmm(xmm_to_preserve_start_ + i), ptr[rsp + i * xmm_len_]);
                else
                    vmovdqu(Xbyak::Xmm(xmm_to_preserve_start_ + i), ptr[rsp + i * xmm_len_]);
            }
            add(rsp, xmm_to_preserve_ * xmm_len_);
        }
        for (uint32_t i = 0; i < num_abi_save_gpr_regs_; ++i)
            pop(Xbyak::Reg64(abi_save_gpr_regs[num_abi_save_gpr_regs_ - 1 - i]));
        ret();
    }

    jit_base(int sse_only = false, void *code_ptr = nullptr, size_t code_size = 256 * 1024, bool use_autogrow = true)
        : sse_only_(sse_only)
        , Xbyak::CodeGenerator(code_size, (code_ptr == nullptr && use_autogrow) ? Xbyak::AutoGrow : code_ptr, this) {}

    virtual ~jit_base() {}

    const jit_ker_t jit_ker() const { return jit_ker_; }

    inline void operator()(int64_t *param_array) const {
        jit_ker_(param_array);
    }

    virtual bool create_kernel() {
        generate();
        jit_ker_ = getCode();
        return !!jit_ker_;
    }

private:
    const jit_ker_t getCode() {
        this->ready();
        if (!is_initialized()) return nullptr;
        const jit_ker_t code = CodeGenerator::getCode<jit_ker_t>();
        return code;
    }

    static inline bool is_initialized() {
        return Xbyak::GetError() == Xbyak::ERR_NONE;
    }

protected:
    virtual void generate() = 0;

    jit_ker_t jit_ker_ = nullptr;

    const Xbyak::Reg64 uni_param_ptr_reg_ = Xbyak::Reg64(Xbyak::Operand::RDI);
};

class SSEMulLatency : public IUbench, public jit_base {
public:
    SSEMulLatency() : jit_base(true) {
        instruction_count_ = _1G() / 40 * 16;
        ops_count_ = instruction_count_ * 4;
        create_kernel();
    }
private:
    void BenchImpl() override {
        jit_ker_(&instruction_count_);
    }

    void generate() override {
        preamble();

        mov(rax, ptr[uni_param_ptr_reg_]);
        pxor(xmm0, xmm0);

        Xbyak::Label inner_loop;
        L(inner_loop);
        sub(rax, 10 * 16);
        for (int32_t i = 0; i < 10 * 16; ++i)
            mulps(xmm0, xmm0);
        jne(inner_loop, T_NEAR);

        postamble();
    }
};

class SSEMulThroughput : public IUbench, public jit_base {
public:
    SSEMulThroughput() : jit_base(true) {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 4;
        create_kernel();
    }
private:
    void BenchImpl() override {
        jit_ker_(&instruction_count_);
    }

    void generate() override {
        Xbyak::Xmm xms[16] = {
            xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7,
            xmm8, xmm9, xmm10, xmm11, xmm12, xmm13, xmm14, xmm15,
        };

        preamble();
        mov(rax, ptr[uni_param_ptr_reg_]);
        for (auto x : xms)
            pxor(x, x);

        Xbyak::Label inner_loop;
        L(inner_loop);
        sub(rax, 10 * 16);
        for (int32_t i = 0; i < 10; ++i) {
            for (auto x : xms)
                mulps(x, x);
        }
        jne(inner_loop, T_NEAR);

        postamble();
    }
};

class FMAMacThroughput : public IUbench, public jit_base {
public:
    FMAMacThroughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 16;
        create_kernel();
    }
private:
    void BenchImpl() override {
        jit_ker_(&instruction_count_);
    }

    void generate() override {
        Xbyak::Ymm yms[16] = {
            ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7,
            ymm8, ymm9, ymm10, ymm11, ymm12, ymm13, ymm14, ymm15,
        };

        preamble();
        mov(rax, ptr[uni_param_ptr_reg_]);
        for (auto y : yms)
            vxorps(y, y);

        Xbyak::Label inner_loop;
        L(inner_loop);
        sub(rax, 10 * 16);
        for (int32_t i = 0; i < 10; ++i) {
            for (auto y : yms)
                vfmadd231ps(y, y, y);
        }
        jne(inner_loop, T_NEAR);

        postamble();
    }
};

class FMAGemmM6N16Throughput : public IUbench, public jit_base {
public:
    FMAGemmM6N16Throughput() {
        instruction_count_ = _1G() / 20 * 12;
        ops_count_ = instruction_count_ * 16;
        memset(B_, 0, sizeof(B_));
        memset(A_, 0, sizeof(A_));

        create_kernel();

        param[0] = instruction_count_;
        *((char**)(param + 1)) = A_;
        *((char**)(param + 2)) = B_;
    }
private:
    void BenchImpl() override {
        jit_ker_(param);
    }

    void generate() override {
        Xbyak::Ymm yms[16] = {
            ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7,
            ymm8, ymm9, ymm10, ymm11, ymm12, ymm13, ymm14, ymm15,
        };

        preamble();
        mov(rax, ptr[uni_param_ptr_reg_ + 0]);
        mov(rbx, ptr[uni_param_ptr_reg_ + 8]);
        mov(rcx, ptr[uni_param_ptr_reg_ + 16]);
        for (auto y : yms)
            vxorps(y, y);

        Xbyak::Label inner_loop;
        L(inner_loop);
        sub(rax, 10 * 12);
        for (int32_t i = 0; i < 10; ++i) {
            vmovups(yms[14], ptr[rcx + 0]);
            vmovups(yms[15], ptr[rcx + 32]);
            for (int j = 0; j < 6; ++j) {
                vbroadcastss(yms[12], ptr[rbx + 4 * j]);
                vfmadd231ps(yms[j * 2 + 0], yms[12], yms[14]);
                vfmadd231ps(yms[j * 2 + 1], yms[12], yms[15]);
            }
        }
        jne(inner_loop, T_NEAR);

        postamble();
    }

    int64_t param[3];
    char B_[2 * 8 * sizeof(float)] __attribute__ ((aligned(64)));
    char A_[6 * sizeof(float)] __attribute__ ((aligned(64)));
};

class AVX512MacThroughput : public IUbench, public jit_base {
public:
    AVX512MacThroughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 32;
        create_kernel();
    }
private:
    void BenchImpl() override {
        jit_ker_(&instruction_count_);
    }

    void generate() override {
        Xbyak::Zmm zms[16] = {
            zmm0, zmm1, zmm2, zmm3, zmm4, zmm5, zmm6, zmm7,
            zmm8, zmm9, zmm10, zmm11, zmm12, zmm13, zmm14, zmm15,
        };

        preamble();
        mov(rax, ptr[uni_param_ptr_reg_]);
        for (auto z : zms)
            vpxord(z, z, z);

        Xbyak::Label inner_loop;
        L(inner_loop);
        sub(rax, 10 * 16);
        for (int32_t i = 0; i < 10; ++i) {
            for (auto z : zms)
                vfmadd231ps(z, z, z);
        }
        jne(inner_loop, T_NEAR);

        postamble();
    }
};

class AVX512VNNIThroughput : public IUbench, public jit_base {
public:
    AVX512VNNIThroughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 32 * 4;
        create_kernel();
    }
private:
    void BenchImpl() override {
        jit_ker_(&instruction_count_);
    }

    void generate() override {
        Xbyak::Zmm zms[16] = {
            zmm0, zmm1, zmm2, zmm3, zmm4, zmm5, zmm6, zmm7,
            zmm8, zmm9, zmm10, zmm11, zmm12, zmm13, zmm14, zmm15,
        };

        preamble();
        mov(rax, ptr[uni_param_ptr_reg_]);
        for (auto z : zms)
            vpxord(z, z, z);

        Xbyak::Label inner_loop;
        L(inner_loop);
        sub(rax, 10 * 16);
        for (int32_t i = 0; i < 10; ++i) {
            for (auto z : zms)
                vpdpbusds(z, z, z);
        }
        jne(inner_loop, T_NEAR);

        postamble();
    }
};

class AVXVNNIThroughput : public IUbench, public jit_base {
public:
    AVXVNNIThroughput() {
        instruction_count_ = _1G() / 20 * 16;
        ops_count_ = instruction_count_ * 16 * 4;
        create_kernel();
#ifdef DUMP_JIT
        // cmd: objdump -D -b binary -mi386:x86-6 avx_vnni_tp.obj
        FILE *fp = fopen("avx_vnni_tp.obj", "wb");
        if (fp) {
            fwrite((const void*)jit_ker_, getSize(), 1, fp);
            fclose(fp);
        }
#endif
    }
private:
    void BenchImpl() override {
        jit_ker_(&instruction_count_);
    }

    void generate() override {
        Xbyak::Ymm yms[16] = {
            ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6, ymm7,
            ymm8, ymm9, ymm10, ymm11, ymm12, ymm13, ymm14, ymm15,
        };

        preamble();
        mov(rax, ptr[uni_param_ptr_reg_]);
        for (auto y : yms)
            vxorps(y, y);

        Xbyak::Label inner_loop;
        L(inner_loop);
        sub(rax, 10 * 16);
        for (int32_t i = 0; i < 10; ++i) {
            for (auto y : yms)
                vpdpbusds(y, y, y, Xbyak::VexEncoding);
        }
        jne(inner_loop, T_NEAR);

        postamble();
    }
};

int main(int argc, const char **argv) {
    std::pair<const char*, IUbench*> lat_list[] = {
        {"SSE Mul Latency                   : %.3f ns\n", new SSEMulLatency},
    };

    std::pair<const char*, IUbench*> tp_list[] {
        {"SSE Mul Throughput                : %.3f /ns,\t GFLOPs: %.3f\n", new SSEMulThroughput},
        {"FMA Mac Throughput                : %.3f /ns,\t GFLOPs: %.3f\n", new FMAMacThroughput},
        {"FMA Gemm M6N16 Mac Throughput     : %.3f /ns,\t GFLOPs: %.3f\n", new FMAGemmM6N16Throughput},
        {"AVX512 Mac Throughput             : %.3f /ns,\t GFLOPs: %.3f\n", new AVX512MacThroughput},
        {"AVX512 VNNI Throughput            : %.3f /ns,\t GFLOPs: %.3f\n", new AVX512VNNIThroughput},
        {"AVX VNNI Throughput               : %.3f /ns,\t GFLOPs: %.3f\n", new AVXVNNIThroughput},
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
