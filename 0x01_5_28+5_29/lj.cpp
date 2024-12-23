#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	cin >> n;
	for(int i = 2; i <= n / i; i ++){
		int s = 0;
		while(n % i == 0) n /= i, s ++;
		cout << i << ' ' << s << '\n';
	}
	if(n > 1) cout << n << ' ' << 1 << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

2
2 9
3 5
考虑到 i 有几种方案
dp[i] = 