#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int const mod = 998244353;

int n, s0[N], s1[N];
string s;

void solve(){
	cin >> s;
	n = s.size();
	s = ' ' + s;
	for(int i = 1; i <= n; i ++){
		s0[i] = s0[i - 1] + (s[i] == '0');
		s1[i] = s1[i - 1] + (s[i] == '1');
    }
    vector<int> F(n + 1, 0);
    vector<int> f(n + 1, 0);
    int res = 0;
    map<int, int> mp;
    mp[0] ++;
    for(int i = 1; i <= n; i ++){
    	int v = s1[i] - s0[i];
    	F[i] = (F[i - 1] + mp[v]) % mod;
    	f[i] = (f[i - 1] + F[i]) % mod;
    	cout<<i<<' '<<mp[v]<<'\n';
    	mp[v] ++;

    }
    cout << f[n] << '\n';
    // for(int i )
    // cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	int T;
	cin >> T;
	while(T --){
		solve();
	}
	return 0;
}
