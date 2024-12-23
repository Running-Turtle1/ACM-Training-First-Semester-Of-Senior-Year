#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, a[N], las[N];

void solve(){
	int res = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		res += (i - las[a[i]]) * (n - i + 1);
		las[a[i]] = i;
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
