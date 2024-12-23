#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
vector<pair<int, int> > e;
int dp[N]; // dp[i] 表示将 i 删除之后
int sz[N];
void dfs(int u, int fa){
	int mxSize = 0;
	int sum = 0;
	for(auto& [v, w] : e[u]){
		if(v == fa) continue;
		dfs(v, u);
		sz[u] += sz[v];
		mxSize = max(mxSize, sz[v]);
		sum += sz[v];
	}
	mxSize = max(mxSize, n - 1 - sum);
	dp[u] = mxSize;
}

void solve(){
	
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
// barycenter
// dp[i] 表示删除 i 之后剩余连通块大小的最大值