# Lambda Expressions

## 概览

Lambda表达式，又叫匿名函数，闭包 (Closure)

语法定义 : 

```cpp
[捕获列表] [参数列表] [可变规则] [返回类型] [函数体]
// [capture list] (parameters) mutable throw() -> return-type {statement}
```

1. 捕获列表。在C++规范中也称为Lambda导入器， 捕获列表总是出现在Lambda函数的开始处。实际上，`[]`是Lambda引出符。编译器根据该引出符判断接下来的代码是否是Lambda函数，捕获列表能够捕捉上下文中的变量以供Lambda函数使用。
2. 参数列表。与普通函数的参数列表一致。如果不需要参数传递，则可以连同括号“()”一起省略。
3. 可变规格。`mutable`修饰符， 默认情况下Lambda函数总是一个`const`函数，`mutable`可以取消其常量性。在使用该修饰符时，参数列表不可省略（即使参数为空）。
4. 异常说明。用于Lamdba表达式内部函数抛出异常。
5. 返回类型。 追踪返回类型形式声明函数的返回类型。我们可以在不需要返回值的时候也可以连同符号”->”一起省略。此外，在返回类型明确的情况下，也可以省略该部分，让编译器对返回类型进行推导。
6. lambda函数体。内容与普通函数一样，不过除了可以使用参数之外，还可以使用所有捕获的变量。

## 应用举例

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    auto f1 = [] {
        cout << "Lambda Expressions\n";
    };
    f1();

    auto x = 10;
    auto f2 = [x] {
        cout << x << '\n';
    };
    f2();
    auto f3 = [&x]{
        x = 20;
        cout << x << '\n';
    };
    f3();

    /* foreach 实例 */
    int a[4] = {1, 2, 3, 4};
    for_each(a, a + 4, [=](int x){
        cout << x << " ";
    });
    cout << '\n';

    return 0;
} 
/* 
    1. 捕获规则 :
    - [] 表示不捕获任何变量
    - [var] 表示以值传递形式捕获变量 var 
    - [&var] 表示引用传递捕获变量 var 
    - [=] 表示值传递捕获所有父作用域变量 (包括 this)
    - [&] 表示引用传递捕获所有父作用域变量 (包括 this)
    - [this] 表示值传递方式捕捉当前的 this 指针

    2. [=, &] 拷贝与引用混合
    - [=, &a, &b]表示以引用传递的方式捕捉变量a和b，以值传递方式捕捉其它所有变量。
    - [&, a, this]表示以值传递的方式捕捉变量a和this，引用传递方式捕捉其它所有变量。

    3. 捕捉列表不允许变量重复传递

*/ 
```

## 递归

`&&` 是右值应用

```cpp
auto fib = [] (auto fib, int n) -> int {
        if(n <= 2) return 1;
        return fib(fib, n - 1) + fib(fib, n - 2);
    };
    int st[3] = {0, 0, 0};
    int p[3] = {0, 1, 2};
    auto dfs = [] (auto &&dfs, int* p, int* st, int u) -> void {
        if(u == 3){
            for(int i = 0; i < 3; i ++){
                cout << p[i] << ' ';
            }
            cout << '\n';
            return ;
        }
        for(int i = 0; i < 3; i ++){
            if(st[i] == false){
                st[i] = true;
                p[u] = i;
                dfs(dfs, p, st, u + 1);
                st[i] = false;
            }
        }
    };
    dfs(dfs, p, st, 0);
```

实际按照如下这样写就可以，把 `auto` 改成对应类型。

`function<返回类型(参数列表)>` 

```cpp
void solve(){
    function<void(int)> dfs = [&] (int u) {
        cout << u << '\n';
        if(u == 5) return ;
        dfs(u + 1);
    };
    dfs(1);
}
```
