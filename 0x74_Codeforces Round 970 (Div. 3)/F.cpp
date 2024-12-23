#include<bits/stdc++.h>
using namespace std;
#define int long long

// 简单概率期望

int const N = 2e5 + 10;
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

int n, sum, a[N];

void solve(){
	sum = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		sum = (sum + a[i]) % mod;
	}

	int res = 0;
	for(int i = 1; i <= n; i ++){
		int t = (sum - a[i]) % mod;
		if(t < 0) t += mod;
		res = (res + a[i] * t % mod) % mod;
	}
	// cout << res << '\n';
	cout << res * inv(n * (n - 1) % mod) % mod << '\n';
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