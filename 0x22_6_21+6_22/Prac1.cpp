#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;
int notDelRes = 0;
int n, a[N], tr[N], l[N];
void add(int p, int v){
    for(int i = p; i < N; i += i & -i){
        tr[i] += v;
    }
}
int ask(int p) {
    int res = 0;
    for(int i = p; i; i -= i & -i){
        res += tr[i];
    }
    return res;
}
int ask(int l, int r){ return ask(r) - ask(l - 1); }
// set<int> st;
// int quety(int x){ // 查询 a[i] < x 的数量

// }
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    for(int i = 1; i <= n; i ++){
        if(a[i] != n) l[i] = ask(a[i] + 1, n);
        add(a[i], 1);
    }
    // for(int i = 1; i <= n; i ++){
    //     cout << l[i] << " \n"[i == n];
    // }
    int mx = -1, res = -1;
    int s = 0;
    memset(tr, 0, sizeof tr);
    for(int i = 1; i <= n; i ++){
        // s += l[i] == 1;
        // if(l[i] == 1){
        //     st.insert(a[i]);
        // }
        if(l[i] == 1){
            add(a[i], 1);
        }
    }
    for(int i = 1; i <= n; i ++){
        int t = ask(1, a[i] - 1) - (l[i] == 0);
        // cout << i << ' ' << ask(1, a[i] - 1) << ' ' << t << '\n';
        if(t > mx || (t == mx && a[i] < res)){
            mx = t;
            res = a[i];
        }
        if(l[i] == 1) add(a[i], -1);
    }
    cout << res << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}

