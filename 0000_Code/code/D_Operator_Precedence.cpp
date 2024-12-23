#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n;
    cin >> n;

    cout << 2 * n - 3 << ' ';

    for(int i = 1; i <= n - 1; i ++){
        cout << "2 -1 ";
    }

    cout << 1 << '\n';
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