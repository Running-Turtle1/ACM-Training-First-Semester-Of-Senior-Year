#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, r1, r2; // 环上的其中一条边的两个端点
int const N = 1e6 + 10;
vector<int> e[N];
int a[N], f[N][2];
bool vis[N];

// dfs 找环
void find(int u, int r){
	vis[u] = true;
	for(auto v : e[u]){
		if(v == r){ // 回到了起点
			r1 = u, r2 = v; // 记录环上端点
			return ; 
		}
		if(vis[v]) continue;
		vis[v] = true;
		find(v, r);
	}
}

// 从 u 出发做树形 DP 且返回不选 u 的最大值
// r : 记录出发点, 防止成环重复 dfs
int dfs(int u, int r){
	f[u][0] = 0, f[u][1] = a[u];
	for(auto v : e[u]){
		if(v == r) continue; // 不能回到起点
		dfs(v, r);
		f[u][0] += max(f[v][1], f[v][0]);
		f[u][1] += f[v][0];
	}
	return f[u][0];
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		int j;
		cin >> a[i] >> j;
		// 添加 j -> i 的一条边
		e[j].push_back(i);
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	if(vis[i] == false){
    		r1 = r2 = 0;
    		find(i, i); // 找 i 所在的环
    		if(r1){ // 找到了环
    			/*
					两个点不能同时选, 所以我们每次指定一个点不选,
					另一个根据最优解选或不选, 这样就能保证不同时选
    			*/
    			res += max(dfs(r1, r1), dfs(r2, r2));
    		}
    	}
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}