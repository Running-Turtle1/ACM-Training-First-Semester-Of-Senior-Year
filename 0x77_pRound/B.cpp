#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 510;

int n, k;
unordered_map<int, int> f, g;
int a[N], b[N];

void solve(){
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> a[i] >> b[i];
        b[i] -= k;
    }
    f[0] = 0;
    for(int i = 1; i <= n; i ++){
        g.clear();
        for(int j = -500 * 500; j <= 500 * 500; j ++){
            int t;
            if(f.count(j - b[i])){
                g[j] = max(g[j], f[j - b[i]] + a[i]);
            }
            if(f.count(j)){
                g[j] = max(g[j], f[j]);
            }
        }
        f = g;
    }
    int res = 0;
    for(int j = -500 * 500; j <= 0; j ++){
        res = max(res, f[j]);
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
