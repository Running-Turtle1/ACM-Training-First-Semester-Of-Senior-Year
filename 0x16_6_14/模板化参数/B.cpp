#include<bits/stdc++.h>
using namespace std;
#define int long long

// template<typename... T>
// void fun1(T ...args)
// {
// 	cout << "Numbers of parameters: " << sizeof...(args) << endl; //打印变参的个数
// }

// signed main(){
// 	fun1();
// 	fun1(1, "");
// 	fun1(1, 2, 3, 4);
// 	fun1('a', 2, "abc", " ", 'w');

// 	return 0;
// }
//递归终结函数
void print()
{
	cout << "This is the end function" << endl;
}

//typename在简单的参数类型中使用
//typename...在可变参数的类型中使用
//比如下面，个人理解为：T1为普通参数类型，T2...为可变参数类型，即T2...是一个组合而不是...args
//注意可以看成两个类型，T1(普通参数)和T2...(可变参数)
template<typename T1, typename...T2>
void print(T1 head, T2...args)
{
	cout << head << endl;
	print(args...);//当参数输出完时，这个相当于print()，会调用终结函数print()
}


signed main()
{
	print(1, 2, 3, 4);

	return 0;
}
