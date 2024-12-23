#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
string s;

void solve(){
	cin >> n >> s;
	s = ' ' + s;
	int c0 = 0, c1 = 0;
	for(int i = 1; i <= n; i ++){
		if(s[i] == '1'){
			c1 ++;
			continue;
		}
		int j = i;
		while(j <= n && s[j] == '0') j ++;
		i = j - 1;
		c0 ++;
	}
	cout << (c1 > c0 ? "Yes" : "No") << '\n';
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