#include<bits/stdc++.h>
using namespace std;
#define int long long
// 显然贪心来填
void solve(){
	int l, r;
	cin >> l >> r;
	int cnt = 1, t = 1;
	while(true){
		l += t ++;
		if(l > r) break;
		cnt ++;
	}
	cout << cnt << '\n';
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