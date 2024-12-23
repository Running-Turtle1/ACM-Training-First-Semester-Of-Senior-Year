# [217. 绿豆蛙的归宿 - AcWing题库](https://www.acwing.com/problem/content/219/)

有向无环图，DAG，记忆化搜索写一下期望 DP 式子即可

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int const N = 2e5 + 10;
vector<pair<int, int> > e[N];
double f[N];

double dfs(int u){
    if(fabs(f[u] + 1.0) > 1e-6) return f[u];
    f[u] = 0;
    int s = e[u].size();
    for(auto [v, w] : e[u]){
        f[u] += 1.0 / s * (w + dfs(v));
    }
    return f[u];
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        int a, b, c;
        cin >> a >> b >> c;
        e[a].push_back({b, c});
        f[i] = -1.0;
    }
    dfs(1);
    cout << fixed << setprecision(2) << f[1] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```

# [218. 扑克牌 - AcWing题库](https://www.acwing.com/problem/content/220/)

题面出错了，害我多花了 114.514 分钟才意识到题目出错了，修改一下题面描述就通过了。

状态定义也比较巧妙，定义别的状态虽然对，但是会多花 9.88244353 分钟来表示答案。

f[a][b][c][d][x][y] 表示到终点的期望距离，写一下 DP 转移方程即可。

特别注意，大小王不能随机化，要取 min 来表示

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int const N = 2e5 + 10;
vector<pair<int, int> > e[N];
double f[N];

double dfs(int u){
    if(fabs(f[u] + 1.0) > 1e-6) return f[u];
    f[u] = 0;
    int s = e[u].size();
    for(auto [v, w] : e[u]){
        f[u] += 1.0 / s * (w + dfs(v));
    }
    return f[u];
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        int a, b, c;
        cin >> a >> b >> c;
        e[a].push_back({b, c});
        f[i] = -1.0;
    }
    dfs(1);
    cout << fixed << setprecision(2) << f[1] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```
