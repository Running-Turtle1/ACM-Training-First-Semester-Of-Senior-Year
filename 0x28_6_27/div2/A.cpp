#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, x1, y1, x2, y2;

void solve(){
	cin >> n;
	while(n --){
		cin >> x1 >> y1 >> x2 >> y2;
		if((x1 < y1 && x2 < y2) || (x1 > y1 && x2 > y2)){
			cout << "YES\n";
		}
		else{
			cout << "NO\n";
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
