#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k, q;

void solve(){
    cin >> n >> k >> q; 
    vector<vector<int> > a(n + 1, vector<int> (k + 1, 0));
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= k; j ++){
            cin >> a[i][j];
        }
    }
    for(int j = 1; j <= k; j ++){
        for(int i = 2; i <= n; i ++){
            a[i][j] |= a[i - 1][j];
        }
    }
    // for(int i = 1; i <= n; i ++){
    //     for(int j = 1; j <= k; j ++){
    //         cout << a[i][j] << " \n"[j == k];     
    //     }
    // }
     
    while(q --){
        int m, c, v;
        char ch;
        cin >> m;
        int l = 1, r = n;
        bool fg = true;
        for(int i = 1; i <= m; i ++){
            cin >> c >> ch >> v;
            if(!fg) continue ;
            int vl = a[l][c], vr = a[r][c];
            if(ch == '<'){
                if(v <= vl){
                    fg = false;
                }
                else if(v <= vr){
                    int lf = l, ri = r + 1;
                    while(lf < ri){
                        int mid = lf + ri >> 1;
                        if(a[mid][c] >= v) ri = mid;
                        else lf = mid + 1;
                    }   
                    r = ri - 1;
                }
            }
            else{
                if(v >= vr){
                    fg = false;
                }
                else if(v >= vl){
                    int lf = l, ri = r;
                    while(lf < ri){
                        int mid = lf + ri >> 1;
                        if(a[mid][c] > v) ri = mid;
                        else lf = mid + 1;
                    }
                    // cout << "lf: " << lf << '\n';
                    l = lf;
                }
            }
        }
        if(!fg) cout << "-1\n";
        else cout << l << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
