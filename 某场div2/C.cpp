#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
string s;

void solve(){
	cin >> n >> k >> s;
	s = ' ' + s;

	int delta = 0;
	vector<int> vc;
	for(int i = n; i >= 1; i --) {
		if(s[i] == '1') delta ++;
		else delta --;
		if(delta >= 0) {
			vc.push_back(delta);
			delta = 0;
		}
	}
	if(delta < 0) {
		vc.push_back(delta);
	}

	int sz = vc.size();
	// cout << sz << '\n';
	// for(int i = sz - 1; i >= 0; i --) {
	// 	cout << vc[i] << " \n"[i == 0];
	// }

	int mxScore = 0;
	for(int i = sz - 1; i >= 0; i --) {
		// cout << (sz - 1 - i) << ' ' << vc[i] << '\n';
		mxScore += (sz - 1 - i) * vc[i];
	}
	// cout << mxScore << '\n';
	if(k > mxScore) {
		cout << "-1\n";
		return ;
	}

	int sum = 0;
	for(int i = 0; i < sz; i ++) {
		sum += vc[i];
		mxScore -= sum;
		// cout << i << ' ' << mxScore << '\n';
		if(mxScore < k || vc[i] < 0) {
			// 此时合并了 i 个分组
			cout << sz - i << '\n';
			// cout << (sz + 1) - (i + 1) << '\n';
			return ;
		}
	}
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