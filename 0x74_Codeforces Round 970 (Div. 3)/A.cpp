#include<bits/stdc++.h>
using namespace std;
#define int long long

// 多练 dfs

int n, a, b;
int tp[22], st[22];
bool fg = false;

void dfs(int u){
	if(u == n + 1){
		int res = 0;
		for(int i = 1; i <= n; i ++){
			int t = tp[i] == 0 ? 1 : -1;
			res += t * (i <= a ? 1 : 2);
		}
		if(!res) fg = true;
		return ;
	}

	tp[u] = 0;
	dfs(u + 1);

	tp[u] = 1;
	dfs(u + 1);
}

void solve(){
	cin >> a >> b;
	n = a + b; 
	fg = false;
	dfs(1);
	cout << (fg ? "YES" : "NO") << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}