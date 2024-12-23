#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int l, r;
	cin >> l >> r;
	int s = 0;
	for(int i = l; i <= r; i ++){
		s += (i & 1);
	}
	cout << s / 2 << '\n';
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