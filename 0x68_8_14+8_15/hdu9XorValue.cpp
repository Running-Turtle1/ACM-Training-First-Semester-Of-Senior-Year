#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int const mod = 998244353;

int n, k;
int fact[N];

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

int C(int n, int m){
	// cout << fact[n] << ' ' << fact[m] << ' ' << fact[n - m] << '\n';
	return fact[n] * inv(fact[m]) % mod * inv(fact[n - m]) % mod;
}

void solve(){
	cin >> n >> k;
	// cout << n << ' ' << k << '\n';
	for(int i = 1; i < n; i ++){
		int x;
		cin >> x;
    }
	int t = C(n, n / 2);
	// cout << t << '\n';
	if(n & 1) t = t * 2 % mod;
	cout << ksm(t, k, mod) << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	fact[0] = 1;
	for(int i = 1; i < N; i ++){
		fact[i] = fact[i - 1] * i % mod;
    }

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}
1
