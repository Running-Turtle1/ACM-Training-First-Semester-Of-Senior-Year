#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	string s;
	cin >> s;
	int pos = -1;
	for(int i = 0; i + 1 < s.size(); i ++){
		if(s[i] == s[i + 1]){
			pos = i;
		}
	}
	for(int i = 0; i < s.size(); i ++){
		cout << s[i];
		if(i == pos){
			if(s[i] == 'z') cout << 'a';
			else cout << (char)(s[i] + 1);
		}
	}
	if(pos == -1){
		if(s.back() == 'z') cout << 'a';
		else cout << (char)(s.back() + 1);
	}
	cout << '\n';
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