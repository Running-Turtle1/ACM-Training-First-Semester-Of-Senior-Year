#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 1e9 + 7;
int const N = 310;

int n, m, k;
int w[N], f[N][N * N];
int s[N * N];

int ksm(int a, int k){
	int res = 1;
	while(k){
		if(k & 1) res = res * a % mod;
		a = a * a % mod;
		k >>= 1;
	}
	return res;
}

int const sz = 1e7 + 10;
int inv[sz], fact[sz];
void init(int n){
	fact[0] = 1;
	for(int i = 1; i <= n; i ++){
		fact[i] = fact[i - 1] * i % mod;
	}
	inv[n] = ksm(fact[n], mod - 2);
	for(int i = n - 1; i >= 0; i --){
		inv[i] = inv[i + 1] * (i + 1) % mod;
    } 
}
int C(int n, int m){
	return fact[n] * inv[m] % mod * inv[n - m] % mod;
}

void solve(){
	int mxCost = 0;
	cin >> n >> m >> k;
	if(m >= n) m = n; 
	for(int i = 1; i <= m; i ++){
		cin >> w[i];
		mxCost += w[i];
    }
    // f[i][j] 考虑到 i 花费 j 元的方案数
    for(int i = 1; i <= m; i ++){
    	for(int j = 0; j <= mxCost; j ++){
        	if(!j) s[j] = 1;
        	else s[j] = (s[j - 1] + f[i - 1][j]) % mod;
        }
        // 前缀和优化 DP
        for(int j = 0; j <= mxCost; j ++){
        	// [j - w[i], j]
        	if(j - w[i] <= 0) f[i][j] = s[j];
        	else f[i][j] = s[j] - s[j - w[i] - 1];
            f[i][j] = (f[i][j] % mod + mod) % mod;
        }
    }

    int res = 0;
    if(m == n){
    	cout << f[n][k] << '\n';
    	return ;
    }
    
    for(int i = 0; i <= mxCost; i ++){
    	if(i > k) break;
    	res = res + f[m][i] * C(k - i + n - m - 1, n - m - 1) % mod;
    	res %= mod;
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	init(sz - 1);
	solve();
	return 0;
}