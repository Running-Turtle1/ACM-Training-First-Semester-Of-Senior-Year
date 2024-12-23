#include<bits/stdc++.h>
using namespace std;
#define int long long
 
int const N = 510;
int const M = 500 * 500;

int n, k;
int f[2][N * N * 2], a[N], b[N];
 
void solve(){
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> a[i] >> b[i];
        b[i] -= k;
    }
    memset(f, -0x3f, sizeof f);
    f[0][0 + M] = 0;
    for(int i = 1; i <= n; i ++){
    	int now = (i & 1), las = now ^ 1;
    	memset(f[now], -0x3f, sizeof f[now]);
    	for(int j = -M; j <= 0; j ++){
    		if(j - b[i] >= -M){
    			f[now][j + M] = max(f[now][j + M], f[las][j - b[i] + M] + a[i]);
    		}
    		f[now][j + M] = max(f[now][j + M], f[las][j + M]);
    	}
    }
    int res = 0;
    for(int j = -M; j <= 0; j ++){
        res = max(res, f[n & 1][j + M]);
    }
    cout << res << '\n';
}
 
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}