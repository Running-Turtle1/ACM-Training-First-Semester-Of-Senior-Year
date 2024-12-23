### 题目链接

[E - Random Swaps of Balls (atcoder.jp)](https://atcoder.jp/contests/abc360/tasks/abc360_e)

## Statements

## Problem Statement

There are $N - 1$ white balls and one black ball. These $N$ balls are arranged in a row, with the black ball initially at the leftmost position.

Takahashi will perform the following operation exactly $K$ times.

- Choose an integer uniformly at random between $1$ and $N$, inclusive, twice. Let $a$ and $b$ the chosen integers. If $a \neq b$, swap the $a$\-th and $b$\-th balls from the left.

After $K$ operations, let the black ball be at the $x$\-th position from the left. Find the expected value of $x$, modulo $998244353$.

## Solution

设 $dp_{i,j}$ 表示第 $i$ 轮黑球位于位置 $j$ 的概率

根据期望定义 ：$res=\sum_{i=1}^N dp_{i,j}*i$ 

发现 2 ~ N 其实是没有区别的位置，即 ：

$dp_{k,2}=dp_{k,3}=\cdots=dp_{k,N}$ 

所以 ：
$res=dp_{k,2}*\sum_{i=2}^N i+dp_{k,1}$ 

求 $dp_{k,2}$ 可以递推 ： 

设 $\lambda$ 为黑球保持不变的概率，多少我忘了

这一轮位于 x =上一轮位于 x * 保持 +  上一轮不位于 * 交换

公式我也懒得写了

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 998244353;

int ksm(int a, int k, int p){
    int res = 1;
    a %= p;
    while(k){
        if(k & 1) res = res * a % p;
        k >>= 1;
        a = a * a % p;
    }
    return res;
}
int inv(int x){
    x %= mod;
    return ksm(x, mod - 2, mod);
}
int n, k;
void solve(){
    cin >> n >> k;
    int p = 2LL * inv(n * n) % mod;
    for(int i = 2; i <= k; i ++){
        int t1 = 2LL * inv(n * n) % mod;
        int t2 = ((n * n % mod - 2 * n) % mod + mod) % mod;
        t2 = t2 * inv(n * n) % mod;
        p = (t1 + t2 * p % mod) % mod;
    }
    int res = 0; 
    int tmp = ((n * (n + 1) % mod * inv(2LL) - 1) % mod + mod) % mod;
    res = tmp * p % mod; 

    (p = (n * n % mod - 2 * n + 2) % mod + mod) %= mod;
    p = p * inv(n * n) % mod;
    for(int i = 2; i <= k; i ++){
        int t1 = 2LL * inv(n * n) % mod;
        int t2 = ((n * n % mod - 2 * n) % mod + mod) % mod;
        t2 = t2 * inv(n * n) % mod;
        p = (t1 + t2 * p % mod) % mod;
    } 
    (res += p) %= mod;
    cout << res << '\n'; 
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```
