#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n = 12, res = 0;
	for(int i = 1; i <= n; i ++){
		string s;
		cin >> s;
		if(s.size() == i) res ++;
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