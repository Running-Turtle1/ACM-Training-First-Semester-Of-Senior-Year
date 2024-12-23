#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N = 1e6 + 10;
int n, m;
int f[N], g[N], q[N<<1];
void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        int v, w, s;
        cin >> v >> w; 
        s = w / 2;
        for(int j = 0; j <= m; j ++){
            g[j] = f[j];
        }
        for(int j = 0; j < v; j ++){ // 划分为 V 个类
            int h = 0, t = -1; // 对每个类用单调队列优化 
            for(int k = j; k <= m; k += v){
                // [k - s * v, k - v] 窗口内取 mx 来更新
                while(h <= t && q[h] < k - s * v) h ++; 
                int tmp = (k - q[h]) / v;
                if(tmp > w / 2) tmp = w / 2; 
                if(h <= t) f[k] = max(g[k], g[q[h]] + tmp * w - tmp * tmp);
                // 当前值比队尾更有价值, 队尾出队 
                int v1 = g[k] + (x - k) / v * w - pow((x - k) / v, 2);
                while(h <= t && g[k] + (x - k) / v * w - ((x - k) / v * ((x - k) / v)) >= g[q[t]] +  tmp * w - tmp * tmp) t --;
                q[++ t] = k;            
            }
        } 
        cout << "Round: " << i << '\n';
        for(int j = 0; j <= m; j ++){
            cout << f[j] << " \n"[j == m];
        }
    } 
    cout << f[m] << '\n';
}

// f[2] = 4
// (6 - 2) / 2 = 2
// 2 * 7 - 2 * 2 = 10

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}

