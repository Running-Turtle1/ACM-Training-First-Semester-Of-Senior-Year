#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
string s;

void solve(){
	cin >> n >> s;
	string t = s;
	sort(s.begin(), s.end());
	for(int i = 0; i < n; i ++){
		if(isdigit(s[i]) == false && islower(s[i]) == false){
			cout << "NO\n";
			return ;
		}
	}
	if(s == t) cout << "YES\n";
	else cout << "NO\n";
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