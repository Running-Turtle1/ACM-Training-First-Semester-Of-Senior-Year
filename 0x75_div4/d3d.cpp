#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n, s1, s2, x, y;
	cin >> n;
	s1 = s2 = 0;
	map<pair<int, int>, int> mp;
	for(int i = 1; i <= n; i ++){
		cin >> x >> y;
		mp[{x, y}] = 1;
	}
	int res = 0, ans = 0;
	for(int i = 0; i <= n; i ++){
		if(mp[{i, 0}] && mp[{i, 1}]){
			// ans += n - 2;
			res += n - 2;
		}
		if(mp[{i, 0}] && mp[{i + 2, 0}] && mp[{i + 1, 1}]){
			res ++;
		}
		if(mp[{i, 1}] && mp[{i + 2, 1}] && mp[{i + 1, 0}]){
			res ++;
		}
	}
	cout << res + ans / 2 << '\n';
	// if(!s1 || !s2){
	// 	cout << "0\n";
	// }
	// else{
	// 	cout << s1 * (s1 - 1) / 2 * s2 + s2 * (s2 - 1) / 2 * s1 << '\n';
	// }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}