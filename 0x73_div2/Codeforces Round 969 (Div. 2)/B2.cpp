#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, m, x, mx;

void solve(){
	cin >> n >> m;
	mx = -2e9;
	for(int i = 1; i <= n; i ++){
		cin >> x;
		mx = max(mx, x);
	}
	for(int i = 1; i <= m; i ++){
		char op;
		int l, r;
		cin >> op >> l >> r;
		if(op == '+'){
			if(l <= mx && mx <= r) mx ++;
		}
		if(op == '-'){
			if(l <= mx && mx <= r) mx --;
		}
		cout << mx << " \n"[i == m];
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