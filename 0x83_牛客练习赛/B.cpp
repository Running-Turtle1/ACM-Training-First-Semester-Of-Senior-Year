#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 1e9 + 7;

int ksm(int a, int k, int p){
    int res = 1;
    a %= p;
    while(k){
        if(k & 1) res = res * a % p;
        k >>= 1;
        a = a * a % p;
    }
    return res;
}
int inv(int x){
	return ksm(x, mod - 2, mod);
}
int const N = 1e6 + 10;
int fac[N];
int C(int n, int m){
	return fac[n] * inv(fac[m]) % mod * inv(fac[n - m]) % mod;
}

void solve(){
	int n, m, res;
	cin >> n >> m;
	res = ksm(2LL, m, mod) - 2;
	res = (res % mod + mod) % mod;
	res = ksm(res, n, mod) ;
	cout << res << '\n';
	// if(n == 1){
	// 	res = ksm(2LL, m, mod) - 2;
	// 	res = (res % mod + mod) % mod; 
	// }
	// else if(n > m){
	// 	res = 0;
	// }
	// else{
	// 	res = ksm(n + 1, m - n, mod);
	// }
	// cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	fac[0] = 1;
	for(int i = 1; i < N; i ++){
		fac[i] = i * fac[i - 1] % mod;
	}

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}