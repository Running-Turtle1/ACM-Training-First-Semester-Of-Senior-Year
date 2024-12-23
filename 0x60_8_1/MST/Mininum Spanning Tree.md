# Minimum Spanning Tree

1、以下很多代码可能使用了 `tuple` 记录边的信息，还是推荐用 `struct` 记录，实测 `tuple` 跑起来巨慢，常数比 `kruskal` 大了数倍。

2、kuangbin 专题板子题太多，因此就放了几道有意思的。

## Problem One : Prim 模板题 + 一点点数学

> [4293. 建造空间站 - AcWing题库](https://www.acwing.com/problem/content/4296/) 
> 
> 在一个三位空间中有 n 个球体。
> 
> 每个球体的球心坐标以及半径已知。
> 
> 两个球体之间可能存在接触或重叠，甚至一个完全包含另一个。
> 
> 我们认为两个球体 A 和 B 之间是连通的，如果满足以下条件之一：
> 
> - A 和 B 相互接触或重叠。
> - A 和 B 之间建有连接通道。
> - 存在一个球体 C 满足，A 和 C 连通并且 B 和 C 连通。
> 
> 初始时，不存在任何连接通道。
> 
> 如果要在两个球体之间建立连接通道，则通道成本等于通道长度。
> 
> 通道从一个球体**表面**延伸至另一球体**表面**，为了节约成本，我们当然希望通道长度越短越好。
> 
> 请计算，为了使得任意两个球体之间都能保持连通（直接或间接），所需花费的建立连通通道的总成本最少是多少。
> 
> 你可以认为任意两个通道之间都不会发生相交（也就是说，即使两条通道在空间上相交了，也不认为可以从一个通道走到另一个通道上）。

球的数量少，直接预处理出来每个球之间的距离。

处理方法就是，设 $dis$ 为两球距离之差，$dis=\sqrt {(x_1-x_2)^2+(y_1-y_2)^2+(z_1-z_2)^2}$ 

如果 $dis\leq r1+r2$ ，说明两球相切或相交 ；

否则最近距离为 $dis-r_1-r_2$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

struct Sphere{
    double x, y, z, r;
}sphere[110];

double eg[110][110];
double pow(double x){
    return x * x;
}
void cal(int x, int y){
    auto &[x1, y1, z1, r1] = sphere[x];
    auto &[x2, y2, z2, r2] = sphere[y];
    double dis = sqrt(pow(x1 - x2) + pow(y1 - y2) + pow(z1 - z2));
    if(dis <= r1 + r2){
        eg[x][y] = eg[y][x] = 0;
    }
    else{
        eg[x][y] = eg[y][x] = dis - r1 - r2;
    }
}

double d[110];
int st[110];
double prim(){
    double res = 0;
    for(int i = 1; i <= n; i ++){
        d[i] = 2e9;
        st[i] = 0;
    }
    d[1] = 0;
    for(int i = 1; i <= n; i ++){
        int t = -1;
        for(int j = 1; j <= n; j ++){
            if(!st[j] && (t == -1 || d[j] < d[t])){
                t = j;
            }
        }
        res += d[t];
        st[t] = 1;
        for(int j = 1; j <= n; j ++){
            d[j] = min(d[j], eg[t][j]);
        }
    }
    return res;
}

void solve(){
    for(int i = 1; i <= n; i ++){
        double a, b, c, r;
        cin >> a >> b >> c >> r;
        sphere[i] = {a, b, c, r};
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j < i; j ++){
            cal(i, j);
        }
        eg[i][i] = 0;
    }
    cout << fixed << setprecision(3) << prim() << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    while(cin >> n, n){
        solve();
    }

    return 0;
}
```

## Problem Two : MST 或 DSU 两种做法

> [387. 北极网络 - AcWing题库](https://www.acwing.com/problem/content/389/)
> 
> 国防部（DND）希望通过无线网络连接几个北部前哨站。
> 
> 在建立网络时将使用两种不同的通信技术：每个前哨站都有一个无线电收发器，一些前哨站还有一个通信卫星。
> 
> 任意两个拥有通信卫星的前哨站不论它们的位置如何，都可以通过卫星进行通信。
> 
> 而如果利用无线电进行通信，则需要两个前哨站的距离不能超过 D 方可进行通信。
> 
> 而 D 的大小取决于收发器的功率，收发器的功率越大，D 也就越大，但是需要的成本也就越高。
> 
> 出于采购和维护的考虑，所有的前哨站都采用相同的收发器，也就是说所有前哨站的无线电通信距离 D 都是相同的。
> 
> 你需要确定在保证任意两个前哨站之间都能进行通信（直接或间接）的情况下，D 的最小值是多少。

最直观的想法就是二分 $D$ ，合法就是把所有小于等于 $mid$ 的基站用并查集连起来，最后查连通分量的个数 $sum$ ，而 $s$ 个卫星最多连接起来 $s$ 个连通分量，看看 $sum\leq s$ 是否成立即可。

因为是 MST 专题，所以提供一种 MST 的解法。

将所有哨站加边，边权就是距离大小。

对于 $s=0$ ，显然答案就是 MST 的边权最大值。

对于 $s\neq 0$ ，生成 MST 之后可以利用卫星去掉 $s-1$ 条边，剩下的最大边就是答案。

DSU 解法 :

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

int s, p;
pair<int, int> at[510];

double const eps = 1e-6;

int fa[510];
int find(int x) {
    if (x == fa[x]) return x;
    return fa[x] = find(fa[x]);
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        fa[rootY] = rootX;
    }
}

double dis[510][510];

double computeDistance(int x, int y) {
    auto &[x1, y1] = at[x];
    auto &[x2, y2] = at[y];
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

bool check(double d) {
    for (int i = 1; i <= p; i++) {
        fa[i] = i;
    }
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= p; j++) {
            if (dis[i][j] <= d) {
                unionSets(i, j);
            }
        }
    }
    int components = 0;
    for (int i = 1; i <= p; i++) {
        if (find(i) == i) components++;
    }
    return components <= s;
}

void solve() {
    cin >> s >> p;
    for (int i = 1; i <= p; i++) {
        cin >> at[i].first >> at[i].second;
    }
    for (int i = 1; i <= p; i++) {
        for (int j = 1; j < i; j++) {
            dis[i][j] = dis[j][i] = computeDistance(i, j);
        }
        dis[i][i] = 0;
    }
    double l = 0, r = 30000;
    while (r - l > eps) {
        double mid = (l + r) / 2.0;
        if (check(mid)) r = mid;
        else l = mid;
    }
    cout << fixed << setprecision(2) << l << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    int T;
    cin >> T;
    while (T--) {
        solve();    
    }

    return 0;
}
```

MST 解法 :

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const M = 250010;

int s, p;

struct Edge{
    int u, v;
    double w;
    bool operator < (const Edge & T) const {
        return w < T.w;
    }
}edges[M];
int cnt = 0;

pair<int, int> pos[510];

int fa[510];
int find(int x){
    return (x == fa[x] ? x : fa[x] = find(fa[x]));
}

void solve(){
    cnt = 0;
    cin >> s >> p;
    for(int i = 1; i <= p; i ++){
        fa[i] = i;
        cin >> pos[i].first >> pos[i].second;
    }
    if(s == p){
        cout << "0.00\n";
    }
    for(int i = 1; i <= p; i ++){
        for(int j = 1; j <= p; j ++){
            auto &[x1, y1] = pos[i];
            auto &[x2, y2] = pos[j];
            edges[++ cnt] = {i, j, sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))};
        }
    }
    sort(edges + 1, edges + cnt + 1);
    vector<double> res;
    for(int i = 1; i <= cnt; i ++){
        auto &[u, v, w] = edges[i];
        int pu = find(u), pv = find(v);
        if(pu != pv){
            fa[pu] = pv;
            res.push_back(w);
        }
    }
    // for(int i = 0; i < res.size(); i ++)
    cout << fixed << setprecision(2) << res[res.size() - s] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 

    int T;
    cin >> T;
    while(T --){
        solve();
    }    
    return 0;
}
```

## Problem Three : 思维 + bfs + MST

> [4335. 博格迷宫 - AcWing题库](https://www.acwing.com/problem/content/4338/)

这题很有意思，但是出现在 MST 专题很没有意思。

给你一个很多位置，从这些位置里面给定起始位置，要求经过所有位置且走过的路程之和最小。经过一个点的时候可以分裂成任意队伍。

相当于就是 MST 了，首先证明 MST 是下界，然后证明能做到 MST 的走法就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 60;

int n, m, cnt = 0;

char g[N][N];

struct Edge{
    int u, v, w;
    bool operator < (const Edge & T) const {
        return w < T.w;
    }
}edges[100010];

vector<pair<int, int> > points;


int cal(int x, int y){
    return (x - 1) * m + y;
}

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int d[N][N], p[2610];
void bfs(int id){
    auto &[sx, sy] = points[id];
    queue<pair<int, int> > q;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            d[i][j] = -1;
        }
    }
    d[sx][sy] = 0;
    q.push({sx, sy});
    while(q.size()){
        auto &[x, y] = q.front(); q.pop();
        for(int i = 0; i < 4; i ++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] != '#' && d[nx][ny] == -1){
                d[nx][ny] = d[x][y] + 1;
                if(g[nx][ny] == 'S' || g[nx][ny] == 'A'){
                    edges[++ cnt] = {cal(nx, ny), cal(sx, sy), d[nx][ny]};
                }
                q.push({nx, ny});
            }
        }
    }
}

string s;
int find(int x) {return x == p[x] ? x : p[x] = find(p[x]); }

void solve(){
    cin >> m >> n;
    cnt = 0;
    points.clear();
    getline(cin, s);

    for(int i = 1; i <= n; i ++){
        getline(cin, s);
        s += string(m + 1, ' ');
        for(int j = 0; j < m; j ++){
            g[i][j + 1] = s[j];
            if(s[j] == 'S' || s[j] == 'A'){
                points.push_back({i, j + 1});
            }
        }
    }
    for(int i = 0; i < points.size(); i ++){
        bfs(i);
    }
    sort(edges + 1, edges + cnt + 1);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            int id = cal(i, j);
            p[id] = id;
        }
    }
    int res = 0;
    for(int i = 1; i <= cnt; i ++){
        auto &[u, v, w] = edges[i];
        if(find(u) != find(v)){
            p[find(u)] = find(v);
            res += w;
        }
    }
    cout << res << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 

    int T;
    cin >> T;
    while(T --){
        solve();    
    }

    return 0;
}
```

## Problem Four : 带点权的最小生成树

> 水资源分配优化
> 村里面一共有 n 栋房子。我们希望通过建造水井和铺设管道来为所有房子供水。
> 对于每个房子 i，我们有两种可选的供水方案：一种是直接在房子内建造水井
> 成本为 wells[i - 1] （注意 -1 ，因为 索引从0开始 ）
> 另一种是从另一口井铺设管道引水，数组 pipes 给出了在房子间铺设管道的成本，
> 其中每个 pipes[j] = [house1j, house2j, costj] 
> 代表用管道将 house1j 和 house2j连接在一起的成本。连接是双向的。
> 请返回 为所有房子都供水的最低总成本
> 测试链接 : [. - 力扣（LeetCode）](https://leetcode.cn/problems/optimize-water-distribution-in-a-village/)

很有意思的一道题，每个点有水源，开采需要费用。

将一个点的水源引向另一个点，也需要费用。

可以做转换 ：设立水源，将水源与所有点连边，对新图求 MST 即可。

## Problem Five : 检查边长度限制的路径是否存在

> 给你一个 `n` 个点组成的无向图边集 `edgeList` ，其中 `edgeList[i] = [ui, vi, disi]` 表示点 `ui` 和点 `vi` 之间有一条长度为 `disi` 的边。请注意，两个点之间可能有 **超过一条边** 。
> 
> 给你一个查询数组`queries` ，其中 `queries[j] = [pj, qj, limitj]` ，你的任务是对于每个查询 `queries[j]` ，判断是否存在从 `pj` 到 `qj` 的路径，且这条路径上的每一条边都 **严格小于** `limitj` 。
> 
> 请你返回一个 **布尔数组** `answer` ，其中 `answer.length == queries.length` ，当 `queries[j]` 的查询结果为 `true` 时， `answer` 第 `j` 个值为 `true` ，否则为 `false` 。

这道题放过来，是因为最开始，我的思路是，对图做 Kruskal 做出 MST，在 ST 表维护路径最大值，检查是否超过 limit。

但这样太过麻烦，因为这题的询问是离线的，我们对询问按照 `limit` 排序，每次加入 $<limit$ 的边，用并查集维护连通性就可以了，快哉快哉。

```cpp
class Solution {
public:
    int find(int x, vector<int> &p){
        return x == p[x] ? x : p[x] = find(p[x], p);
    }
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        int q = queries.size();
        int m = edgeList.size();
        vector<int> p(n, 0);
        vector<bool> ans(q);
        for(int i = 0; i < q; i ++){
            queries[i].push_back(i);
        }
        for(int i = 0; i < n; i ++){
            p[i] = i;
        }
        sort(queries.begin(), queries.end(), [&] (vector<int> &a, vector<int> &b){
            return a[2] < b[2];
        });
        sort(edgeList.begin(), edgeList.end(), [&] (vector<int> &a, vector<int> &b){
            return a[2] < b[2];
        });
        int now = 0;
        for(int i = 0; i < q; i ++){
            int asku = queries[i][0], askv = queries[i][1], limit = queries[i][2], id = queries[i][3];
            while(now < m && edgeList[now][2] < limit){
                int u = edgeList[now][0], v = edgeList[now][1];
                int pu = find(u, p), pv = find(v, p);
                if(pu != pv){
                    p[pu] = pv;
                }
                now ++;
            }
            ans[id] = find(asku, p) == find(askv, p);
        }
        return ans;
    }
};
```
