#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 200010;

int n, k;
struct node{
	int a, b;
	bool operator < (const node & T) const {
		return (a - 1) * T.b < (T.a - 1) * b;
	}
}infos[N];
int dp[N][12]; // 考虑到第 i 个数, 已经选了 j 个数的最大贡献

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		cin >> infos[i].a >> infos[i].b;
	}
	sort(infos + 1, infos + n + 1);
	// cout << '\n';
	// for(int i = 1; i <= n; i ++){
	// 	cout << infos[i].a << ' ' << infos[i].b << '\n';
    // }
    // cout << '\n';
    memset(dp, -1, sizeof dp);
	dp[1][0] = 1, dp[1][1] = infos[1].a + infos[1].b;
	for(int i = 2; i <= n; i ++){
		for(int j = 0; j <= k; j ++){
			dp[i][j] = max(dp[i][j], dp[i - 1][j]);
			if(j) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] * infos[i].a + infos[i].b);
			}
		}
	}
	cout << dp[n][k] << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}