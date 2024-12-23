#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, m;
string a, b;
int suma[N][26];
int sumb[N][26];

void solve(){
	cin >> n >> m >> a >> b;
	a = ' ' + a, b = ' ' + b;
	for(int i = 1; i <= n; i ++){
		for(int j = 0; j < 26; j ++){
			suma[i][j] = suma[i - 1][j];
		}
		suma[i][a[i] - 'a'] ++;
    }
    for(int i = 1; i <= n; i ++){
		for(int j = 0; j < 26; j ++){
			sumb[i][j] = sumb[i - 1][j];
		}
		sumb[i][b[i] - 'a'] ++;
    }
    // cout << suma[1][0] << '\n';
	while(m --){	
		int l, r;
		cin >> l >> r;
		int tmp = 0;
		for(int j = 0; j < 26; j ++){
			tmp += abs((suma[r][j] - suma[l - 1][j]) - (sumb[r][j] - sumb[l - 1][j]));
		}
		cout << tmp / 2 << '\n';
	}
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