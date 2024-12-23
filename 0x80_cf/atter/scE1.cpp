#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 310;

int l, n, m;
int dp[N][N][N], a[N * N], b[N][N], s[N][N];

void solve(){
	cin >> l >> n >> m;
	for(int i = 1; i <= l; i ++){
		cin >> a[i];
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			cin >> b[i][j];
			s[i][j] = 0;
		}
	}
	for(int k = 1; k <= l; k ++){
		for(int i = 1; i <= n; i ++){
			for(int j = 1; j <= m; j ++){
				dp[k][i][j] = 0;
			}
		}
	}
	 
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			dp[l][i][j] = (b[i][j] == a[l]);
			s[i][j] = dp[l][i][j];
		}
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= m; j ++){
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
			// cout << s[i][j] << " \n"[j == m];
		}
	}
	auto ask = [&] (int x1, int y1, int x2, int y2) {
		if(x1 > x2 || y1 > y2) return 0LL;
		return s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
	};
	for(int k = l - 1; k >= 1; k --){
		for(int i = 1; i <= n; i ++){
			for(int j = 1; j <= m; j ++){
				if(b[i][j] == a[k]) dp[k][i][j] = (ask(i + 1, j + 1, n, m) == 0);
			}
		}
		for(int i = 1; i <= n; i ++){
			for(int j = 1; j <= m; j ++){
				s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + (dp[k][i][j] != 0);
			}
		}
	}
	int res = 0;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		res |= dp[1][i][j];
        }
    }
    cout << (res ? "T" : "N") << '\n';
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