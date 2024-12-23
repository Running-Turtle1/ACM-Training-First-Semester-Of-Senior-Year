#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, m;
vector<int> e[N];
int dfn[N], low[N], tot = 0;
bool is_Cut[N];

void tarjan(int u, bool isRoot){
	dfn[u] = low[u] = ++ tot;
	int childCount = 0;
	for(int v : e[u]){
		if(!dfn[v]){
			tarjan(v, false);
			low[u] = min(low[u], low[v]);
			childCount += (low[v] >= dfn[u]);
		}
		else{
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(childCount > isRoot){
		is_Cut[u] = true;
	}
}
void tarjan(){
	for(int i = 1; i <= n; i ++){
		if(!dfn[i]){
			tarjan(i, true);
		}
	}
}
 
void solve(){
	cin >> n >> m;
	for(int i = 1; i <= m; i ++){
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
    }
    tarjan();
    // for(int i = 1; i <= n; i ++){
    // 	cout << dfn[i] << " \n"[i == n];
    // }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	if(is_Cut[i]) res ++;
    }
    cout << res << '\n';
    for(int i = 1; i <= n; i ++){
    	if(is_Cut[i]) cout << i << " \n"[i == n];
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
