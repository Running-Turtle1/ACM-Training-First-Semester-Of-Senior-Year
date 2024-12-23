// 0000000111111111111111111

// 111111111111111111

// 000000000000000000000

#include<bits/stdc++.h>
using namespace std;
#define int long long

string s, t;

void solve(){
	t = "";
	cin >> s;
	for(int i = 0; i < s.size(); i ++){
		t += s[i];
		int j = i;
		while(j < s.size() && s[j] == s[i]) j ++;
		i = j - 1;
	}
	int res = 0;
	// for(int i = 0; i < t.size(); i ++){
	// 	if(t[i] == '1') res ++;
	// 	else{
	// 		if(i + 1 < t.size() && t[i + 1] == '1'){
	// 			res ++;
	// 			i ++;
	// 		}
	// 		else{
	// 			res ++;
	// 		}
	// 	}
	// }
	// cout << res << '\n';
	int n = t.size();
	int s=0;
	for(int i=0;i+1<n;i++)if(t[i]=='0'&&t[i+1]=='1')s=1;
	cout <<n-s<<'\n';
	// if(t[0] == '0'){
	// 	cout << ((n & 1) ? (n - 2) / 2 + 1 : (n - 2) / 2) << '\n';
	// }
	// else{
	// 	cout <<((n & 1) ? (n - 1) / 2 : n / 2) << '\n';
	// }
}
// 1010
// 000000 : 视为 1 个 0
// 111111 : 视为一个 1

// 01 : 第 1 个 01 不操作, 后面的需要把 0 剪出来
// 10 : 把 0 剪出来

// 0101 : (n - 2) / 2
// 01010 : (n - 2) / 2 + 1
// 1010 : n / 2
// 10101 : (h - 1) / 2

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