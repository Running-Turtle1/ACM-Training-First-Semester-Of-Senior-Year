#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3e6 + 10;

int n, d;
int x[N], y[N];
int sx[N], sy[N];
int ans[N];

int askx(int l, int r){
	return sx[r] - sx[l - 1];
}
int asky(int l, int r){
	return sy[r] - sy[l - 1];
}
void add(int l, int r){
	ans[l] ++;
	ans[r + 1] -- ;
}

void solve(){
	cin >> n >> d; 
	for(int i = 1; i <= n; i ++){
		cin >> x[i] >> y[i];
    }
    sort(x + 1, x + n + 1);
    sort(y + 1, y + n + 1);
    for(int i = 1; i <= n; i ++){
    	sx[i] = sx[i - 1] + x[i];
    	sy[i] = sy[i - 1] + y[i];
    }
    // for(int i = 1; i <= n; i ++){
    // 	cout << sx[i] << " \n"[i == n];
    // }
    // for(int i = 1; i <= n; i ++){
    // 	cout << sy[i] << " \n"[i == n];
    // }
    int res = 0;
    for(int py = -2e6; py <= 2e6; py ++){
    	int p = lower_bound(y + 1, y + n + 1, py) - y;
    	int td = (p - 1) * py - asky(1, p - 1) + asky(p, n) - (n - p + 1) * py;
    	// if(py == 0){
    		// cout << "td: " << td << '\n';
    	// }
    	// if(td < 0 || td > 2e6){
    	// 	cout << "Re\n";
    	// 	return ;
    	// }
    	if(td <= 1e6) add(td, 1e6);
    }
    for(int i = 1; i <= 1e6; i ++){
    	ans[i] += ans[i - 1];
    }
    // return ;
    // cout << ans[0] << '\n';
    for(int px = -2e6; px <= 2e6; px ++){
    	int p = lower_bound(x + 1, x + n + 1, px) - x;
    	int td = (p - 1) * px - askx(1, p - 1) + askx(p, n) - (n - p + 1) * px;
    	if(td > d) continue ;
    	// cout << "px: " << td << '\n';
    	td = d - td;
    	// cout << "ntd: " << td << '\n';
    	res += ans[td];
    }		
    cout << res << '\n'; 
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
