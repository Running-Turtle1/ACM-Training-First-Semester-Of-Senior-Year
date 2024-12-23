#include<bits/stdc++.h>
using namespace std;
#define int long long

struct Edge{
	int u, v;
	bool fg = false; // 默认不是割边
};
vector<Edge> edges; // 边集
vector<Edge> h[N]; // 邻接表存出边编号
int dfn[N], low[N];
void add(int a, int b){
	edges.push_back({a, b});
	h[a].push_back(edges.size() - 1);
}
int cnt = 0;
void tarjan(int x, int inEdge){
	dfs[x] = low[x] = ++ cnt;
	for(int i = 0; i < h[x].size(); i ++){
		int j = h[x][i], y = e[j].v;
		if(!dfn[y]){
			tarjan(y, j);
			low[x] = min(low[x], low[y]);
			if(low[y] > dfn[x]){
				edges[j].fg = edges[j ^ 1].fg = true;
			}
		}
		else if(j != (inEdge ^ 1)){ // 不是反向边
			low[x] = min(low[x], dfn[y]);
		}
	}
}

void solve(){ 

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
