#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n;
vector<int> e[N];
int maxSub[N], sz[N];
pair<int, int> centroid;

void dfs(int u, int fa){
	sz[u] = 1;
	for(int v : e[u]){
		if(v == fa) continue ;
		dfs(v, u);
		sz[u] += sz[v];
		maxSub[u] = max(maxSub[u], sz[v]);
	}
	maxSub[u] = max(maxSub[u], n - sz[u]);
	// cout << u << ' ' << sz[u] << ' ' << maxSub[u] << '\n';
	if(maxSub[u] <= n / 2){
		if(centroid.first == -1) centroid.first = u;
		else centroid.second = u;
	}
}
pair<int, int> leaf;
void find(int u, int fa){
	if(e[u].size() == 1){
		leaf = {u, fa};
		return ;
	}
	for(auto v : e[u]){
		if(v == fa) continue ;
		find(v, u);
	}
}
void solve(){
	centroid = {-1, -1};
	cin >> n;
	for(int i = 1; i <= n; i ++){
		sz[i] = 0;
		maxSub[i] = 0;
		e[i].clear();
    }
	int u, v;
	for(int i = 1; i < n; i ++){
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
    }
    dfs(1, 0);
    if(centroid.second == -1 || n == 2){
    	// cout << "??\n";
    	cout << u << ' ' << v << '\n';
    	cout << v << ' ' << u << '\n';
    }
    else{
    	// cout << "???\n";
    	auto [p1, p2] = centroid;
    	find(p2, p1);
    	cout << leaf.first << ' ' << leaf.second << '\n';
    	cout << leaf.first << ' ' << p1 << '\n';
    }
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}