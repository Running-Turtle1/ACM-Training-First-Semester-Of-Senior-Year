#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int p[35100], sz[35100], ans[35100];

int find(int x){
    if(p[x] == x) return x;
    int t = find(p[x]);
    ans[x] += ans[p[x]];
    return p[x] = t;
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        p[i] = i;
        sz[i] = 1;
        ans[i] = 0;
    }
    for(int i = 1; i <= m; i ++){
        int x, y;
        string opt;
        cin >> opt >> x;
        if(opt == "T"){
            cin >> y;
            int fx = find(x), fy = find(y);
            if(fx != fy){
                p[fx] = fy;
                ans[fx] = sz[fy];
                sz[fy] += sz[fx];
            }
        }
        else{
            find(x);
            cout << ans[x] << '\n';
        }
    }

}

signed main(){
    freopen("queue.in", "r", stdin);
    freopen("queue.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}