#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, x, y, r;
int a[3100][3100];

void sol(int x, int y, int r){
	for(int row = x - r; row <= x + r; row ++){
		if(row < 1 || row > n) continue;
		int len = r - abs(row - y);
		int l = y - len;
		int r = y + len;
		for(int k = l; k <= r; k ++){
			if(k < 1 || k > n) continue;
			a[row][k] ^= 1;
		}
	}
}

void solve(){
	cin >> n >> m;
	while(m --){
		cin >> x >> y >> r;
		sol(x, y, r);
	}
	int res = 0;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
        	// cout<<a[i][j]<<" \n"[j==n];
            res += a[i][j];
        }
    }
    cout << res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
