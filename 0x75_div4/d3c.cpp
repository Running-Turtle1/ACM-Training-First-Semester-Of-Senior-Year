#include<bits/stdc++.h>
using namespace std;
#define int long long

int a, b, k;

void solve(){
	cin >> a >> b >> k;
	int ta = (a + k - 1) / k;
	int tb = (b + k - 1) / k;
	if(tb >= ta){
		cout << 2 * tb << '\n';
	}
	else{
		cout << 2 * ta - 1 << '\n';
	}
	// cout << max((b + k - 1) / k, (a + k - 1) / k) << '\n';
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