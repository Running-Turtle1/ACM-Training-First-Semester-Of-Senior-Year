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