#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	cin >> n;
	if(n & 1) cout << "No";
	else cout << "Yes";
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}