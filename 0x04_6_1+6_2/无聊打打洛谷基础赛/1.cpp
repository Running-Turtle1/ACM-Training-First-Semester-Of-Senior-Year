#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	string s;
	cin >> s;
	int res = 0;
	for(auto x : s){
		if(x >= 'A' && x <= 'Z') continue;
		res += min(abs('A' - x), abs('Z' - x));
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