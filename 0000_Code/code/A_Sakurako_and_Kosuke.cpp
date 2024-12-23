#include<bits/stdc++.h>
using namespace std;
#define int long long

// shift + alt + arrow
// ctrl + d
// F5 / F6
// ctrl + alt + B

void solve(){
    int n, m, r, c;
	cin >> n >> m >> r >> c;
	cout << (m - c) + (n - r) * m + (n - r) * (m - 1) << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
 