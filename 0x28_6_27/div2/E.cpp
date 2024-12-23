#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 1e9 + 7;

int n, k;
int c[63][64];


int dp[63];

void solve(){
	cin >> n >> k;

	int ans = 0;

	int SumofOne = 0;
	// 枚举 LCP 的长度
	for(int len = 0; len < 63; len ++){
		int bit = 62 - len;
		if((n >> (bit - 1) & 1) == 0) continue;
		if(n >> bit & 1) SumofOne ++;
		if(SumofOne > k) break;
		if(bit == 0) res ++;
		int Remain = bit - 1;
		int tmp = 0;
		for(int j = 0; j + SumofOne <= k; j ++){
			tmp = (tmp + c[Remain][j]) % mod;
		}
		ans = (ans) + tmp*(tmp+1)/2;
		// if(bit == 3) cout << ans << '\n';
		// if(bit == 2) cout << ans << '\n';
	}
	cout << ans << '\n';
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	c[0][0] = 1;
	for(int i = 1; i <= 63; i ++){
		c[i][0] = 1;
		for(int j = 1; j <= i; j ++){
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}

	// cout << c[5][2] << '\n';

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}