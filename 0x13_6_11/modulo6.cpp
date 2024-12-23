#include<bits/stdc++.h>
using namespace std;
#define int long long

int const p = 998244353;
int const N = 1e5 + 10;

int Fact[N], Inv[N];

int ksm(int a, int k, int p){
    int res = 1;
    while(k){
        if(k & 1) res = res * a % p;
        k >>= 1;
        a = a * a % p;
    }
    return res;
}

void initInv(int n){
    Fact[0] = 1;
    for(int i = 1; i <= n; i ++){
        Fact[i] = Fact[i - 1] * i % p;
    }
    Inv[n] = ksm(Fact[n], p - 2, p);
    for(int i = n - 1; i >= 0; i --){
        Inv[i] = Inv[i + 1] * (i + 1) % p;
    }
}

int C(int n, int m){
    return Fact[n] * Inv[m] % p * Inv[n - m] % p;
}

void solve(){
    int m, n;
    cin >> n >> m;
    cout << C(n - 1, m - 1) * Fact[n] % p << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    initInv(100000);
    int t;
    cin>>t;
    while(t--)
    solve();
    return 0;
}