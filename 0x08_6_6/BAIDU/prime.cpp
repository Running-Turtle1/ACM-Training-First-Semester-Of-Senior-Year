#define _CRT_SECURE_NO_WARNINGS
#include<iostream>

using namespace std;

const int N = 1e6 + 10;

int cnt, pm[N];
bool st[N];
void getPrime(int n){
    for(int i = 2; i <= n; i ++){
        if(!st[i]) pm[cnt ++] = i;
        // 将 2~n 所有数的倍数都标记为合数
        for(int j = 2 * i; j <= n; j += i){
            st[j] = true;
        }
    }
}

void get_prime(int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (!st[i])
        {
            prime[cnt++] = i;
        }
        for (int j = 2 * i; j <= n; j += i) st[j] = true; 
    }
}
int main()
{
    int n;
    cin >> n;
    get_prime(n);
    cout << cnt << endl;
    return 0;
}

int cnt, pm[N];
bool st[N];
void getPrime(int n){
    for(int i = 2; i <= n; i ++){
        if(st[i]) continue;
        pm[cnt ++] = i;
        // 将 2~n 所有数的倍数都标记为合数
        for(int j = 2 * i; j <= n; j += i){
            st[j] = true;
        }
    }
}

int cnt, prim[N];
bool st[N]; // !st[i] 为质数
void get_prim(int n){
    for(int i = 2; i <= n; i ++){
        if(!st[i]) prim[cnt ++] = i;
        for(int j = 0; prim[j] <= n / i; j ++){
            st[prim[j] * i] = true;
            if(i % prim[j] == 0) break;
        }
    }
    st[1] = true;
}