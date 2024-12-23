#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	function<void(int)> dfs = [&] (int u) {
		cout << u << '\n';
		if(u == 5) return ;
		dfs(u + 1);
	};
	dfs(1);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
