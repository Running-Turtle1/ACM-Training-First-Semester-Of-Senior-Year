#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n, now = 0;
	cin >> n;

	int r = 1;
	while(true){
		if(r & 1) now -= 2 * r - 1;
		else now += 2 * r - 1;
		if(abs(now) > n) break;
		r ++;
	}
	if(r & 1){
		cout << "Sakurako\n";
	}
	else{
		cout << "Kosuke\n";		
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