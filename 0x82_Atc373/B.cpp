#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	string s;
	cin >> s;
	int now = -1;
	for(int i = 0; i < s.size(); i ++){
		if(s[i] == 'A') now = i;
	}
	// cout << now << '\n';
	int res = 0;
	for(int i = 2; i <= 26; i ++){
		char ch = 'A' + i - 1;
		for(int j = 0; j < s.size(); j ++){
			if(s[j] == ch){
				res += abs(j - now);
				now = j;
				// cout << j << ' ' << now << '\n';
				break;
			}
		}
	}
	cout << res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}