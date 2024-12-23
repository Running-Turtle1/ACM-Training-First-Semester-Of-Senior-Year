#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;


int n, m;
vector<int> e[N];
int dfn[N], low[N], tot = 0;
bool is_Cut[N];
int ans[N], sz[N]; // 以 i 为根子树的大小

void tarjan(int u, bool isRoot){
    dfn[u] = low[u] = ++ tot;
    int sum = 0;
    sz[u] = 1;
    int childCount = 0;
    for(int v : e[u]){
        if(!dfn[v]){
            tarjan(v, false);
            sz[u] += sz[v];
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]){
            	childCount ++;
            	sum += sz[v];
            	ans[u] += sz[v] * (n - sz[v]);
            }
        }
        else{
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(childCount > isRoot){
        is_Cut[u] = true;
        ans[u] += n - 1;
        ans[u] += (n - sum - 1) * (sum + 1);
    }
    else{
    	ans[u] = 2 * (n - 1);
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
	for(int i = 1; i <= n; i ++){
		cout << ans[i] << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
