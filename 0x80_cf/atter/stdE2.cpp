#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1510;
int const inf = 1e18;

int l, n, m, a[N], b[N][N], dp0[N][N], dp1[N][N];
int at[N * N];

void solve(){
	cin >> l >> n >> m;
	for(int i = 1; i <= n * m; i ++){
		at[i] = -1;
	}
	for(int i = 1; i <= l; i ++){
		cin >> a[i];
		if(at[a[i]] == -1) at[a[i]] = i;
	}
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		cin >> b[i][j];       
     		dp0[i][j] = dp1[i][j] = inf;
        }
    }

    for(int i = n; i >= 1; i --){
    	for(int j = m; j >= 1; j --){
    		if(i != n){
    			dp0[i][j] = min(dp0[i][j], dp0[i + 1][j]);
    			dp1[i][j] = min(dp1[i][j], dp1[i + 1][j]);
    		}
    		if(j != m){
    			dp0[i][j] = min(dp0[i][j], dp0[i][j + 1]);
    			dp1[i][j] = min(dp1[i][j], dp1[i][j + 1]);
    		}
    		int pos = at[b[i][j]];
    		if(pos != -1 && pos % 2 == 0){
    			if(i == n || j == m || dp1[i + 1][j + 1] > pos + 1){
    				dp0[i][j] = min(dp0[i][j], pos);
    			}
    		}
    		if(pos != -1 && pos % 2 == 1){
    			if(i == n || j == m || dp0[i + 1][j + 1] > pos + 1){
    				dp1[i][j] = min(dp1[i][j], pos);
    			}
    		}
    	}
    }
    cout << (dp1[1][1] == 1 ? "T" : "N") << '\n';
    // cout << (dp1[1][1] < dp0[1][1] ? "T" : "N") << '\n';
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