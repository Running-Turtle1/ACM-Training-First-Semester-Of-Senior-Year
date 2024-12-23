#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 5e5 + 10;
int const sz = __lg(N) + 2;

vector<int> e[N];
int deep[N], stjump[N][sz];

void dfs(int u, int fa){
	deep[u] = deep[fa] + 1;
	stjump[u][0] = fa;
	for(int j = 1; j < sz; j ++){
		stjump[u][j] = stjump[stjump[u][j - 1]][j - 1];
	}
	for(auto& v : e[u]){
		if(v == fa) continue ;
		dfs(v, u);
	}
}

int lca(int u, int v){
	if(deep[u] < deep[v]) swap(u, v);
	for(int j = sz - 1; j >= 0; j --){
		if(deep[stjump[u][j]] >= deep[v]){
			u = stjump[u][j];
		}
	}
	if(u == v) return u;
	for(int j = sz - 1; j >= 0; j --){
		if(stjump[u][j] != stjump[v][j]){
			u = stjump[u][j];
			v = stjump[v][j];
		}
	}
	return stjump[u][0];
}

int n, m, r;

void solve(){	
	cin >> n >> m >> r;
	for(int i = 1; i < n; i ++){
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs(r, 0);
	while(m --){
		int a, b;
		cin >> a >> b;
		cout << lca(a, b) << '\n';
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
