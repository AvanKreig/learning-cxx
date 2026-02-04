#include "../exercise.h"

// 兼容C的枚举，无作用域，会污染命名空间
enum ColorEnum : unsigned char {
    COLOR_RED = 31,
    COLOR_GREEN,
    COLOR_YELLOW,
    COLOR_BLUE,
};

// C++类型安全枚举，有作用域，避免命名空间污染
enum class Color : int {
    Red = COLOR_RED,
    Green,
    Yellow,
    Blue,
};

ColorEnum convert_by_pun(Color c) {
    // 联合实现类型双关：所有成员共享内存，二进制值直接复用
    union TypePun {
        ColorEnum e;  // 目标类型：无作用域枚举
        Color c;      // 源类型：有作用域枚举
    };

    TypePun pun;
    // TODO: 补全类型双关转换
    pun.c = c;        // 第一步：将源类型Color的值存入联合的c成员
    return pun.e;     // 第二步：从联合的e成员读出，转为目标类型ColorEnum
}

// ---- 不要修改以下代码 ----
int main(int argc, char **argv) {
    ASSERT(convert_by_pun(Color::Red) == COLOR_RED, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Green) == COLOR_GREEN, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Yellow) == COLOR_YELLOW, "Type punning conversion");
    ASSERT(convert_by_pun(Color::Blue) == COLOR_BLUE, "Type punning conversion");
    return 0;
}