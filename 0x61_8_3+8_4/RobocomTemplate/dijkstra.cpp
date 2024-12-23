#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

{ // BF - dijkstra
	int d[N], g[N][N];
	bool st[N];
	void dijkstra(){
		memset(d, 0x3f, sizeof d);
		d[s] = 0;
		for(int i = 1; i <= n; i ++){
			int u = -1;
			for(int j = 1; j <= n; j ++){
				if(!st[j] && (u == -1 || d[j] < d[u])){
					u = j;
				}
			}
			st[u] = true;
			for(int v = 1; v <= n; v ++){
				d[v] = min(d[v], d[u] + g[u][v]);
			}
		}
	}
}
{ // heap - disjktra
	typedef pair<int, int> pii;
	priority<pii, vector<pii>, greater<pii> > heap;
	int h[N], e[N], w[N], ne[N], idx;
	int d[N], st[N];
}	void dijkstra(){
	memset(d, 0x3f, sizeof d);
	d[s] = 0;
	heap.push({0, s});
	while(heap.size()){
		auto const [dis, u] = heap.top();
		heap.pop();
		if(st[u]) continue ;
		st[u] = true;
		for(int i = h[u]; ~i; i = ne[i]){
			int v = e[i];
			if(d[u]  + w[i] < d[v]){
				d[v] = d[u] + w[i];
				heap.push({d[v], v});
			}
		}
	}
}