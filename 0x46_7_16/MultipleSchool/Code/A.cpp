#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, mod;
int C[5100][5100];
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
void solve(){
    cin >> n >> m >> mod;
    for(int i = 0; i <= n; i ++){
        C[i][0] = 1;
        for(int j = 1; j <= i; j ++){
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
        }
    }
    int res = 0;
    // 构造以几个 1 结尾
    for(int i = 1; i <= n; i ++){
        // 先构造 1 结尾的方案数
        int firstConstruct = C[n][i];
        int left = ksm(2LL, i, mod) - 1;
        left = (left % mod + mod) % mod;
        left = ksm(left, m - 1, mod);
        int haha = ksm(2, m - 1, mod);
        haha = ksm(haha, n - i, mod);
        // cout << i << ' ' << tmp*left*haha << '\n';
        res+=firstConstruct*left%mod*haha%mod;
        res%=mod;
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
