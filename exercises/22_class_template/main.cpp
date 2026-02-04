#include "../exercise.h"
#include <cstring>

template<class T>
struct Tensor4D {
    unsigned int shape[4];
    T *data;

    Tensor4D(unsigned int const shape_[4], T const *data_) {
        unsigned int size = 1;
        // TODO: 填入正确的 shape 并计算 size（原逻辑正确，无需修改）
        for (int i = 0; i < 4; ++i) {
            shape[i] = shape_[i];
            size *= shape[i];
        }
        data = new T[size];
        std::memcpy(data, data_, size * sizeof(T));
    }

    ~Tensor4D() {
        delete[] data;
    }

    // 禁止复制和移动，避免浅拷贝内存错误
    Tensor4D(Tensor4D const &) = delete;
    Tensor4D(Tensor4D &&) noexcept = delete;

    // 实现单向广播加法：others形状不同的维度长度必须为1，该维度广播取0号索引
    Tensor4D &operator+=(Tensor4D const &others) {
        // 计算当前张量的各维度步长（行优先，从后往前算）
        unsigned int strides[4];
        strides[3] = 1;
        for (int i = 2; i >= 0; --i) {
            strides[i] = strides[i + 1] * shape[i + 1];
        }
        // 计算others张量的各维度步长
        unsigned int other_strides[4];
        other_strides[3] = 1;
        for (int i = 2; i >= 0; --i) {
            other_strides[i] = other_strides[i + 1] * others.shape[i + 1];
        }

        // 四重循环遍历当前张量的所有4维索引（i:0维, j:1维, k:2维, l:3维）
        for (unsigned int i = 0; i < shape[0]; ++i) {
            for (unsigned int j = 0; j < shape[1]; ++j) {
                for (unsigned int k = 0; k < shape[2]; ++k) {
                    for (unsigned int l = 0; l < shape[3]; ++l) {
                        // 计算当前张量的一维偏移索引
                        unsigned int idx = i * strides[0] + j * strides[1] + k * strides[2] + l * strides[3];
                        
                        // 核心修正：广播索引计算（others维度长度为1时，取0，否则取与当前张量相同的索引）
                        unsigned int oi = (others.shape[0] == 1) ? 0 : i;
                        unsigned int oj = (others.shape[1] == 1) ? 0 : j;
                        unsigned int ok = (others.shape[2] == 1) ? 0 : k;
                        unsigned int ol = (others.shape[3] == 1) ? 0 : l;
                        
                        // 计算others张量对应的一维偏移索引
                        unsigned int o_idx = oi * other_strides[0] + oj * other_strides[1] + ok * other_strides[2] + ol * other_strides[3];
                        
                        // 广播加法：当前元素 += others对应广播元素
                        data[idx] += others.data[o_idx];
                    }
                }
            }
        }
        return *this;
    }
};

// ---- 仅修改模板实例化部分，其余代码不变 ----
int main(int argc, char **argv) {
    {
        unsigned int shape[]{1, 2, 3, 4};
        int data[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,
            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        // 修正：显式指定模板参数int
        auto t0 = Tensor4D<int>(shape, data);
        auto t1 = Tensor4D<int>(shape, data);
        t0 += t1;
        for (auto i = 0u; i < sizeof(data) / sizeof(*data); ++i) {
            ASSERT(t0.data[i] == data[i] * 2, "Tensor doubled by plus its self.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        float d0[]{
            1, 1, 1, 1,
            2, 2, 2, 2,
            3, 3, 3, 3,
            4, 4, 4, 4,
            5, 5, 5, 5,
            6, 6, 6, 6};
        unsigned int s1[]{1, 2, 3, 1};
        float d1[]{6,5,4,3,2,1};
        // 修正：显式指定模板参数float
        auto t0 = Tensor4D<float>(s0, d0);
        auto t1 = Tensor4D<float>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == 7.f, "Every element of t0 should be 7 after adding t1 to it.");
        }
    }
    {
        unsigned int s0[]{1, 2, 3, 4};
        double d0[]{
             1,  2,  3,  4,
             5,  6,  7,  8,
             9, 10, 11, 12,
            13, 14, 15, 16,
            17, 18, 19, 20,
            21, 22, 23, 24};
        unsigned int s1[]{1, 1, 1, 1};
        double d1[]{1};
        // 修正：显式指定模板参数double
        auto t0 = Tensor4D<double>(s0, d0);
        auto t1 = Tensor4D<double>(s1, d1);
        t0 += t1;
        for (auto i = 0u; i < sizeof(d0) / sizeof(*d0); ++i) {
            ASSERT(t0.data[i] == d0[i] + 1, "Every element of t0 should be incremented by 1 after adding t1 to it.");
        }
    }
    return 0;
}