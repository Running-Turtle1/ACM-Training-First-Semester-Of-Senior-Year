#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1100;
int n, m, p[N], s[N], c[N];

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        cin >> p[i] >> s[i];
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            c[j] = (j == i ? p[j] / 2 + s[j] : p[j] + s[j]);
        }
        sort(c + 1, c + n + 1);
        c[n + 1] = 2e9;
        int now = m;
        for(int j = 1; j <= n + 1; j ++){
            if(now < c[j]){
                res = max(res, j - 1);
                break;
            }
            now -= c[j];
        }
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}