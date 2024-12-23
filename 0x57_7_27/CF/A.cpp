#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	cin >> n;
	cout << ((n % 4 == 0) ? n / 4 : n / 4 + 1) << '\n';
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