#include<bits/stdc++.h>
using namespace std;
#define int long long

int power2[32];

int xor1_n(int x){
    if(x % 4 == 0) return x;
    else if(x % 4 == 1) return 1LL;
    else if(x % 4 == 2) return x + 1;
    return 0LL;
}

int xorl_r(int l, int r){
    if(!l) l = 1;
    return xor1_n(r) ^ xor1_n(l - 1);
}

void solve(){
    int l, r, i, k;
    cin >> l >> r >> i >> k;
    int res = xorl_r(l, r);
    if(k <= r) { // 有解的条件
        r -= k, l -= k;
        if(l < 0) l = 0;
        l = (l + power2[i] - 1) / power2[i], r /= power2[i];
        res ^= (power2[i] * (xorl_r(l, r) )) ^ (((r - l + 1) & 1) * k);
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

    power2[0] = 1;
    for(int i = 1; i <= 30; i ++) power2[i] = power2[i - 1] * 2;

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}