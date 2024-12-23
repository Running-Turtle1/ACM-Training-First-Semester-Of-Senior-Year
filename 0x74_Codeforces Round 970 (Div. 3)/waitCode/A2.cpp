#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int a, b;
	cin >> a >> b;
	
	bool fg = false;
	int n = a + b;
	for(int i = 0; i < (1 << n); i ++){
		int res = 0;
		for(int j = 0; j < n; j ++){
			int t = (j < a ? 1 : 2);
			if(i >> j & 1){ // +
				res += t;
			}
			else{ // -
				res -= t;
			}
		}
		if(res == 0) fg = true;
	}

	cout << (fg ? "YES" : "NO") << '\n';
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