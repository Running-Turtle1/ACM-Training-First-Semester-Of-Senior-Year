#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
string s;

void solve(){
	cin >> n >> k >> s;
	s = ' ' + s;

	// if(k > n * (n - 1) / 2) {
	// 	cout << "-1\n";
	// 	return ;
	// }

	int cnt = 0;
	vector<int> vc;
	for(int i = n; i >= 2; i --) {
		if(s[i] == '1') ++ cnt;
		else -- cnt;
		vc.push_back(cnt);
	}

	sort(vc.begin(), vc.end(), [&] (auto a, auto b) {
		return a > b;
	});

	int sum = 0;
	for(int i = 0; i < vc.size(); i ++) {
		sum += (vc[i]);
		// cout << i << ' ' << sum << '\n';
		if(sum >= k) {
			cout << i + 2 << '\n';
			return ;
		}
	}

	cout << "-1\n";
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