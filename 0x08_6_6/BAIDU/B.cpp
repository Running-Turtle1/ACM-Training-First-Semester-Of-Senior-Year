#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 998244353;
int Inv[10000010];
void LinearCalInv(int n){
	Inv[1] = 1; 
	for(int i = 2; i <= n; i ++){
		Inv[i] = (mod - mod / i) * Inv[mod % i] % mod;
	}
}

bool st[10000010];
int cnt, pm[10000010];
void init(int n){
	st[1] = true;
	for(int i = 2; i <= n; i ++){
		if(!st[i]) pm[cnt ++] = i;
		for(int j = 0; pm[j] <= n / i; j ++){
			st[i * pm[j]] = true;
			if(i % pm[j] == 0) break;
		}
    }
}

int n;

int ksm(int a, int b){
	int res=1;
	while(b){
		if(b&1)res=res*a%mod;b>>=1;a=a*a%mod;
	}
	return res;
}

void solve(){
	cin >> n;
	LinearCalInv(10000000);
	init(10000000);
	int m = 1;
	for(int i = 1; i <= n; i ++){
		if(!st[i]){
			// cout<<"i: "<<i<<' '<<(int)(log(n) / log(i))<<'\n';
			m = m * ksm(i,(int)(log(n) / log(i))) % mod;
		}
    }
    // cout << m << '\n';
	int ans = 0;
	int s = 0;
	for(int i = 1; i <= n; i ++){
		(ans += (s - (i - 1) * Inv[i] + mod) % mod * m % mod) %= mod;
		(s += Inv[i]) %= mod;
    }
    cout << (ans+mod)%mod << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}