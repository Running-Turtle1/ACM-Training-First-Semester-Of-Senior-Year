#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int N = 1E5 + 10;
constexpr int mod = 998244353;

int fact[N], infact[N];

int ksm(int a, int k){
    a %= mod;
    int res = 1;
    while(k){
        if(k & 1) res = res * a % mod;
        k >>= 1;
        a = a * a % mod;
    }
    return res;
}

int m, n;

unordered_map<int, int> f[N];

void solve(){
    fact[0] = 1;
    for(int i = 1; i < N; i ++){
        fact[i] = fact[i - 1] * i % mod;
    }
    infact[N - 1] = ksm(fact[N - 1], mod - 2);
    for(int i = N - 2; i >= 0; i --){
        infact[i] = infact[i + 1] * (i + 1) % mod;
    }
    cin >> m >> n;
    auto C = [&] (int n, int m){
        if(m < 0 || m > n) return 0LL;
        return fact[n] * infact[m] % mod * infact[n - m] % mod;
    };
    
    for(int x = 1; x <= m; x ++){
        f[1][x] = 1;
    }
    int res = n * C(m, n) % mod;
    for(int i = 1; i <= n; i ++){
        for(auto &[x, y] : f[i]){
            res = res - f[i][x] * C(m / x - 1, n - i) % mod;
            res %= mod;
            if(res < 0) res += mod;
            // f[i][x] = y;
            for(int j = 2; j * x <= m && i + 1 <= n; j ++){
                (f[i + 1][j * x] += f[i][x]) %= mod;
            }
        }
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
