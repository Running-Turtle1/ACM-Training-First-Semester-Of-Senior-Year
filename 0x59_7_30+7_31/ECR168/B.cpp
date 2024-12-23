#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n;
char g[3][N];

void solve(){
	cin >> n;
	for(int i = 1; i <= 2; i ++){
		for(int j = 1; j <= n; j ++){
			cin >> g[i][j];
		}
	}
	int res = 0;
	for(int j = 2; j < n; j ++){
		string s1 = "";
		s1 += g[1][j - 1];
		s1 += g[1][j];
		s1 += g[1][j + 1];
		string s2 = "";
		s2 += g[2][j - 1];
		s2 += g[2][j];
		s2 += g[2][j + 1];
		if((s1 == "x.x" && s2 == "...")){
			res ++;
		}
		if((s2 == "x.x" && s1 == "...")){
			res ++;
		}
	}
	cout << res << '\n';
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