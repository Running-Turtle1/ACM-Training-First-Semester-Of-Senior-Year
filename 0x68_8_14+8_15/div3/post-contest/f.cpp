#include<bits/stdc++.h>
using namespace std;
#define int long long

int s[110][110][110];
int n, k;
int a[1100], b[1100];
int f[1100][110];

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		cin >> a[i] >> b[i];
    }
    memset(f, 0x3f, sizeof f);
    f[0][0] = 0;
    for(int i = 1; i <= n; i ++){
    	for(int j = 0; j <= k; j ++){
    		for(int r = 0; r <= k && r <= j; r ++){
    			if(f[i - 1][r] != 0x3f3f3f3f and s[a[i]][b[i]][j - r] != -1){
    				f[i][j] = min(f[i - 1][r] + s[a[i]][b[i]][j - r], f[i][j]);
    			}
    		}
    	}
    }
    // cout << f[1][0] <<  ' ' << f[2][0] << ' ' << f[3][0] << ' ' << f[4][0] << '\n';
    // cout << f[n][19] << '\n';
    // cout << f[n][k] << '\n';
    // cout << 0x3f3f3f3f << '\n';
    // for(int i = 0; i <= k; i ++){
    // 	if(f[n][18] == f[n - 1][i] + s[a[n]][b[n]][18-i]){
    // 		cout<<i<<'\n';
    // 	}
    // }
    for(int i = 0; i <= k; i ++){
    	if(f[3][18] == f[n - 1][i] + s[a[n]][b[n]][18-i]){
    		cout<<i<<'\n';
    	}
    }
    cout << f[3][10] << '\n';
    if(f[n][k] > 0x3f3f3f3f) cout << "-1\n";
    else cout << f[n][k] << '\n';
}
// 3 : 得到 10 分, 操作 23 次
// 4 : 得到 8 分, 操作 12 次
int dfs(int a, int b, int k){
	if(k == 0) return s[a][b][k] = 0;
	if(s[a][b][k] != -1) return s[a][b][k];
	if(a == 1 && b == 1) return s[a][b][k] = 1;
	if(k == 1) return s[a][b][k] = min(a, b);
	if(a > b) {
		if(s[a][b][k] == -1){
			s[a][b][k] = dfs(a - 1, b, k - 1) + b;
		}
		else{
			s[a][b][k] = min(dfs(a - 1, b, k - 1) + b, s[a][b][k]);
		}
	}
	else{
		if(s[a][b][k] == -1){
			s[a][b][k] = dfs(a, b - 1, k - 1) + a;
		}
		else{
			s[a][b][k] = min(s[a][b][k], dfs(a, b - 1, k - 1) + a);
		}
	}
	return -1;
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0); 

	// for(int i = 0; i < 110; i ++){
	// 	for(int j = 0; j < 110; j ++){
	// 		for(int k = 0; k < 1100; k ++){
	// 			s[i][j][k] = -1;
	// 		}
	// 	}
	// }
	memset(s, -1, sizeof s);
	for(int i = 1; i <= 100; i ++){
		for(int j = 1; j <= 100; j ++){
			for(int k = 0; k <= 100; k ++){
				if(k <= i + j){
					dfs(i, j, k);
				}
			}
		}
	}

	// cout << s[8][3][10] << '\n';
	// cout << s[5][4][0] <<'\n';
	// cout << s[6][2][7] << '\n';
	// cout << s[8][3][11] << '\n';
	// cout << s[6][3][4] << '\n';

	int T;
	cin >> T;
	while(T --){
		solve();
	}
	return 0;
}
