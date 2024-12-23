#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 1e9 + 7;

string s;

// int sol(int n, vector<int> &v){
// 	int res = 0, s = 0;
// 	for(int i = 0; i < v.size(); i ++){
// 		res = res + i * (n + 1 - v[i]) + s;
// 		res = (res % mod + mod) % mod;
// 		s = (s + v[i]) % mod;
// 	}
// 	return res;
// }

int sol(int n, vector<int> &v){
	int sz = v.size();
	vector<int> s(sz + 1, 0);
	for(int i = 0; i < sz; i ++){
		if(i) s[i] = s[i - 1] + v[i] + 1;
		else s[i] = v[i] + 1;
	}
	int res = 0;
	for(int i = 0; i < sz; i ++){
		if(i){
			res += (n - v[i] + 1) * s[i - 1];
			res %= mod;
		}
	}
	return res;
}

void solve(){
	cin >> s;
	int n = s.size();
	s = ' ' + s;
	vector<vector<int> > sum(n + 1, vector<int> (2, 0));
	vector<vector<int> > v(n + 2);
	map<int, int> mp;
	int cnt = 0;
	for(int i = 1; i <= n; i ++){
		sum[i][0] = sum[i - 1][0] + (s[i] == '0');
		sum[i][1] = sum[i - 1][1] + (s[i] == '1');
    }
    // cout << "Nep\n";
    for(int i = 0; i <= n; i ++){
    	int tmp = sum[i][1] - sum[i][0];
    	// cout << "Uh\n";
    	if(mp.count(tmp) == false){
    		mp[tmp] = ++ cnt;
    	}
   		v[mp[tmp]].push_back(i);
   		// cout << "X\n";
    }
    // cout << "Nep\n";
    // cout << "cnt: " << cnt << '\n';
    // for(int i = 1; i <= cnt; i ++){
    // 	for(auto &x : v[i]){
    // 		cout << x << ' ';
    // 	}
    // 	cout << '\n';
    // }

    int res = 0;
    for(int i = 1; i <= cnt; i ++){
    	// cout << i << ' ' << sol(n, v[i]) << '\n';
    	(res += sol(n, v[i])) %= mod;
    }
    cout << res << '\n';
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
