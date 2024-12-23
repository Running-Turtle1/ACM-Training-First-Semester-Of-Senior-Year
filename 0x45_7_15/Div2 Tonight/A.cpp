#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;

void solve(){
	cin >> n >> k;
	int res = 0;
	while(true){
		if(n == 1) break;
		if(n >= k) n -= k;
		else n = 0;
		n ++;
		res ++;
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