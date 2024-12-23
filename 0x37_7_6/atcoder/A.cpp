#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k, x;

void solve(){
	cin >> n >> k >> x;
	for(int i = 1; i <= n; i ++){
		int j;
		cin >> j;
		cout << j << ' ';
		if(i == k) cout << x << ' ';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
