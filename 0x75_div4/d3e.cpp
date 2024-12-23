#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;

int f(int x){
	return 2LL * x * x + (4LL * k - 2) * x;
}

void solve(){
	cin >> n >> k;
	int lim = n * n + 2LL * n * k - n;
	int l = 1, r = n;
	while(l < r){
		int mid = l + r + 1 >> 1;
		if(f(mid) <= lim) l = mid;
		else r = mid - 1;
	}
	int res = (lim - f(l)) / 2;
	if(l != n){
		res = min(res, (f(l + 1) - lim) / 2);
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