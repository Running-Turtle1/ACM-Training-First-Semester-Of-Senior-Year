#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10, M = 2e6 + 10;

int n, r1, r2;
int h[N], e[M], ne[M], idx = 0;
int be[M];
int a[N], f[N][2];
bool vis[N];

void add(int a, int b){
	e[idx] = b, ne[idx] = h[a], h[a] = idx ++;
}

// 找基环树的环, ine 代表入边
bool find(int u, int ine){
	vis[u] = true;
	for(int i = h[u]; ~i; i = ne[i]){
		if(i == (ine ^ 1)) continue; // 访问到了反向边
		int v = e[i];
		if(vis[v] == false){
			if(find(v, i)) return true;
		}
		else{
			r1 = u, r2 = v;
			be[i] = 1, be[i ^ 1] = 1; // 记录边
			return true;
		}
	}
	return false;
}

// 对基环树树形 DP, 标记上所有基环树上的点
int dfs(int u, int ine){
	vis[u] = true;
	f[u][0] = 0; f[u][1] = a[u];
	for(int i = h[u]; ~i; i = ne[i]){
		if(i == (ine ^ 1) || be[i]) continue; // 反向边或者是环上的边
		int v = e[i];
		dfs(v, i);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
	}
	return f[u][0];
}

void solve(){
	memset(h, -1, sizeof h);
	cin >> n;
	for(int i = 1; i <= n; i ++){
		int j;
		cin >> a[i] >> j;
		// 建双向边
		add(i, j);
		add(j, i);
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	if(vis[i] == false){ // 没访问过
    		r1 = r2 = 0;
    		find(i, -1);
    		if(r1){
    			res += max(dfs(r1, -1), dfs(r2, -1));
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