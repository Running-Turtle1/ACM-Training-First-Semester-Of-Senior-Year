#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1100;

int n, k;
int a[N], b[N];

int s[110][110][1001];

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		cin >> a[i] >> b[i];
		if(a[i] < b[i]) swap(a[i], b[i]);
    }
    vector<vector<int> > dp(n + 3, vector<int> (k + 3, 2e18));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i ++){
    	for(int j = 0; j <= k; j ++){
    		for(int c = 0; c <= j; c ++){
    			dp[i][j] = dp[i - 1][c] + s[a[i]][b[i]][c-j];
    		}
    	}
    }
    cout << dp[n][k] << '\n';
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);
	// cout << "YES: \n";
	for(int i = 1; i <= 100; i ++){
		for(int j = 1; j <= i; j ++){
			for(int k = 1; k <= 1000; k ++){
				int &res = s[i][j][k];
				if(k <= i - 1) res = k * j;
				else if(k >= i) res = (i-1)*j+k-(i-1);
			}
		}
	}

	// cout << s[6][3][4] << '\n';
	// cout << s[4][4][5] << '\n';

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}