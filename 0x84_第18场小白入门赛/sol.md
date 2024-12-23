# 第 18 场 小白入门赛

## 6 武功秘籍

考察进制理解。

对于第 $i$ 位，设 $bit_i=x$ ，每一位的最大值是 $b_j$ ，也就是说每一位是 $b_j+1$ 进制 ，那么第 $i$ 位的大小就是 $x\times \sum_{j=i+1}^{las} (b_j+1)$   。

据此推导。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n, k;
    cin >> n >> k;
    if(k == 1){
        cout << "0\n";
        return ;
    }
    -- k;
    vector<int> bit;
    while(n){
        bit.push_back(n % 10);
        n /= 10;
    }
    vector<int> t(bit.size() + 1);
    // for(auto &x : bit) cout << x << ' '; cout << '\n';
    int l, r = 0, lasBit = 0;
    t[0] = 1;
    for(int i = 0; i < bit.size(); i ++){
        l = r + 1;
        r += t[i] * bit[i];
        if(r >= k){
            lasBit = i;
            break;
        }
        // cout << i << ' ' << l << ' ' << r << '\n';
        t[i + 1] = t[i] * (bit[i] + 1);
    }
    // cout << lasBit << '\n';
    for(int i = lasBit; i >= 0; i --){
        cout << (k / t[i]);
        k %= t[i];
    }
}

signed main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);

    int T = 1;
    // cin >> T;
    while (T --){
        solve();
    }

    return 0;
}
```

## 2 + 4 情报传递

思维题，技巧在于具有大量相同的区间，实际上只有左右两个特殊区间，以及中间大量相同的区间。

首先，如果不存在点不能走，那么从 $x$ 走到 $y$ ，贪心走 $\lceil \frac {y-x}{2} \rceil$ 即可。

假设在 $a\rightarrow b$ 区间内，存在 $x$ 个 $c$ 的倍数，设 $d$ 是这些点的最小值，$e$ 是最大值。

那么从 $a\rightarrow d-1$ 和 $e+1\rightarrow b$ 贪心走即可。

剩下的全是相同的走法。

$O(1)$ 。

dp 思路很简答，爬楼梯问题，$O(n)$ 。

Trick : 

第一个 $\geq x$ 的 $c$ 的倍数 : $\lceil \frac x c \rceil \times c$ 

第一个 $\leq x$ 的 $c$ 的倍数 : $\lfloor \frac x c \rfloor \times c$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int dis(int a, int b){
    return (b - a) / 2 + (b - a) % 2;
}

void solve(){
    int a, b, c, x = 0;
    cin >> a >> b >> c;
    int d = (a + c - 1) / c * c; // 第一个 >= a 的 c 的倍数
    int e = b / c * c; // 第一个 <= b 的 c 的倍数
    if(d > b){ 
        cout << dis(a, b) << '\n';
    }
    else{
        cout << dis(a, d - 1) + dis(e + 1, b) + 1 + dis(1, c + 1) * ((e - d) / c) << '\n';
    } 
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    cin >> T;
    while (T --){
        solve();
    }

    return 0;
}
```

### 3 村长分钱

> 已知 $a,b$ , 求满足 $a \bmod y=b$ ，多少 $y$ 满足要求

即 $a=b+xy$ 。

即 $xy=b-a$ ，计算一下 $b-a$ 有多少因子即可。

注意只统计 $>b$ 的因子。

```cpp
#include <iostream>
#include <cmath>
using namespace std;

int count_solutions(int a, int b) {
    if (a < b) return 0; // 无解的情况
    int d = a - b;
    int count = 0;

    // 枚举 d 的因数
    for (int x = 1; x * x <= d; ++x) {
        if (d % x == 0) {
            if (x > b) count++;         // x 是 d 的因数，且 x > b
            if (d / x != x && d / x > b) count++; // d/x 也是因数，且 d/x > b
        }
    }

    return count;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << count_solutions(a, b) << endl;
    return 0;
}
```

## 5 好汉身份

假设先手的回合，发现选择 $a+b$ 小的更优。

发现后手同样如此。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

struct node{
    int a, b;
    bool operator < (const node & T) const {
        return a + b < T.a + T.b;
    }
}v[2100];

int n;

void solve(){
    cin >> n;
    n <<= 1;
    for(int i = 1; i <= n; i ++){
        cin >> v[i].a;
    }
    for(int i = 1; i <= n; i ++){
        cin >> v[i].b;
    }
    sort(v + 1, v + n + 1);
    int res = 0; 
    for(int i = 1; i <= n; i ++){
        if(i & 1) res += v[i].a;
        else res -= v[i].b;
    }
    cout << res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    // cin >> T;
    while (T --){
        solve();
    }

    return 0;
}
```
