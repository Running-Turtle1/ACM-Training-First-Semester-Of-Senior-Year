## 题目链接

[E-前缀和前缀最大值_牛客小白月赛97 (nowcoder.com)](https://ac.nowcoder.com/acm/contest/85347/E)

## 题解

- A 类价值增加只会在放正数的时候出现，且 maxx 最多出现 正数 + 1 次，就是前面全放正数，设正数数量 = $\lambda$ ，即 $mx=\lambda+1$ 

- 最少就是全放负数，抵消掉所有的 $\sum_i positive_i\leq neg$ ，设为 $x$ ，即 $mn=\lambda + 1 - x$ 

- 两者之间共有 $x+1$ 种不同数，我们思考是否都能取到 ？

- 实际上最小构造方式，每次取一个正数放前面就能得到所有构造方案

- 对于每个询问， $O(100)$ 处理即可。
  
  ## Trick

- 先想正解，在想复杂数据结构

- 对于常数很大的暴力数据结构，不是一点思路没有的情况下慎用，因为写完之后发现错了就寄了

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, q, b[N];
int neg[N]; // 负数绝对值前缀和
int s[N][110]; // 正数 j 的数量前缀和

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> b[i];
        neg[i] = neg[i - 1] + (b[i] < 0 ? -b[i] : 0);
        for(int j = 1; j <= 100; j ++){
            s[i][j] = s[i - 1][j] + (b[i] == j);
        }
    }
    auto ask = [&] (int l, int r){
        int has = neg[r] - neg[l - 1];
        int sum = 0;
        for(int i = 1; i <= 100; i ++){
            int tmp = s[r][i] - s[l - 1][i];
            if(has >= tmp * i){
                has -= tmp * i;
                sum += tmp;
            }
            else{
                return sum + has / i;
            }
        }  
        return sum;
    };
    cin >> q;
    while(q --){
        int l, r;
        cin >> l >> r;
        cout << ask(l, r) + 1 << '\n';
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```
