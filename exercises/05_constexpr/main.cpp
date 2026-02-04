#include "../exercise.h"

constexpr unsigned long long fibonacci(int i) {
    if (i <= 0) return 0;  // 处理i=0的情况
    if (i == 1) return 1;  // 处理i=1的情况
    unsigned long long a = 0, b = 1, res;  // 初始化前两项
    for (int n = 2; n <= i; ++n) {         // 从第2项迭代到第i项
        res = a + b;
        a = b;
        b = res;
    }
    return res;
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // 仅修改此处：移除ANS前的constexpr，改为运行期计算
    constexpr auto ANS_N = 90;
    auto ANS = fibonacci(90); // 关键修改：去掉constexpr
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}