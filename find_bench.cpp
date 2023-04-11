#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <random>
#include <vector>
#include <algorithm>

#include "iubench.h"

int binary_find_index_asc(int val, const int *val_arr, const int *index_arr, int length);

int linear_find_index_ooo(int val, const int *val_arr, int length);

class LinearFindLatency : public IUbench {
public:
    LinearFindLatency(int length) {
        instruction_count_ = 1;
        ops_count_ = 1;

        arr_.resize(length);

        for (int i = 0; i < length; ++i)
            arr_[i] = i;

        dis_ = std::uniform_int_distribution<int>(0, length - 1);

        std::random_shuffle(arr_.begin(), arr_.end());
    }

private:
    std::vector<int> arr_;
    std::uniform_int_distribution<int> dis_;
    std::default_random_engine eng_;

    void BenchImpl() override {
        int to_find = dis_(eng_);
        linear_find_index_ooo(to_find, arr_.data(), (int)arr_.size());
    }
};

class BinaryFindLatency : public IUbench {
public:
    BinaryFindLatency(int length) {
        instruction_count_ = 1;
        ops_count_ = 1;

        arr_.resize(length);

        for (int i = 0; i < length; ++i)
            arr_[i] = i;

        dis_ = std::uniform_int_distribution<int>(0, length - 1);

        std::random_shuffle(arr_.begin(), arr_.end());
        idx_.assign(arr_.begin(), arr_.end());
    }

private:
    std::vector<int> arr_;
    std::vector<int> idx_;
    std::uniform_int_distribution<int> dis_;
    std::default_random_engine eng_;

    void BenchImpl() override {
        int to_find = dis_(eng_);
        binary_find_index_asc(to_find, arr_.data(), idx_.data(), (int)arr_.size());
    }
};

int main(int argc, const char **argv) {
    for (int i = 1; i <= 20; ++i) {
        int length = 1 << i;
        auto lf = LinearFindLatency(length);
        auto bf = BinaryFindLatency(length);

        lf.Bench(100, 100000 * (i < 10 ? 20 : 1));
        bf.Bench(100, 100000 * (i < 10 ? 20 : 1));
        
        fprintf(stderr, "Element num 2^%-2d = %-7d        Linear: %-10.3f ns        Binary: %-10.3f ns\n",
            i, length, lf.CalNsPerInstruction(), bf.CalNsPerInstruction());
    };

    return 0;
}
