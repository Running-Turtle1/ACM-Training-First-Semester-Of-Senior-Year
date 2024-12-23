#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 1e9 + 7;
int const N = 2e5 + 10;
int const sz = 20;

int n, a[N];
int s0[N][sz], s1[N][sz];

map<tuple<int, int, int>, int> mp;
int ksm(int a, int k, int p){
	if(mp.count({a, k, p})) return mp[{a, k, p}];
    int res = 1;
    a %= p;
    while(k){
        if(k & 1) res = res * a % p;
        k >>= 1;
        a = a * a % p;
    }
    return mp[{a, k, p}] = res;
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		for(int j = 0; j < sz; j ++){
			s0[i][j] = s0[i - 1][j] + ((a[i] >> j & 1) == 0);
			s1[i][j] = s1[i - 1][j] + ((a[i] >> j & 1) == 1);
		}
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	for(int j = 0; j < sz; j ++){
    		int num1 = s1[i - 1][j], num0 = s0[i - 1][j];
    		int now = (a[i] >> j & 1);
    		if(now == 1){
    			int cnt = 0;
    			if(num1 == 0) cnt = ksm(2LL, num0, mod);
    			else cnt = ksm(2LL, num0, mod) * ksm(2LL, num1 - 1, mod) % mod;
    			res = (res + cnt * (1LL << j) % mod) % mod;
    		}
    		else{ // 当前是 0
    			int cnt = 0;
    			if(num1) cnt = ksm(2LL, num0, mod) * ksm(2LL, num1 - 1, mod) % mod;
    			res = (res + cnt * (1LL << j) % mod) % mod;
    		}
    	}
    	// cout << i << ' ' << res << '\n';
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
