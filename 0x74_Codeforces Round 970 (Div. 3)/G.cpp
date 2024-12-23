#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, q, x, a[N], cnt[N], s[N];

int ask(int l, int r){
	if(l == 0){
		return s[r];
	}
	return s[r] - s[l - 1];
}

void solve(){
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cnt[i] = 0;
	}
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		cnt[a[i]] ++;
	}
	for(int i = 0; i <= n; i ++){
		if(i == 0){
			s[0] = cnt[0];
			continue ;
		}
		s[i] = cnt[i] + s[i - 1];
		cout << i << ' ' << s[i] << '\n';
	}
	int need = ((n & 1) ? (n + 1) / 2 : (n / 2 + 1));
	vector<int> f(n + 1, -1);
	// cout<<ask(0,0)<<' '<<ask(2,2)<<' '<<ask(4,4)<<'\n';
	// int mid = 0, x = 2;
	// int tmp = 0;
	// 		for(int i = 0; i <= n; i += x){
	// 			cout << "ask: " << i << ' ' << i + mid << '\n';
	// 			tmp += ask(i, i + mid);
	// 		}
	// 		tmp --;
	// cout << tmp << '\n';
	for(int i = 1; i <= q; i ++){
		// cout << "In\n";
		cin >> x;
		if(f[i] != -1) cout << f[i] << ' ';
		int l = 0, r = x - 1;
		while(l < r){
			int mid = l + r + 1 >> 1; // 二分中位数
			int tmp = 0;
			bool fg = false;
			for(int i = 0; i <= n; i += x){
				tmp += ask(i, i + mid - 1);
				// if(ask(i + mid, i + mid)) fg = true;
			}
			// tmp -= ask()
			// cout << "mid: " << mid << ' ' << tmp << '\n';
			// tmp --;
			if(tmp <= need) l = mid;
			else r = mid - 1;
		} 
		f[i] = l;
		cout << f[i] << ' ';
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