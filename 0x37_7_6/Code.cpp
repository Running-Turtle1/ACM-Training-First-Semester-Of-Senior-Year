#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int const N = 2e5 + 10;
vector<int> e[N];
int dfn[N], low[N], tot;
int stk[N], instk[N], top;
int scc[N], siz[N], cnt;

void tarjan(int x){
	dfn[x] = low[x] = ++ tot;
	stk[++ top] = x, instk[x] = 1;
	for(auto y : e[x]){
		if(!dfn[y]){
			tarjan(y);
			low[x] = min(low[x], low[y]);
		}
		else if(instk[y]){
			low[x] = min(low[x], dfn[y]);
		}
	}
	if(dfn[x] == low[x]){ // x 是根节点
		int y;
		cnt ++;
		do{
			y = stk[top --];
			instk[y] = 0;
			scc[y] = cnt; // scc 编号
			siz[cnt] ++; // scc 大小
		}
		while(y != x);
	}
}

int din[N], dout[N]; // 缩点的入度以及出度
vector<int> cpg[N]; // Contracted point graph, 缩点图
void tarjan(){
	for(int i = 1; i <= n; i ++){
		if(!dfn[i]){
			tarjan(i);
		}
	}
	for(int i = 1; i <= n; i ++){
		for(int j : e[i]){
			if(scc[i] != scc[j]){
				dout[scc[i]] ++;
				din[scc[j]] ++;
				cpg[scc[i]].push_back(scc[j]);
			}
		}
	}
}

int w[N], nw[N], f[N];
int dfs(int x){
	if(f[x]) return f[x];
	for(int y : cpg[x]){
		f[x] = max(f[x], dfs(y));
	}
	f[x] += nw[x];
	return f[x];
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		cin >> w[i];
    }
	for(int i = 1; i <= m; i ++){
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
	}
	tarjan();
	for(int i = 1; i <= n; i ++){
		nw[scc[i]] += w[i];
	}

	int res = 0;
	for(int i = 1; i <= cnt; i ++){
		res = max(res, dfs(i));
	}
	cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
