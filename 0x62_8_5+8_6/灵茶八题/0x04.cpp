#include<bits/stdc++.h>
using namespace std;
// #define int long long

void solve(){
    int n;
    cin >> n;
    vector<int> v(n + 5);
    for(int i = 1; i <= n; i ++){
        cin >> v[i];
    }

    int s = (1LL << 16) - 1;
    vector<vector<int> > dp(2, vector<int> (s + 1, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= n; i ++){
        int now = (i & 1);
        for(int j = 0; j <= s; j ++){
            dp[now][j] = 0;
        }
        for(int j = 0; j <= s; j ++){
            dp[now][j] = (dp[now][j] + dp[now ^ 1][j]) % 2;
            if(j >= v[i]){
                dp[now][j] = (dp[now][j] + dp[now ^ 1][j - v[i]]) % 2;
            }
        }
    }   
    // cout << dp[1][0] << '\n';
    // cout << dp[1][1] << '\n';
    int res = 0;
    for(int i = 1; i <= s; i ++){
        if(dp[n & 1][i]){
            // cout << i << '\n';
            res = res ^ i;
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
