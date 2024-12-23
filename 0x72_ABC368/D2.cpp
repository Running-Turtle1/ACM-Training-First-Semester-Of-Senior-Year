#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, k;
vector<int> p;
vector<int> e[N];
int fg[N];

void dfs(int u, int fa){
	for(auto &v : e[u]){
		if(v == fa) continue ;
		dfs(v, u);
		fg[u] |= fg[v];
	}
}

void solve(){
	cin >> n >> k;
	for(int i = 1; i < n; i ++){
		int a, b;
		cin >> a >> b;
		e[a].push_back(b);
		e[b].push_back(a);
	}
	for(int i = 1; i <= k; i ++){
		int x;
		cin >> x;
		fg[x] = 1;
		p.push_back(x);
	}
	dfs(p[0], 0);
	cout << accumulate(fg + 1, fg + n + 1, 0LL) << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
