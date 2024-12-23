#include<iostream>
using namespace std;

template<typename Type>
void Swap(Type &a, Type & b)
{
	Type tem = a;
	a = b;
	b = tem;
	cout << "Type:" << typeid(Type).name()<<"   ";
}
int main()
{
	int a = 2;
	double b = 1.0;
	swap(a, b);
}
