## A

```cpp
void solve(){
	int n = 12, res = 0;
	for(int i = 1; i <= n; i ++){
		string s;
		cin >> s;
		if(s.size() == i) res ++;
    }
    cout << res;
}
```

## B

```cpp
void solve(){
	string s;
	cin >> s;
	int now = -1;
	for(int i = 0; i < s.size(); i ++){
		if(s[i] == 'A') now = i;
	}
	// cout << now << '\n';
	int res = 0;
	for(int i = 2; i <= 26; i ++){
		char ch = 'A' + i - 1;
		for(int j = 0; j < s.size(); j ++){
			if(s[j] == ch){
				res += abs(j - now);
				now = j;
				// cout << j << ' ' << now << '\n';
				break;
			}
		}
	}
	cout << res;
}
```

## C

```cpp
void solve(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
	for(int i = 1; i <= n; i ++){
		cin >> b[i];
    }

    cout << *max_element(a + 1, a + n + 1) + *max_element(b + 1, b + n + 1);

}
```

## D

```cpp
int const N = 2e5 + 10;

int n, m;
vector<pair<int, int> > e[N];

int x[N];

bool st[N];

void dfs(int u, int fa){
	st[u] = true;
	for(auto [v, w] : e[u]){
		if(v == fa) continue ;
		x[v] = x[u] + w;
		if(!st[v]) dfs(v, u);
	}
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= m; i ++){
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back({v, w});
		e[v].push_back({u, -w});
	}
	for(int i = 1; i <= n; i ++){
		if(!st[i]) dfs(i, 0);
	}
	for(int i = 1; i <= n; i ++){
		cout << x[i] << " \n"[i == n];
    }


}
```

## E

二分套二分，第一层二分还需要的票数，第二层二分多少人可以超过当前竞选者。

```cpp
int const N = 2e5 + 10;
int n, m, k, pos, val, sum[N], ans[N];
pair<int, int> a[N];

bool check(int i, int x){
	pos = upper_bound(a + 1, a + n + 1, make_pair(val + x, LLONG_MAX)) - a;
	if(pos - 1 != i && val + x + 1 - a[pos - 1].first > k - x) return (n - pos + 1) < m;
	int l = 1, r = pos - 1;
	while(l < r){
		int mid = l + r >> 1;
		(pos - mid) * (val + x + 1) - (sum[pos - 1] - sum[mid - 1]) - (x + 1) * (mid <= i) <= k - x ? r = mid : l = mid + 1;
	} 
	return (l <= i ? n - l : n - l + 1) < m;
}

void solve(){
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i ++){
		cin >> a[i].first;
		a[i].second = i;
		k -= a[i].first;
    }
    sort(a + 1, a + n + 1, [&] (auto &a, auto &b){
    	return a.first < b.first;
    });
    for(int i = 1; i <= n; i ++){
    	sum[i] = sum[i - 1] + a[i].first;
    }
    for(int i = 1; i <= n; i ++){
    	val = a[i].first;
    	int id = a[i].second;
    	if(n - (upper_bound(a + 1, a + n + 1, make_pair(val + k, LLONG_MAX)) - a) + 1 >= m){
    		ans[id] = -1;
     		continue ;
    	}
    	int l = 0, r = k;
    	while(l < r){
    		int mid = l + r >> 1;
    		if(check(i, mid)) r = mid;
    		else l = mid + 1;
    	}
    	ans[id] = l;
    }
    for(int i = 1; i <= n; i ++){
    	cout << ans[i] << ' ';
    }
}
```

## F

考虑每个物品的重量都不同，那么最多 $m\ln m$ 个物品，$01$ 背包即可。

但是会出现 $w$ 相同的物品，对 $w$ 相同的物品，放 $\frac m w$ 个进入一个数组，贡献用差分的方式算。对于这类物品，最多用 $01$ 背包做 $\frac W w$ 次转移。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3100;

int n, m;

int w[N], v[N];

vector<int> vc[N];

int f[N];

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		cin >> w[i] >> v[i];
		int now = v[i] - 1;
		for(int j = 1; j * w[i] <= m; j ++){
			vc[w[i]].push_back(now);
			now -= 2;
		}
    }
    for(int i = 1; i <= m; i ++){
    	sort(vc[i].begin(), vc[i].end(), [&] (auto &a, auto &b){return a > b;});
    }

    // f[j] 背包为 j 的最大价值
    for(int i = 1; i <= m; i ++){ // 考虑物品的重量
    	for(int k = 0; k < vc[i].size(); k ++){ // 考虑物品
    		if(k > m / i) break;
    		for(int j = m; j >= i; j --){
    			f[j] = max(f[j], f[j - i] + vc[i][k]);
    		}
    	} 
    }
    int res = 0;
    for(int j = 0; j <= m; j ++){
    	res = max(res, f[j]);
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
