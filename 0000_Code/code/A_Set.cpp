#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int l, r, k;
    cin >> l >> r >> k;
    r /= k;
    cout << max(0LL, r - l + 1) << '\n';
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