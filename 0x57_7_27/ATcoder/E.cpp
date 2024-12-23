#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 82;
int const M = 1e4 + 10;

int n, x, y;
int f[N][N][M]; // 考虑到第 i 个物品, 已经吃了 j 个, 甜度不超过 k 的最小咸度
int a[N], b[N];

void solve(){
	cin >> n >> x >> y;
	for(int i = 1; i <= n; i ++){
		cin >> a[i] >> b[i];
    }
    memset(f, 0x3f, sizeof f);
    // i = 0, j = 0
    for(int k = 0; k <= x; k ++){
    	f[0][0][k] = 0;
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	for(int j = 0; j <= i; j ++){
    		for(int k = 0; k <= x; k ++){
    			// 不吃
    			f[i][j][k] = min(f[i - 1][j][k], f[i][j][k]);
    			// 吃 
    			if(j >= 1 && k >= a[i]){
    				f[i][j][k] = min(f[i - 1][j - 1][k - a[i]] + b[i], f[i][j][k]);
    			}
    			if(f[i][j][k] <= y){
    				// cout << i << ' ' << j << ' ' << k << '\n';
    				res = max(res, j);
    			}
    		}
    	}
    }
    cout << min(res + 1, n) << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
