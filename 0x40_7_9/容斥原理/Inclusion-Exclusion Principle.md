# Inclusion-Exclusion Principle

## 集合的并

### 1. 两个集合的容斥原理公式

对于两个集合 $A$ 和 $B$：

$|A \cup B| = |A| + |B| - |A \cap B|$ 

### 2. 多个集合的容斥原理公式

对于 $n$ 个集合 \($A_1, A_2, \ldots, A_n$\)：

$
|A_1 \cup A_2 \cup \cdots \cup A_n| \\ = \sum_{i=1}^n |A_i| - \sum_{1 \le i < j \le n} |A_i \cap A_j| +   \sum_{1 \le i < j < k \le n} |A_i \cap A_j \cap A_k| - \cdots + \\ (-1)^{n+1} |A_1 \cap A_2 \cap \cdots \cap A_n|   \\  = \sum_{k=1}^n (-1)^{k+1} \left( \sum_{1 \le i_1 < i_2 < \cdots < i_k \le n} \left| A_{i_1} \cap A_{i_2} \cap \cdots \cap A_{i_k} \right| \right)
$

(奇正偶负)

## 集合的交

集合的交等于全集减去补集的并。

即满足所有条件的情况 = 所有情况 - 至少不满足某一条件的情况

$|\cap_{i=1}^n|=|U|-|\cup_{i=1}^n\overline{S_i}|$ 

## 例题

> 给定一个整数 $n$ 和 $m$ 个不同的质数 $p_0,p_2,\cdots,p_{m-1}$ , 求 $1\sim n$ 中能被 $p_0,p_2,\cdots,p_{m-1}$ 中的至少一个数整除的数有多少个 ? 其中 $m\leq 16$ , $n,p_i\leq 10^9$ 

使用二进制位来表示每个集合选与不选的状态。$S_1=001$ 表示能被 $p_0$ 整除的数的集合，$S_3=011$ 表示能被 $p_0,p_1$ 同时整除的数的集合。枚举所有状态进行容斥即可。

```cpp
int cal(){
    int res = 0;
    for(int i = 1; i < (1 << m); i ++){
        int t = 1, sign = -1;
        for(int j = 0; j < m; j ++){
            if(i >> j & 1){
                t *= prim[j];
                sign = -sign;
            }
        }
        if(t) res += n / t * sign;
    }
    return res;
}
```

## Example One

[F - x = a^b (atcoder.jp)](https://atcoder.jp/contests/abc361/tasks/abc361_f)

Think as the following steps, we can solve this problem.

hint1 : Que1 : calaulate how many numbers in 1 ~ N can be represented as $a^b$ 

hint2 : Let a = 1, $1^b\equiv 1$ ，so 1 is an answer certainly, then we let ans = 1, calcaulate how many numbers in 2 ~ N can be represented as $a^b$ 

hint3 : consider that $2^{60}>10^{18}$ , so b has a domain : $b\in[2,60)$ , so 2 ~ N can be only shown as $a^2,a^3,\cdots,a^{59}$ 

hint4 : For $a^b$ , if b can be arithmetically decomposed into $\geq 2$ elements, assuming $b=x*y$ , then $a^b=(a^x)^y$ . This kind of number will be counted in the answer when considering $a^y$ , so for exponents that can be decomposed into 2 or more elements, we can directly ignore them.

hint3 : Therefore, we only consider the prime numbers in the range [2, 60). Let these numbers be $p_0,p_1,\cdots,p_m$ , the corresponding answer sets are $s_0, s_1,\cdots,s_m$ . We can then apply the principle of inclusion-exclusion to these sets. 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

bool isPrime(int x){
    for(int i = 2; i <= x / i; i ++){
        if(x % i == 0) return false;
    }
    return true;
}
int n;
int cnt = 0;
vector<int> pm; // [2, 60] 内的质数
void init(){
    int cnt = 0;
    for(int i = 2; i < 60; i ++){
        if(isPrime(i)){
            pm.push_back(i);
        }
    }
}

int Pow(int a, int b){
    int res = 1;
    for(int i = 1; i <= b; i ++){
        if(res >= (n + 1 + a - 1) / a){
            return n + 10;
        }
        res = res * a;
    }
    return res;
}
// 计算 [2, n] 中 a^p 的 a 的取值个数
// 其中 p >= 2
int cal(int p){
    if(Pow(2LL, p) > n) return 0;
    int l = 2, r = 1e9;
    while(l < r){
        int mid = l + r + 1 >> 1;
        if(Pow(mid, p) <= n) l = mid;
        else r = mid - 1;
    }
    // [2, l] 都可以取到
    return l - 1;
}

void solve(){
    cin >> n;
    int res = 1; // add the case 1
    init(); // 预处理质数, cnt, pm
    cnt = pm.size(); 
    for(int i = 1; i < 1 << cnt; i ++){
        int s = 0;
        int p = 1;
        bool fg = false; // 防止 p 累乘起来太大
        for(int j = 0; j < cnt; j ++){
            if(i >> j & 1){
                s ++;
                if(p >= (n + 1 + pm[j] - 1) / pm[j]){
                    fg = true;
                    break;
                }
                p *= pm[j];
            }
        }
        if(fg) continue ; 
        if(s & 1) res += cal(p);
        else res -= cal(p);
    }
    cout << res << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```

## Example Two

[P9118 [春季测试 2023] 幂次 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P9118)

上一个问题是这个问题的一个弱化版本，这个问题增加了 k=1 或 k≥3 的情况。但对于 k=1，答案是 n；如果 k≥3，因为答案很小，我们可以用暴力枚举的方法。但是，当我解决这个问题时，我遇到了一些问题。不能在上一题的数组中去掉质因子 2 之后直接使用容斥原理，因为 4 的答案不会被统计，可能是因为丢失了质因子。

The last problem is a weaker version of this. This add  the case when k = 1 or k >= 3 , but for k = 1, the answer is n. if k >= 3, becase the answer is small, we can use brute force to enumerate. However, when i solve this problem, i encountered some issues. We cannot use the inclusion-exclusion principle on the previous vector after removing the prime factor 2, because the answer for 4 will be countered. This likely due to the loss of factors. 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

bool isPrime(int x){
    for(int i = 2; i <= x / i; i ++){
        if(x % i == 0) return false;
    }
    return true;
}
int n, k;
int cnt = 0;
vector<int> pm; // [2, 60] 内的质数
void init(){
    int cnt = 0;
    for(int i = 2; i < 60; i ++){
        if(isPrime(i)){
            pm.push_back(i);
        }
    }
}

int Pow(int a, int b){
    int res = 1;
    for(int i = 1; i <= b; i ++){
        if(res >= (n + 1 + a - 1) / a){
            return n + 10;
        }
        res = res * a;
    }
    return res;
}

// 计算 [2, n] 中 a^p 的 a 的取值个数
// 其中 p >= 2
int cal(int p){
    if(Pow(2LL, p) > n) return 0;
    int l = 2, r = 1e9;
    while(l < r){
        int mid = l + r + 1 >> 1;
        if(Pow(mid, p) <= n) l = mid;
        else r = mid - 1;
    }
    // [2, l] 都可以取到
    return l - 1;
}

void solve(){
    cin >> n >> k;
    if(k == 1){
        cout << n << '\n';
        return ;
    }

    int res = 1; // add the case 1
    init(); // 预处理质数, cnt, pm
    cnt = pm.size(); 

    if(k == 3){
        // vector<int> v(pm.begin() + 1, pm.end());
        // swap(v, pm);
        unordered_set<int> s;
        for(int i = 3; i < 60; i ++){ // b
            for(int j = 1; ; j ++){
                if(Pow(j, i) > n) break;
                s.insert(Pow(j, i));
            }
        }
        cout << s.size() << '\n';
        return ;
    }
    // cnt --;
    // for(int i = 0; i < cnt; i ++){
    //     cout << i << ' ' << pm[i] << '\n';
    // }

    for(int i = 1; i < 1 << cnt; i ++){
        int s = 0;
        int p = 1;
        bool fg = false; // 防止 p 累乘起来太大
        for(int j = 0; j < cnt; j ++){
            if(i >> j & 1){
                s ++;
                if(p >= (n + 1 + pm[j] - 1) / pm[j]){
                    fg = true;
                    break;
                }
                p *= pm[j];
            }
        }
        if(fg) continue ; 
        // if(cal(p)){
        //     cout << "Prime: ";
        //     // cout << ((s & 1) ? "")
        //     cout << p << ' ' << cal(p) << '\n';
        // }
        if(s & 1) res += cal(p);
        else res -= cal(p);
    }
    cout << res << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```
