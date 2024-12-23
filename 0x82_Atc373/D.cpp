#include<bits/stdc++.h>
using namespace std;
#define int long long

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

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
