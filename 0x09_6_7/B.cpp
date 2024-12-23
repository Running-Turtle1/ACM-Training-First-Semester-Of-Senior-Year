#include<bits/stdc++.h>
using namespace std;
#define int long long

int const p = 998244353;
int const N = 1e7 + 10;

int Inv[N];
bool st[N];
int cnt, pm[N];
int n, LCM = 1;

void init(){
	// 线性逆元
	Inv[1] = 1;
	for(int i = 2; i <= n; i ++){
		Inv[i] = (p - p / i) * Inv[p % i] % p;
    }
    // 线性筛质数
    st[1] = true;
    for(int i = 2; i <= n; i ++){
    	if(!st[i]) pm[cnt ++] = i;
    	for(int j = 0; pm[j] <= n / i; j ++){
    		st[i * pm[j]] = true;
    		if(i % pm[j] == 0) break;
    	}
    }

    auto ksm = [] (int a, int k){
    	int res = 1;
    	while(k){
    		if(k & 1) res = res * a % p;
    		k >>= 1;
    		a = a * a % p;
    	}
    	return res;
    };
    for(int i = 1; i <= n; i ++){
    	if(!st[i]){ // i 是质数
			LCM = LCM * ksm(i, (int)(log(n) / log(i))) % p;
		}
    }
}

// (j, i) 相遇的次数
int f(int j, int i){
	return ((Inv[j] - Inv[i]) % p + p) % p;
}

void solve(){
	int res = 0, s = 0;
	cin >> n;
	init();
	for(int i = 1; i <= n; i ++){
		int tmp = (s - (i - 1) * Inv[i] % p) % p + p;
		res = (res + tmp) % p;
		s = (s + Inv[i]) % p;
    }
    cout << LCM * res % p << '\n';
}	

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}