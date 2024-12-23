#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	string s;
	cin >> s;
	if(s.size() == 3){
		if(s.substr(0, 2) == "10" && s[2] >= '2'){
			cout << "Yes\n";
			return ;
		}
	}
	else if(s.size() >= 4 && s.substr(0, 2) == "10"){
		if(s[2] >= '1'){
			cout << "Yes\n";
			return ;
		}
	}
	cout << "No\n";
	return ;
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