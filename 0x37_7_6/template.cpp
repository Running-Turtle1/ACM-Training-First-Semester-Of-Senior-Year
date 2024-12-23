#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<pair<int, int> > bridges;
void tarjan(int u, int fa){
	dfn[u] = low[u] = ++ tot;
	for(int v : e[u]){
		if(!dfn[v]){
			tarjan(v, u);
			low[u] = min(low[u], low[v]);
			if(low[v] > dfn[u]){
				bridges.push_back({u, v});
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
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
