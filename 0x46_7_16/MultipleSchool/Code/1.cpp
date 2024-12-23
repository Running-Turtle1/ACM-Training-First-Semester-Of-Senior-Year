#include<bits/stdc++.h>
using namespace std;

int n;
int f[2][5100];
int t[5100], d[5100], p[5100];
// struct node{
//     int t, d, p;
// }in[5100];
void solve(){
    cin >> n;
    memset(f, 0, sizeof f);
    for(int i = 1; i <= n; i ++){
        int x, y, z;
        cin>>t[i]>>d[i]>>p[i]; 
    } 
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	int now = i & 1;
    	now ^= 1;
    	memset(f[now], 0, sizeof f[now]);
        for(int j = 1; j <= 5000; j ++){
            f[now][j] = f[now ^ 1][j];
            if(j < d[i] && j - t[i] >= 0){
                f[now][j] = max(f[now][j], f[now ^ 1][j - t[i]] + p[i]);
            }
            else if(j >= d[i] && d[i] - t[i] >= 0){
                f[now][j] = max(f[now][j], f[now ^ 1][d[i] - t[i]] + p[i]);
            }
            res = max(res, f[now][j]);
        }
    }
    // for(int i = 1; i <= 5000; i ++){
    //     for(int j = 1; j <= n; j ++){
    //         f[i][j] = f[i][j - 1];
    //         if(i < d[j] && i - t[j] >= 0){
    //             f[i][j] = max(f[i][j], f[i - t[j]][j - 1] + p[j]);
    //         }
    //         else if(i >= d[j] && d[j] - t[j] >= 0){
    //             f[i][j] = max(f[i][j], f[d[j] - t[j]][j - 1] + p[j]);
    //         }
    //         // f[i][j] = max(f[i][j], f[i - 1][j]);
    //         res = max(res, f[i][j]);
    //     }
    // }
    // for(int i = 1; i <= 9; i ++){
    //     for(int j = 1; j <= n; j ++){
    //         cout << i << ' ' << j << ' ' << f[i][j] << '\n';
    //     }
    // }
    cout << res << '\n';
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while(T --){
        solve();
    }
    return 0;
}
