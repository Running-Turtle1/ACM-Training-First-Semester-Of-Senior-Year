#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	cin >> n;

	char ch[] = {'a', 'e', 'i', 'o', 'u'};
	for(int i = 0; i < 5; i ++){
		char x = ch[i];
		// cout << x << '\n';continue;
		cout << string(n / 5, x);
		if((i + 1) <= n % 5) cout << x;
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