#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n, k;
    cin >> n >> k;
    if(k == 1){
        cout << "0\n";
        return ;
    }
    -- k;
    vector<int> bit;
    while(n){
        bit.push_back(n % 10);
        n /= 10;
    }
    vector<int> t(bit.size() + 1);
    int l, r = 0, lasBit = 0;
    t[0] = 1;
    for(int i = 0; i < bit.size(); i ++){
        l = r + 1;
        r += t[i] * bit[i];
        if(r >= k){
            lasBit = i;
            break;
        }
        t[i + 1] = t[i] * (bit[i] + 1);
    }
    // cout << lasBit << '\n';
    for(int i = lasBit; i >= 0; i --){
        cout << (k / t[i]);
        k %= t[i];
    }
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	int T = 1;
	// cin >> T;
	while (T --){
		solve();
	}

	return 0;
}