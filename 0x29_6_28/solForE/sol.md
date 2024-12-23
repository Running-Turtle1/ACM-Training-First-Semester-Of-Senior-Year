### Problem Link

[Problem - 1982E - Codeforces](https://codeforces.com/problemset/problem/1982/E)

### Detailed Solution

[Codeforces Round 955 (Div. 2) A-F题解 - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/705437500)

### Trick

- 类似数位 DP 的思想，但又不像

- dp(n, k) 表示答案，考虑如何递归子问题

- 最重要的是找到一个划分边界

- 我们选的是 最高位 1 代表的数 m，设 $m=2^x-1$ 

- 对于 dp(n, k) ，按照如下方式进行记忆化搜索 :

- 首先，k+1 个 1 对应的最小数是 $2^{k+1}-1$ ，n 小于等于这个数的话，就全部合法

- 此外，还有 k=0 的边界情况，此时只有 0 合法

- 对于其他情况，发现 dp(n, k) 按 m 分

- 前半部分是 dp(m-1, k)

- 后半部分是 dp(m~n,k) 每个数去掉高位 1，就是 dp(n-m,k-1)

- 如此一来就能划分子问题了

- 但是发现这样每次搜两个点，按照二叉树是最坏是 $2^{60}$ ，可能 TLE

- 就要观察每次划分左区间的特点，他是 $000111111$ 的形式，最多出现 60 次

- 所以左边最多 60 种 n 的状态，k 也是最大 60，记忆化没问题

- 对于右边就是每次减高位，复杂度相当于 lowbit 操作

- 左边递归处理的时候，左边的左边跟右边都是一类状态，很好写。左边分的右边还是左边的形态，所以右边的状态也有限，大约就是 $63*k$  吧

### Analysis

- 首先相到记忆化搜索行不行

- 其次相当 m 这种划分方式（或者说划分点）

- 最后还要观察状态转移过程中的特殊性（保证状态有限）

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
map<pair<int, int>, int> f;

int const mod = 1e9 + 7;

int dfs(int n, int k){
	// cout << n << ' ' << k << '\n';
	if(f.count({n, k})) return f[{n, k}];
	if(k == 0){
		return f[{n, k}] = 1; // 只有 0 合法
	}
	int mx = (1LL << (k + 1)) - 1;
	if(n < mx){
		// cout << "Here " << n*(n+1)/2<<'\n';
		// int t1 = (n + 1), t2 = (n + 2);
		// if(n & 1) t1 /= 2;
		// else t2 /= 2;
		__int128 tmp = (__int128)(n + 1) * (n + 2) / 2 % mod;
		return f[{n, k}] = (long long)tmp;
	}
	else if(n == mx) return f[{n, k}] = dfs(n - 1, k);
	else{
		int m; // 最高位 1
		for(m = 62; m >= 0; m --){
			if(n >> m & 1){
				break;
			}
		}
		m = (1LL << m);
		// cout << "m: " << m << '\n';
		return f[{n, k}] = (dfs(m - 1, k) + dfs(n - m, k - 1)) % mod;
	}
}

void solve(){
	// f.clear();
	cin >> n >> k;
	cout << dfs(-- n, k) << '\n';
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
