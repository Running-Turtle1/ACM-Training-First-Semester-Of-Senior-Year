#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n, a, b, g;
int v[N];

void solve(){
	cin >> n >> a >> b;
	g = __gcd(a, b);
	for(int i = 1; i <= n; i ++){
		cin >> v[i];
		v[i] %= g;
	}
	sort(v + 1, v + n + 1);
	int res = v[n] - v[1];
	for(int i = 1; i < n; i ++){ // [1, i] 翻转
		res = min(res, v[i] + g - v[i + 1]);
	}
	cout << res << '\n';
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