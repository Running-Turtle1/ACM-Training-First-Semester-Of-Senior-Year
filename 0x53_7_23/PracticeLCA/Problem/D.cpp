#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	string s;
	int const mod = 1e9 + 7;
	cin >> n >> s;
	s = ' ' + s;

	int ans = 0;
	vector<int> f(n + 1), g(n + 1), sum(n + 1);
	auto ask = [&] (int l, int r) {return sum[r] - sum[l - 1]; };
	for(int i = 1; i <= n; i ++){
		sum[i] = sum[i - 1] + s[i] == '0';
		g[i] = ((g[i - 1] + 1) * 2 - 1) % mod;
		f[i] = f[i - 1] + f[i - 1] + ask(1, i - 1);
		f[i] %= mod;
		if((s[i] - '0') % 2 == 0){
			ans = ans + g[i - 1] - f[i - 1] - ask(1, i - 1) + 1;
			ans %= mod;
		}
    }
    cout << ans << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
