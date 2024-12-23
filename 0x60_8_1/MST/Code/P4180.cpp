#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 5e5 + 10;
int const M = 1e6 + 10;
int const sz = __lg(N) + 3;
int const INF = 2e18;

vector<tuple<int, int, int> > edges; // 边集
vector<pair<int, int> > e[N]; // MST 的邻接表
int n, m;
int deep[N], stjump[N][sz], stMax[N][sz][2]; // ST[i][j][0/1] 维护路径最大值和次大值
int p[N], atMst[M]; // 并查集 & 边集中的边是否在 MST 中

int find(int x){
	return (x == p[x] ? x : p[x] = find(p[x]));
}
void dfs(int u, int fa, int w);
int lca(int u, int v);
pair<int, int> askMax(int u, int v);

void solve(){
	cin >> n >> m;
	edges.clear();
	for(int i = 1; i <= n; i ++){
		e[i].clear();
		p[i] = i;
	}
	for(int i = 0; i < m; i ++){
		int u, v, w;
		cin >> u >> v >> w;
		edges.push_back({w, u, v});
		atMst[i] = 0;
	}
	sort(edges.begin(), edges.end());

	int MST = 0; // MST 大小
	for(int i = 0; i < m; i ++){
		auto &[w, u, v] = edges[i];
		int pu = find(u), pv = find(v);
		if(pu != pv){
			p[pu] = pv;
			MST += w;
			atMst[i] = 1;
		}
	}

	for(int i = 0; i < m; i ++){
		if(atMst[i]){
			auto &[w, u, v] = edges[i];
			e[u].push_back({v, w});
			e[v].push_back({u, w});
		}
	}

	dfs(1, 0, 0); // 预处理 ST 表查询路径最大/次大值

	int secondMST = INF;
	for(int i = 0; i < m; i ++){
		if(!atMst[i]){
			auto &[w, u, v] = edges[i];
			auto [mx1, mx2] = askMax(u, v); 
			if(w > mx1){
				secondMST = min(secondMST, MST - mx1 + w);
			}
			else if(mx2 != -INF && w > mx2){
				secondMST = min(secondMST, MST - mx2 + w);
			}
		}
	}
	cout << secondMST << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}

void dfs(int u, int fa, int w){
	deep[u] = deep[fa] + 1;
	stjump[u][0] = fa;
	stMax[u][0][0] = w;
	stMax[u][0][1] = -INF;

	// 最大值与次大值 = 所有最大值与次大值中的最大值和次大值
	for(int j = 1; j < sz; j ++){
		stjump[u][j] = stjump[stjump[u][j - 1]][j - 1];

		auto &st = stMax[u][j];
		for(int k = 0; k < 2; k ++){
			if(stMax[u][j - 1][k] > st[0]){
				st[1] = st[0];
				st[0] = stMax[u][j - 1][k];
			}
			else if(stMax[u][j - 1][k] > st[1] && stMax[u][j - 1][k] != st[0]){
				st[1] = stMax[u][j - 1][k];
			}
		}

		int halfJump = stjump[u][j - 1];
		for(int k = 0; k < 2; k ++){
			if(stMax[halfJump][j - 1][k] > st[0]){
				st[1] = st[0];
				st[0] = stMax[halfJump][j - 1][k];
			}
			else if(stMax[halfJump][j - 1][k] > st[1] && stMax[halfJump][j - 1][k] != st[0]){
				st[1] = stMax[halfJump][j - 1][k];
			}
		}

	}
	for(auto &[v, w] : e[u]){
		if(v == fa) continue ;
		dfs(v, u, w);
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

pair<int, int> askMax(int u, int v){  // 返回最大值和次大值
	int p = lca(u, v);
	pair<int, int> res = {-INF, -INF};

	for(int j = sz - 1; j >= 0; j --){
		if(deep[stjump[u][j]] >= deep[p]){
			for(int k = 0; k < 2; k ++){
				if(stMax[u][j][k] > res.first){
					res.second = res.first;
					res.first = stMax[u][j][k];
				}
				else if(stMax[u][j][k] > res.second && stMax[u][j][k] != res.first){
					res.second = stMax[u][j][k];
				}
			}
			u = stjump[u][j];
		}
	}

	for(int j = sz - 1; j >= 0; j --){
		if(deep[stjump[v][j]] >= deep[p]){
			for(int k = 0; k < 2; k ++){
				if(stMax[v][j][k] > res.first){
					res.second = res.first;
					res.first = stMax[v][j][k];
				}
				else if(stMax[v][j][k] > res.second && stMax[v][j][k] != res.first){
					res.second = stMax[v][j][k];
				}
			}
			v = stjump[v][j];
		}
	}
	return res;
}