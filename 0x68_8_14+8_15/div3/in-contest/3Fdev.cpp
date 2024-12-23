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
    			if(dp[i-1][c] != 2e18 && s[a[i]][b[i]][j-c] != 2e18)
    			dp[i][j] = dp[i - 1][c] + s[a[i]][b[i]][j-c];
    		}
    	}
    }

    if(dp[n][k]==2e18)cout<<"-1\n";
    else cout << dp[n][k] << '\n';
}

signed main(){
//	 ios::sync_with_stdio(false);
//	 cin.tie(0), cout.tie(0);
	// cout << "YES: \n";
	for(int i = 0; i <= 100; i ++){
		for(int j = 0; j <= 100; j ++){
			for(int k = 0; k <= 1000; k ++){
				s[i][j][k]=2e18;
			}
		}
	}
	for(int i = 100; i >= 1; i --){
		for(int j = i; j >= 1; j --){
			s[i][j][0] = 0;
			for(int k = 1; k < i + j; k ++){
				if(s[i + 1][j][k - 1] != 2e18){
					s[i][j][k] = s[i + 1][j][k - 1] + j;	
				}
				
//				if(s[i][j][k] !)
//				s[i][j][k] = s[i][]
//				int &res = s[i][j][k];
//				if(k == i + j) res = i * j;
//				else if(k >= i) res = (i - 1) * j + k - (i - 1);
//				else res = k * j;
			}
			s[i][j][i + j] = i * j;
		}
	}
	
//	cout << s[9][2][11] << '\n';
//	cout << s[4][3][7] << '\n';
//	cout << s[10][8][7] << '\n';
//	
//		cout<<s[8][3][11]<<'\n';
//		cout<<s[6][2][7]<<'\n';
	
//	cout<<s[1][1][2]<<'\n';
//	 cout << s[6][3][4] << '\n';
//	 cout << s[4][4][5] << '\n';

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}
