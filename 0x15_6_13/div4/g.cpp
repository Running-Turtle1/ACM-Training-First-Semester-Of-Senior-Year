#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 1e9 + 7;

int l, r, k;

int ksm(int a, int k){
	int res = 1;
	while(k){
		if(k & 1) res = res * a % mod;
		k >>= 1;
		a = a * a % mod;
	}
	return res;
}

void solve(){
	cin >> l >> r >> k;
	int x = 9 / k;
	// int res = x; // 首项
	// int tmp = 0;
	// for(int i = l; i < r; i ++){
	// 	int tmp = 0;
	// }
	// cout << res * tmp << '\n';
	int res = ksm(x + 1, l) * (ksm(x + 1, r - l) - 1) % mod;
	cout << (res + mod) % mod << '\n';

	// for(int i = l; i <= r; i ++){
	// 	res = res + ksm(x + 1, i - 1);
	// 	res = res * x;
	// }
	// cout << res << '\n';
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