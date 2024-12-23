#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n, m, q;
	cin >> n >> m >> q;

	vector<int> b(m + 1, 0);
	for(int i = 1; i <= m; i ++){
		cin >> b[i];
	}
	sort(b.begin() + 1, b.begin() + m + 1);
	for(int i = 1; i <= q; i ++){
		int x;
		cin >> x;
		if(x > b[m]) cout << n - b[m] << '\n';
		else if(x < b[1]) cout << b[1] - 1 << '\n';
		else{
			int p = lower_bound(b.begin() + 1, b.begin() + m + 1, x) - b.begin();
			cout << (b[p] - b[p - 1]) / 2 << '\n';
		}
	}
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