#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, m, q, a, b, c, d, e, f;

int in[N];

void solve(){
	int res = 0; // 已经经过的进攻回合
	cin >> n;
	auto f = [&] (int x) -> int {
		if(res % 3 == 0){
			return x / 3 * 5 + x % 3;
		}
		if(res % 3 == 1){
			if(x == 1) return 1;
			if(x == 2) return 4;
			x -= 2;
			return 4 + x / 3 * 5 + x % 3;
		}
		if(res % 3 == 2){
			if(x == 1) return 3;
			-- x;
			return 3 + x / 3 * 5 + x % 3;
		}
		return 0;
	};
	// cout << f(4) << '\n';
	for(int i = 1; i <= n; i ++){
		cin >> q;
		int l = 1, r = 1e9;
		while(l < r){	
			int mid = l + r >> 1;
			if(f(mid) >= q) r = mid;
			else l = mid + 1;
		}
		// cout << i << ' ' << l << '\n';
		res += l;
    }
    cout << res;
    // int l = 0, r = 1e18;
    // while(l < r){
    	// int mid = l + r >> 1;
    	// if(mid / 3 * 3 + mid % 3 >= s) r = mid;
    	// else l = mid + 1;
    // }
    // cout << l;
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