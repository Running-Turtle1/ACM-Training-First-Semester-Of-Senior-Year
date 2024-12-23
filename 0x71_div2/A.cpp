#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	string s;
	cin >> n >> s;
	cout << (s[0] == s[n - 1] ? "No\n" : "Yes\n");
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