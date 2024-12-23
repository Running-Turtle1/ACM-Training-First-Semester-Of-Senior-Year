#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int x = 5;
	auto cal = [] (int x){
		return x + 1;
	};
	x = cal(x);
	cout << x;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}