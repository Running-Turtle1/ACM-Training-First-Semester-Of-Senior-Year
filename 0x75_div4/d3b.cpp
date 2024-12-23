#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N = 1e6 + 10;
char s[N][5];

void solve(){
	int n;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= 4; j ++){
			cin >> s[i][j];
		}
	}
	for(int i = n; i >= 1; i --){
		for(int j = 1; j <= 4; j ++){
			if(s[i][j] == '#'){
				cout << j << ' ';
			}
		}
	}
	cout << '\n';
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