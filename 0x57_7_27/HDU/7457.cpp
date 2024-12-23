#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 998244353;  

void solve(){
	int n;
	cin >> n;
	vector<int> f(n + 2, 0), F(n + 1, 0); 
	f[1] = 1;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j * i <= n; j ++){
			f[j * i + 1] = (f[j * i + 1] + f[i]) % mod;
		}
	}
	for(int i = 1; i <= n; i ++){
		for(int j = i; j <= n; j += i){
			F[j] = (F[j] + f[i]) % mod;
		}
	}
	for(int i = 1; i <= n; i ++){
		cout << F[i] << " \n"[i == n];
    }
}



signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
