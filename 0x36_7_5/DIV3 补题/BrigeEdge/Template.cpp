#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int const M = 2e5 + 10;

int n, m;
struct edge{
	int u, v;
	bool isBridgeEdge = false; // 是否是桥边
}edges[M];
int sz[N];
int res = 2e9;

struct judgeBridgeEdge{
	int p[N];
	int find(int x){
		if(x == p[x]) return p[x];
		return p[x] = find(p[x]);
	}
	judgeBridgeEdge() {
		for(int i = 1; i <= n; i ++){
			p[i] = i;
			sz[i] = 1;
    	}
		for(auto &[u, v, fg] : edges){
			int pu = find(u), pv = find(v);
			if(pu == pv){
				fg = true;
			}
			else{
				p[pv] = pu;
				sz[pv] += sz[pu];
			}
		}    	
	}
};

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= m; i ++){
		int u, v;
		cin >> u >> v;
		edges[i * 2 - 1] = {u, v};
		edges[i * 2] = {v, u};
		// e[u].push_back(u);
		// e[v].push_back(v);
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
