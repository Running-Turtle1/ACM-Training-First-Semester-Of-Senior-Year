#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, m;
vector<int> e[N];
int dfn[N], low[N], tot = 0;
set<pair<int, int> > st;
vector<pair<int, int> > bridges;
int sz[N];
void tarjan(int u, int fa){
	dfn[u] = low[u] = ++ tot;
	sz[u] = 1;
	for(int v : e[u]){
		if(!dfn[v]){
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]){
				bridges.push_back({u, v}); // 回溯时求出一条割边
			}
		}
		else if(v != fa) {
			low[u] = min(low[u], dfn[v]);
		}
	}
} 
void tarjan(){
	for(int i = 1; i <= n; i ++){
		if(!dfn[i]){
			tarjan(i, 0);
		}
	} 
}

void solve(){
	tot = 0;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		e[i].clear();
		sz[i] = dfn[i] = low[i] = 0;
	}
	st.clear();
	for(int i = 1; i <= m; i ++){
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}

	tarjan(); // 初始化桥边
	// for(int i = 1; i <= n; i ++){
	// 	cout << dfn[i] << " \n"[i == n];
    // }
	// for(int i = 1; i <= n; i ++){
	// 	cout << sz[i] << " \n"[i == n];
    // }
	int res = n * (n - 1) / 2;
	for(int i = 1; i <= n; i ++){
		for(int j : e[i]){
			if(st.count({i, j}) ){
				// cout << i << ' ' << j << '\n';
				int mn = sz[j];
				int tmp = mn * (mn - 1) / 2;
				mn = n - mn;
				tmp += mn * (mn - 1) / 2;
				res = min(res, tmp);
			}
		}
	}
	cout << res << '\n';
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
// 10000
// 2 1
// 1 2

// 3 2
// 1 3
// 2 1

// 3 2
// 1 2
// 3 2

// 3 2
// 3 2
// 1 3

// 3 3
// 1 2
// 3 2
// 1 3

// 4 3
// 2 1
// 1 3
// 4 1

// 4 3
// 2 3
// 4 1
// 2 1

// 4 3
// 2 3
// 3 1
// 1 4

// 4 4
// 3 1
// 3 2
// 2 1
// 1 4

// 4 3
// 1 2
// 3 1
// 2 4

// 4 3
// 1 3
// 4 1
// 2 4

// 4 4
// 4 1
// 2 1
// 3 1
// 2 4

// 4 3
// 3 2
// 1 2
// 4 2

// 4 3
// 3 2
// 2 4
// 1 3
// 4 4
// 1 3
// 2 4