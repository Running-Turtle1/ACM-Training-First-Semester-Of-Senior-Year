#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 310;

int l, n, m;
int a[N], b[N][N];
int dp[N][N][N];


void solve(){
	cin >> l >> n >> m;
	for(int i = 1; i <= l; i ++){
		cin >> a[i];
	}
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		cin >> b[i][j];       
        }
    } 
	for(int k = l; k >= 1; k --){
		for(int i = n; i >= 1; i --){
        	for(int j = m; j >= 1; j --){
        		dp[k][i][j] = 0;
        		if(i + 1 <= n) dp[k][i][j] |= dp[k][i + 1][j];
        		if(j + 1 <= m) dp[k][i][j] |= dp[k][i][j + 1];
        		if(b[i][j] == a[k]){
        			if(i == n || j == m || k == l || dp[k + 1][i + 1][j + 1] == 0){
        				dp[k][i][j] = 1;
        			}
        		}
        	}
    	}
	}
	cout << (dp[1][1][1] ? "T" : "N") << '\n';
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