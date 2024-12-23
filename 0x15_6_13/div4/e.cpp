#include<bits/stdc++.h>
using namespace std;
#define int long long

int x, y, z, k;

void solve(){
	cin >> x >> y >> z >> k;
	int res = 0;
	// 每一维不能超过 2000
	for(int a = 1; a <= x; a++){
    	for(int b = 1; b <= y; b++){
        	if(k % (a * b) != 0) continue;
        	// 这里继续你要执行的代码逻辑
        	int c = k / (a * b);
        	res = max(res, (x - a + 1) * (y - b + 1) * (z - c + 1));
    	}
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