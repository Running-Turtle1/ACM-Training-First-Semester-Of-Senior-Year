#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int x, y, k;
    cin >> x >> y >> k;
    if(!y){
        cout << x << '\n';
        return ;
    }
    if(x <= y){
        cout << ((k & 1) ? y - x : x) << '\n';
    }
    else{
        int t = (x / y);
        if(k > t){
            k -= t;
            x %= y;
            cout << ((k & 1) ? y - x : x) << '\n';
        }
        else{
            cout << x - k * y << '\n';
        }
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