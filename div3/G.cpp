#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, k;
vector<pair<int, int> > e[N];

int f[N][110], s[N];

void dfs(int u, int fa){
	f[u][0] = 0;
	if(e[u].size() == 1) f[u][1] = 0, s[u] = 1;
	for(auto &[v, w] : e[u]){
		if(v == fa) continue ;
		dfs(v, u);
		s[u] += s[v];
		for(int i = min(s[u], k); i >= 0; i --){
			for(int j = 0; j <= s[v] && j <= i; j ++){
				f[u][i] = min(f[u][i], f[u][i - j] + f[v][j] + j * (k - j) * w);
			}
		}
	}
}

void solve(int cnt){
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		e[i].clear();
		for(int j = 0; j <= k; j ++) f[i][j] = 1e18;
		s[i] = 0;
    }
    for(int i = 1; i < n; i ++){
    	int u, v, w;
    	cin >> u >> v >> w;
    	e[u].push_back({v, w});
    	e[v].push_back({u, w});
    }
    dfs(1, 0);
    cout << "Case #" << cnt << ": ";
    cout << f[1][k] << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	for(int i = 1; i <= T; i ++){
		solve(i);
	}

	return 0;
}