#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, x, y, k;

void solve(){
	cin >> x >> y >> k;
	while(true){
		if(x == 1) break;
		int need = ((x + y - 1) / y) * y - x;
		if(!need) need = y;
		if(k < need) break;
		k -= need;
		x += need;
		while(x % y == 0) x /= y;
	}
	if(x != 1){
		x += k;
	}
	else{
		x = 1 + k % (y - 1);
	}
	cout << x << '\n';
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
// log_y 看看走几步能变成 1
// 