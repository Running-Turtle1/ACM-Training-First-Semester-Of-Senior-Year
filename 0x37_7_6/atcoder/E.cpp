#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, a, b, c, res = 0;

void solve(){
    cin >> n;
    int mx = 0;
    for(int i = 1; i < n; i ++){
        cin >> a >> b >> c;
        mx = max(mx, c);
        res += 2 * c;
    }
    res -= mx;
    cout << res << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
