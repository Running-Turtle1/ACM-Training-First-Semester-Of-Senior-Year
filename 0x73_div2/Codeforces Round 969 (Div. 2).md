## A

赛时没想到比较好的做法，区间 DP 预处理做的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n, m, q;

int a[N], b[N], c[N];
int f[1100][1100];

void solve(){
    int l, r;
    cin >> l >> r;
    cout << f[l][r] << '\n';
}


int g[1100][1100];
int ask(int l, int r){
    if(f[l][r] != -1){
        return f[l][r];
    }
    if(r - l + 1 < 3) return f[l][r] = 0;
    if(r - l + 1 == 3){
        if(g[l][l + 1] == 1 && g[l][l + 2] == 1 && g[l + 1][l + 2] == 1) return f[l][r] = 1;
        else return f[l][r] = 0;
    }
    int mx = 0;
    for(int k = l; k < r; k ++){
        mx = max(mx, ask(l, k) + ask(k + 1, r));
    }
    return f[l][r] = mx;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    memset(f, -1, sizeof f);

    for(int i = 1; i <= 1000; i ++){
        for(int j = 1; j <= 1000; j ++){
            g[i][j] = __gcd(i, j);
        }
    }

    for(int l = 1; l <= 1000; l ++){
        for(int r = l; r <= 1000; r ++){
            ask(l, r); 
            // for(int k = l; k < r; k ++){
                // int t = ask(l, k) + ask(k + 1, r);
                // if(ask(l, k) != -1 && ask(k + 1, r) != -1){
                //     f[l][r] = max(f[l][r], f[l][k] + f[k + 1][r]);
                // }
            // }
        }
    }

    int T = 1;
    cin >> T;
    while (T --){
        solve();
    }

    return 0;
}
```

实际上，选出的三个数里面至少有两个奇数，那么答案最多有奇数个数除 2 下取整。

选择相邻的奇数和他们之间的偶数，即可满足条件。

因为相邻的数互质且相邻奇数互质，关于第二条 :

$\gcd(2k+1,2k+3)=gcd(2k+1,2)=1$ 

```cpp
void solve(){
    int l, r;
    cin >> l >> r;
    int s = 0;
    for(int i = l; i <= r; i ++){
        s += (i & 1);
    }
    cout << s / 2

    return 0;
}
```

## B

这题赛时也没想到比较好的做法。

于是用 FHQ TREAP 暴力维护了一下。

split 的时候根据权值 split。

查询最大值是否存在，二分这个最大值 $mx$ 。

check(x) 合法 : 按照 x split treap 的时候右树不为空。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e6 + 10;
struct Node{
    int l, r;
    int val;
    int rnd;
    int size; // 用于排名分裂
    int add; // 懒标记
}tr[N];
int root = 0, idx = 0;

int newNode(int v){
    ++ idx;
    tr[idx].val = v;
    tr[idx].rnd = rand();
    tr[idx].size = 1;
    tr[idx].add = 0;
    return idx;
}

void pushup(int p){
    tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;
}

void pushdown(int p){
    if(!tr[p].add) return ;
    tr[p].val += tr[p].add;
    tr[tr[p].l].add += tr[p].add;
    tr[tr[p].r].add += tr[p].add; 
    tr[p].add = 0;
}

void split(int p, int v, int &x, int &y){
    if(!p) {x = y = 0; return;}
    pushdown(p);
    if(tr[p].val <= v){
        x = p;
        split(tr[x].r, v, tr[x].r, y);
        pushup(x);
    }
    else{
        y = p;
        split(tr[y].l, v, x, tr[y].l);
        pushup(y);
    }
}
int merge(int x, int y){
    if(!x || !y) return x + y;
    if(tr[x].rnd < tr[y].rnd){
        pushdown(x);
        tr[x].r = merge(tr[x].r, y);
        pushup(x);
        return x;
    }
    else{
        pushdown(y);
        tr[y].l = merge(x, tr[y].l);
        pushup(y);
        return y;
    }
}

// mid 是否小于等于最大值
// 特征 : 
int check(int mid){
    int x, y;
    split(root, mid - 1, x, y);
    int ans = y != 0;//tr[y].size != 0;
    root = merge(x, y);
    return ans;
}
int bs(){
    int l = -1e6, r = 2e9;
    while(l < r){
        int mid = l + r + 1 >> 1;
        if(check(mid)) l = mid;
        else r = mid - 1;
    }
    return l;
}
void insert(int v){
    int x, y, z;
    split(root, v, x, y);
    z = newNode(v);
    root = merge(merge(x, z), y);
}
void solve(){
    srand(time(NULL));
    // 初始化 treap
    for(int i = 1; i <= idx; i ++){
        tr[i].l = tr[i].r = 0;
        tr[i].val = tr[i].rnd = tr[i].size = tr[i].add = 0;
    }
    root = idx = 0;
    int n, m, l, r, x, y, z;
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        int x;
        cin >> x;
        insert(x);
    }

    while(m --){
        char opt;
        cin >> opt >> l >> r;
        split(root, r, x, y); // [1, r] [r + 1, n]
        split(x, l - 1, x, z); // [1, l - 1] [l, r]
        if(opt == '+') tr[z].add ++;
        else tr[z].add --;
        root = merge(merge(x, z), y);  

        cout << bs() << ' ';

    }
    cout << '\n';

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

考虑题解做法，对于 $<mx$ 的数，不会通过 `+` 操作 $>mx$ 。

对于 $mx$ ，不会通过 `-` 操作变成非最大值。

所以只用维护 mx 即可。

## C

发现对于每个 $c_i$ ，变化为 $c_i+ax+by$ 。

因为要维护 $mx-mn$ 。

所以想对 $c_i-a$ ，就让其余所有数 +a。

如此一来 $x$ 和 $y$ 就相当于可以取负数了。

设 $g=\gcd(a,b)$ 

对所有数 $mod \;  g$ 。

假设得到了 $c_1，c_2，c_3，c_4，c_5$ 。

发现还可让 $c_1 \sim c_i$ 全部加上 $g$ ，让答案更优。

枚举一下哪一段加上 $g$ 。

```cpp
int n, a, b, g;
int v[N];

void solve(){
    cin >> n >> a >> b;
    g = __gcd(a, b);
    for(int i = 1; i <= n; i ++){
        cin >> v[i];
        v[i] %= g;
    }
    sort(v + 1, v + n + 1);
    int res = v[n] - v[1];
    for(int i = 1; i < n; i ++){ // [1, i] 翻转
        res = min(res, v[i] + g - v[i + 1]);
    }
    cout << res << '\n';
}
```

## D

注意题目，一个叶子结点可以贡献一个贡献，当且仅当 $10$ 的数量 $\neq$ $01$ 的数量。

赛时读错题了，浪费了很久。

发现合并相邻的 $01$ 之后，只有以下四种串 :

$01$ : 得分 

$010$ : 不得分 

$10$ : 得分 

$101$ : 不得分

发现开头结尾字符不同的可以得分。

设 $x$ ，$y$ ，$z$ 表示叶子结点中 $0$ ，$1$ ，$2$ 的数量。

对于 $1$ 节点。

如果 $1$ 节点已经确定，贪心对叶子结点赋相反值。

如果 $1$ 节点不确定，观察样例，发现 $x=y$ 时，且没有缓冲节点（非叶子非根的 ？），那么先手会吃亏。但是最多是少拿一个。

因此 $x=y$ 观察缓冲节点奇偶性。否则直接贪心拿。

```cpp
int const N = 1e6 + 10;

int n;
int v[N], d[N];

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        d[i] = 0;
    }
    for(int i = 1; i < n; i ++){
        int u, v;
        cin >> u >> v;
        d[u] ++; 
        d[v] ++;
    }
    string s;
    cin >> s;
    for(int i = 0; i < s.size(); i ++){
        v[i + 1] = (s[i] == '0' ? 0 : (s[i] == '1' ? 1 : 2));
    }
    int x, y, z;
    x = y = z = 0;

    int t = 0;

    for(int i = 1; i <= n; i ++){
        if(d[i] == 1 && i != 1){ 
            if(v[i] == 0) x ++;
            if(v[i] == 1) y ++;
            if(v[i] == 2) z ++;
        }
        else if(v[i] == 2 && i != 1){
            t ++;
        }
    }
    // cout << x << ' ' << y << ' ' << z << ' ' << t << '\n';
    if(v[1] == 0){ // 抢 1
        cout << y + (z + 1) / 2 << '\n';
    }
    else if(v[1] == 1){ // 抢 0
        cout << x + (z + 1) / 2 << '\n';
    }
    else if(x == y) { // 可能需要中间缓冲
        if(t & 1){
            cout << x + (z + 1) / 2 << '\n';
        }
        else{
            cout << x + z / 2 << '\n';
        }
    }
    else if(x > y){
        cout << x + z / 2 << '\n';
    }
    else{
        cout << y + z / 2 << '\n';
    }
}
```

## E

读错题了，写了个重链剖分解决每个 `dist` 不独立的，对于树的标号也没有要求，可以用下面的代码思路 :

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const N = 1e3 + 10;

vector<int> e[N];

int sz[N], son[N], dep[N], fa[N];
int w[N], nw[N], id[N], top[N], tim = 0;

void dfs1(int u, int father){
    sz[u] = 1, dep[u] = dep[father] + 1, fa[u] = father;
    for(int v : e[u]){
        if(v == father) continue ;
        dfs1(v, u);
        sz[u] += sz[v];
        if(sz[v] > sz[son[u]]) son[u] = v;
    }
}
// id : 存 u 剖分之后的编号
// nw : 新编号在树中对应的权值
void dfs2(int u, int tp){
    top[u] = tp, id[u] = ++ tim, nw[tim] = w[u];
    if(!son[u]) return ;
    dfs2(son[u], tp);
    for(int v : e[u]){
        if(v == fa[u] || v == son[u]) continue ;
        dfs2(v, v);
    }
}

struct tree{
    int l, r;
    int sum, add;
}tr[N * 4];

void pushup(int u){
    tr[u].sum = tr[lc].sum + tr[rc].sum;
}

void pushdown(int u){
    if(tr[u].add){
        tr[lc].sum += tr[u].add * (tr[lc].r - tr[lc].l + 1);
        tr[rc].sum += tr[u].add * (tr[rc].r - tr[rc].l + 1);
        tr[lc].add += tr[u].add;
        tr[rc].add += tr[u].add;
        tr[u].add = 0;
    }
}

void build(int u, int l, int r){
    tr[u] = {l, r, nw[l], 0};
    if(l == r) return ;
    int mid = l + r >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    pushup(u);
}

void update(int u, int l, int r, int k){
    if(l <= tr[u].l && r >= tr[u].r){
        tr[u].sum += k * (tr[u].r - tr[u].l + 1);
        tr[u].add += k;
        return ;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    if(l <= mid) update(lc, l, r, k);
    if(r > mid) update(rc, l, r, k);
    pushup(u);
}

// 将树从 u 到 v 节点最短路径上的所有节点的值加上 k
void update_path(int u, int v, int k){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        update(1, id[top[u]], id[u], k);
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    update(1, id[v], id[u], k);
}

// 以 u 为根的子树的所有节点的值加 k
// 以 u 为根的子树的 dfs 序是连续的
void update_tree(int u, int k){
    update(1, id[u], id[u] + sz[u] - 1, k);
}

int ask(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].sum;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    int res = 0;
    if(l <= mid) res += ask(lc, l, r);
    if(r > mid) res += ask(rc, l, r);
    pushup(u);
    return res;
}

// 查询树从 u 到 v 节点最短路径上的所有节点的值之和
int ask_path(int u, int v){
    int res = 0;
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        res += ask(1, id[top[u]], id[u]);
        u = fa[top[u]];
    }
    if(dep[u] < dep[v]) swap(u, v);
    res += ask(1, id[v], id[u]);
    return res;
}

// 查询以 u 为根的子树的节点值之和
int ask_tree(int u){
    return ask(1, id[u], id[u] + sz[u] - 1);
}

int lca(int u, int v){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] < dep[v] ? u : v;
}
int n, sw, r = 1;
int p[N];
void solve(){
    cin >> n >> sw;
    for(int i = 1; i <= n; i ++){
        e[i].clear();
    }
    for(int i = 2; i <= n; i ++){
        cin >> p[i];
        e[i].push_back(p[i]);
        e[p[i]].push_back(i);
    }
    // 从根节点 dfs
    dfs1(r, 0);
    dfs2(r, r);
    build(1, 1, n); // 用链建线段树

    vector<int> showtimes(n + 1, 0); // 出现次数 
    vector<int> val(n + 1, 0); // 权值
    vector<pair<int, int> > edge(n + 1);
    for(int i = 1; i < n; i ++){
        int u, v;
        cin >> u >> val[i];
        v = p[u];
        edge[i] = {u, v};
    }

    // 剖分对应边
    for(int i = 1; i <= n; i ++){
        int j = (i == n ? 1 : i + 1);
        update_path(i, j, 1);
        int LCA = lca(i, j);
        update_path(LCA, LCA, -1);
    }

    for(int i = 1; i < n; i ++){
        auto [u, v] = edge[i];
        int LCA = lca(u, v);
        showtimes[i] = ask_path(u,v) - ask_path(LCA,LCA);
        cout << i << ' ' << val[i] << ' ' << showtimes[i] << '\n';
    }

    vector<int> res(n + 1, 0);
    vector<int> sval(n + 1, 0);
    // 预处理已知答案前缀和
    for(int i = 1; i <= n; i ++){
        res[i] = res[i - 1] + showtimes[i] * val[i]; 
        sval[i] = sval[i - 1] + val[i];
        cout << "res: " << i << ' ' << res[i] << '\n';
    }
    int mxs = 0, ss = 0;
    for(int i = n - 1; i >= 2; i --){
        mxs = max(mxs, showtimes[i]);
        ss += showtimes[i];
        int allnums = n - i;
        res[i] = res[i - 1] +  (ss - mxs) + mxs * (sw - allnums + 1 - sval[i - 1]);
        cout << "mxs: " <<mxs<<'\n';
        cout << "ss: " << ss << '\n';
        cout << "sval: " <<sval[i - 1] << '\n';
    }
    for(int i = 2; i <= n; i ++){
        cout << res[i] << " \n"[i == n];vector<int> res(n + 1, 0);
    }
    // int i = 0;
    // auto add=[&](int l,int r, int v){
    //     res[l]+=v;
    //     res[r+1]-=v;
    // };
    // for(auto &[u, v] : edge){
    //     i ++;
    //     int LCA = lca(u, v);
    //     ss[i] = ask_path(u,v) - ask_path(LCA,LCA);
    //     tms[i] = ss[i] + tms[i - 1];
    //     cout<<ss[i]<< ' '<<t[i]<<'\n';
    //     // res[i] += ss[i] * t[i];
    //     add(i, n, ss[i] * t[i]);
    //     // res[n] += ss[i] * t[i];
    // }
    // for(int i = 1; i <= edge.size()+1; i ++){
    //     res[i]+=res[i-1];
    //     cout<<"i: "<<i<<' '<<res[i]<<'\n';
    // }
    // cout<<res[n]<<'\n';
    // int mx = -2e9;
    // int st = 0;
    // for(int i = edge.size() - 1; i > 0; i --){
    //     i ++;
    //     auto &[u, v] = edge[i];
    //     mx = max(mx, t[i + 1]);
    //     int tmp = sw - tms[i] - ((edge.size() - 1) - i);
    //     cout<<"St:\n";
    //     cout << tmp << '\n';
    //     cout <<mx <<'\n';
    //     cout<<st<<'\n';
    //     res[i] += tmp * mx + st;
    //     // res[i] =  
    //     st += t[i];
    //     i --;
    // }    
    // for(int i = 1; i <= n; i ++){
    //     cout<<res[i]<<" \n"[i==n];
    // }
    // // for(int i = 1; i <= n; i ++){
    // //     int u = i, v = (i == n ? 1 : i + 1);
    //     // int LCA = lca(u, v);
    //     // ss[i] = ask_path(u,v) - ask_path(LCA,LCA);
    //     // cout<<ss[i]<<'\n';
    //     // res[n] = ss[i] * t[i];
    // // }
    // // cout << res[n] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    cin >> T;
    while (T --){
        solve();
    }

    return 0;
}
```

关注到题目给出的性质 :

给的树是按照 dfs 序标号给出的，也就是对于以 $i$ 为根的子树，会包含 $[i,i+sz_i-1]$ 这些标号。

这样带来一个性质 ：

对于每个边 $p_i \rightarrow i$ ，只会被包含在两个路径中 : 

分别是 $dist(i-1,i)$ 和 $dist(i+sz_i-1,i+sz_i)$ 。

对于每个路径，如果所有边都被确定了，那么这个 dist 唯一。

否则，这个 dist 就是已经确定的边加上剩余的 w

设 $cnt$ 为未完全确定所有边的路径的数量，$sum$ 为已经给出的边权之和。

那么答案就是 $2w + cnt\times (w-sum)$ 。

```cpp
int n, w;
int sz[N], p[N];
pair<int, int> to[N]; // 边 i 属于 {fs, sc} 这两个 dist
vector<int> e[N];
unordered_set<int> path[N]; // dist(i, i + 1) 包含的边

void dfs(int u, int fa){
    sz[u] = 1;
    for(int v : e[u]){
        if(v == fa) continue ;
        dfs(v, u);
        sz[u] += sz[v];
    }
}

void solve(){
    cin >> n >> w;
    for(int i = 1; i <= n; i ++){
        e[i].clear();
        path[i].clear();
    }
    for(int i = 2; i <= n; i ++){
        cin >> p[i];
        e[p[i]].push_back(i);
    }
    dfs(1, 0);
    for(int i = 2; i <= n; i ++){
        to[i] = {i - 1, i + sz[i] - 1};
        path[i - 1].insert(i);
        path[i + sz[i] - 1].insert(i);
    }
    // res = sum * 2 + (w - sum) * cnt
    int sum = 0, cnt = n;
    for(int i = 2; i <= n; i ++){
        int x, y; // 给出第 x 条边的权值为 y
        cin >> x >> y;
        int fs = to[x].first, sc = to[x].second;
        path[fs].erase(x);
        path[sc].erase(x);
        if(!path[fs].size()) cnt --;
        if(!path[sc].size()) cnt --;
        sum += y;
        cout << 2 * sum + (w - sum) * cnt << " \n"[i == n];
    }
}
```

如果你想不到上述性质，赛时可以多模拟样例。

这样基本可以发现，每个边会被 `dist` 经过两次。

那么不就是每个边会出现在两个 `dist` 中吗 ？

进一步推理，发现两个 `dist` 其实是固定，就是上文推得那两种。

对于 $p_i \rightarrow i$ 的边，会被 $dist_i$ 和 $dist_{i+sz_i-1}$ 经过。

 这样基本会维护就能做出来了，维护用 uset 就行了，也不用任何高级的 DS 。

## F

考虑 $a$ 经过有限次操作之后的最后形态。一定是形成的差分数组 $b$ 的所有值相同且均为奇数。

如果是 $b_i$ 是偶数，那么 $a_i+a_{i-1}$ 是偶数，可以往中间塞一个数，构造出两个 $\frac {b_i } 2$ 。

如果 $b_{i+1}$ 跟 $b_{i}$ 是两个不同的奇数，那么可以证明 $a_{i-1}+a_{i+1}$ 是一个偶数，且它除 $2$ 之后得到的是一个 $\neq a_i$ 的偶数。

如果这个数 $x>a_i$ ，那么 $x$ 会削减 $a_i$ 与 $a_{i+1}$ 的差分数组，但这些一定都是 $\gcd b$ 的倍数，最终所有数会变成 $\gcd b_i$ 。

更严谨的证明我也不会。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 4e5 + 10;
int n, cnt, a[N], b[N], c[N], sc[N];

int const sz = __lg(N) + 3;
int Log2[N], f[N][sz];

int ask_gcd(int l, int r){
    // vector<int> t;
    // int d = 0;
    // for(int i = l; i <= r; i ++) t.push_back(b[i]);
    // sort(t.begin(), t.end());
    // for(auto &x : t) d = __gcd(d, x);
    // return d;
    int s = Log2[r - l + 1];
    int t = __gcd(f[l][s], f[r - (1 << s) + 1][s]);
    while(t && t % 2 == 0) t /= 2;
    return t;
}

int ask(int l, int r){
    if(l > r) return 0;
    return sc[r] - sc[l - 1];
}

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    cnt = 0;
    for(int i = 1; i <= n; i ++){
        int j = i;
        while(j <= n && a[j] == a[i]) j ++;
        a[++ cnt] = a[i];
        c[cnt] = j - i;
        sc[cnt] = sc[cnt - 1] + c[cnt];
        i = j - 1;
    }
    for(int i = 2; i <= cnt; i ++){
        b[i] = abs(a[i] - a[i - 1]);
        // while(b[i] % 2 == 0) b[i] /= 2;
    }

    for(int i = 1; i <= cnt; i ++){
        f[i][0] = b[i];
    }

    for(int j = 1; j < sz; j ++){
        for(int i = 1; i + (1 << j) - 1 <= cnt; i ++){
            f[i][j] = __gcd(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
        }
    }

    // cout << "cnt: " << cnt << '\n';
    // for(int i = 1; i <= cnt; i ++){
    //     cout << a[i] << " \n"[i == cnt];
    // }
    // for(int i = 1; i <= cnt; i ++){
    //     cout << b[i] << " \n"[i == cnt];
    // }
    // for(int i = 1; i <= cnt; i ++){
    //     cout << c[i] << " \n"[i == cnt];
    // }

    int res = 0;
    for(int i = 1, j = 2; i <= cnt; i ++){
        // while(j <= i) j ++;
        // int g = ask_gcd(i + 1, j);
        // while(j <= cnt && ask_gcd(i + 1, j) != 1) j ++;
        int tmp = 0;
        if(ask_gcd(i + 1, cnt) != 1){
            tmp = cnt + 1;
        }
        else{
            int l = i + 1, r = cnt;
            while(l < r){
                int mid = l + r >> 1;
                if(ask_gcd(i + 1, mid) == 1) r = mid;
                else l = mid + 1;
            }
            tmp = l;
        }

        res += c[i] * (c[i] + 1) / 2 + c[i] * ask(tmp, cnt);
        // cout << i << ' ' << j << ' ' << c[i] << ' ' << ask(tmp, cnt) << ' ' << c[i] * (c[i] + 1) / 2 + c[i] * ask(j, cnt) << '\n';
    }
    cout << res << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 

    for(int i = 2; i < N; i ++){
        Log2[i] = Log2[i / 2] + 1;
    }

    int T;
    cin >> T;
    while(T --){
        solve();
    }

    return 0;
}
```
