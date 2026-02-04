#include "../exercise.h"
// 补全iostream头文件：原代码含std::cout，需显式引入（避免编译报错）
#include <iostream>

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>
// 类继承体系：A → B → C → D（公有继承），演示虚函数动态绑定/非虚函数静态绑定
struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    // override显式重写基类虚函数，编译器校验签名一致性
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    // final修饰虚函数：禁止后续派生类（如D）重写该函数
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    // 仅重写非虚函数direct_name，无法重写被final修饰的virtual_name
    char direct_name() const {
        return 'D';
    }
};

int main(int argc, char **argv) {
    // 优化断言提示语：从模糊的?改为精准描述，报错时更易定位问题
    constexpr auto MSG = "虚/非虚函数调用结果错误，检查绑定规则！";

    A a;
    B b;
    C c;
    D d;

    // 直接调用对象函数：无绑定，执行自身类型的函数版本
    ASSERT(a.virtual_name() == 'A', MSG);
    ASSERT(b.virtual_name() == 'B', MSG);
    ASSERT(c.virtual_name() == 'C', MSG);
    ASSERT(d.virtual_name() == 'C', MSG); // D继承C的final版virtual_name
    ASSERT(a.direct_name() == 'A', MSG);
    ASSERT(b.direct_name() == 'B', MSG);
    ASSERT(c.direct_name() == 'C', MSG);
    ASSERT(d.direct_name() == 'D', MSG);

    // 基类引用绑定派生类对象：核心多态演示
    A &rab = b;
    B &rbc = c;
    C &rcd = d;

    ASSERT(rab.virtual_name() == 'B', MSG);  // 虚函数：动态绑定→实际类型B
    ASSERT(rbc.virtual_name() == 'C', MSG);  // 虚函数：动态绑定→实际类型C
    ASSERT(rcd.virtual_name() == 'C', MSG);  // 虚函数：C::virtual_name被final修饰，D无法重写
    ASSERT(rab.direct_name() == 'A', MSG);   // 非虚函数：静态绑定→声明类型A
    ASSERT(rbc.direct_name() == 'B', MSG);   // 非虚函数：静态绑定→声明类型B
    ASSERT(rcd.direct_name() == 'C', MSG);   // 非虚函数：静态绑定→声明类型C

    A &rac = c;
    B &rbd = d;

    ASSERT(rac.virtual_name() == 'C', MSG);  // 虚函数：动态绑定→实际类型C
    ASSERT(rbd.virtual_name() == 'C', MSG);  // 虚函数：动态绑定→实际类型D（继承C的final版本）
    ASSERT(rac.direct_name() == 'A', MSG);   // 非虚函数：静态绑定→声明类型A
    ASSERT(rbd.direct_name() == 'B', MSG);   // 非虚函数：静态绑定→声明类型B

    A &rad = d;

    ASSERT(rad.virtual_name() == 'C', MSG);  // 虚函数：动态绑定→实际类型D（继承C的final版本）
    ASSERT(rad.direct_name() == 'A', MSG);   // 非虚函数：静态绑定→声明类型A

    // 新增：打印执行成功提示，验证代码运行完成
    std::cout << "所有断言通过！虚函数/非虚函数绑定规则验证成功！" << std::endl;
    return 0;
}