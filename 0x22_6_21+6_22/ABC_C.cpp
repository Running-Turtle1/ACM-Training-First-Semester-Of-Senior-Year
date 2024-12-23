#include<bits/stdc++.h>
using namespace std;
#define int long long

int sx, sy, tx, ty;

void solve(){
	cin >> sx >> sy >> tx >> ty;
	int mn = abs(ty - sy);
	int l, r;
	if((sx & 1) == (sy & 1)){
		l = sx;
		r = sx + 1;
	}
	else{
		l = sx - 1;
		r = sx;
	}
	l -= mn, r += mn;
	// cout << l << ' ' << r << '\n';
	if(l <= tx && tx <= r){
		cout << mn << '\n';
	}
	else if(tx < l){
		cout << mn + ((l - tx + 1) / 2) << '\n';
	}
	else{
		cout << mn + ((tx - r + 1) / 2) << '\n';
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
// y 偶, x 偶, 左 ; y 偶, x 奇, 右 ;
// y 奇, x 偶, 右 ; y 奇, x 奇, 左 ;