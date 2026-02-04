#include "../exercise.h"
#include <iostream>

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 缓存优化的斐波那契计算，含基线条件和非法输入校验
    unsigned long long get(int i) {
        // 校验输入合法性：索引不能为负，且不超过缓存数组长度
        ASSERT(i >= 0 && i < 128, "i must be in [0, 127]");
        // 基线条件：0和1直接返回缓存的初始值，无需计算
        if (i <= 1) return cache[i];
        // 仅计算未缓存的项，从当前cached到目标i，逐步填充缓存
        for (; cached <= i; ++cached) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
        }
        // 返回缓存中已计算好的结果
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 聚合初始化：直接初始化缓存基线值和已缓存标记，无冗余操作
    // cache[0]=0, cache[1]=1，其余cache元素默认值0；cached=2（表示已缓存0、1项，下一个计算项为2）
    Fibonacci fib{{0, 1}, 2};
    
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}