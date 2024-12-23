#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3e5 + 10;

int n;
vector<int> e[N];
int w[N], dp[N][2];

void dfs(int u, int fa){
	dp[u][1] = w[u];
	for(auto v : e[u]){
		if(v == fa) continue;
		dfs(v, u);
		dp[u][0] += max({dp[v][0], dp[v][1]});
		dp[u][1] += dp[v][0];
	}
}

void solve(){
	int sumValue = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> w[i];
		sumValue += w[i];
		dp[i][0] = dp[i][1] = 0;
		e[i].clear();
    }
    for (int i = 1; i < n; ++i){
    	int u, v;
    	cin >> u >> v;
    	e[u].push_back(v);
    	e[v].push_back(u);
    }
    dfs(1, 0);
    // cout << max(dp[1][0], dp[1][1]) << '\n';
    cout << (sumValue << 1) - max(dp[1][0], dp[1][1]) << '\n';
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