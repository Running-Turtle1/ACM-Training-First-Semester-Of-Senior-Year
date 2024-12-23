#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 998244353;

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
	x %= mod;
	return ksm(x, mod - 2, mod);
}
int n, k;
void solve(){
	cin >> n >> k;
	int p = 2LL * inv(n * n) % mod;
	for(int i = 2; i <= k; i ++){
		int t1 = 2LL * inv(n * n) % mod;
		int t2 = ((n * n % mod - 2 * n) % mod + mod) % mod;
		t2 = t2 * inv(n * n) % mod;
		p = (t1 + t2 * p % mod) % mod;
	}
	int res = 0; 
	int tmp = ((n * (n + 1) % mod * inv(2LL) - 1) % mod + mod) % mod;
	res = tmp * p % mod; 

	(p = (n * n % mod - 2 * n + 2) % mod + mod) %= mod;
	p = p * inv(n * n) % mod;
	for(int i = 2; i <= k; i ++){
		int t1 = 2LL * inv(n * n) % mod;
		int t2 = ((n * n % mod - 2 * n) % mod + mod) % mod;
		t2 = t2 * inv(n * n) % mod;
		p = (t1 + t2 * p % mod) % mod;
	} 
	(res += p) %= mod;
	cout << res << '\n'; 
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
