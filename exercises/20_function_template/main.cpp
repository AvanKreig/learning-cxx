#include "../exercise.h"
#include <cmath>

// READ: 函数模板 <https://zh.cppreference.com/w/cpp/language/function_template>
// TODO: 将这个函数模板化（修复命名冲突：plus → add）
template<typename T>
T add(T a, T b) {
    return a + b;
}

int main(int argc, char **argv) {
    // 所有调用统一替换为add，匹配模板名
    ASSERT(add(1, 2) == 3, "Plus two int");
    ASSERT(add(1u, 2u) == 3u, "Plus two unsigned int");

    // THINK: 浮点数何时可以判断 ==？何时必须判断差值？
    ASSERT(add(1.25f, 2.5f) == 3.75f, "Plus two float");
    ASSERT(add(1.25, 2.5) == 3.75, "Plus two double");
    // TODO: 修改判断条件使测试通过（浮点数精度兼容：差值绝对值 < 极小阈值）
    ASSERT(std::abs(add(0.1, 0.2) - 0.3) < 1e-10, "How to make this pass?");

    return 0;
}