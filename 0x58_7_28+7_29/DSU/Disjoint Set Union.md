## Problem One : 维护区间连通块

[F - Range Connect MST (atcoder.jp)](https://atcoder.jp/contests/abc364/tasks/abc364_f)

暴力模拟的话，就是基于 Kruskal 的思想，按 $c$ 从小到大排序，对于每次询问，枚举检查 $j\in [l,r]$ ，只要 $j$ 与 $n+i$ 不连通，就连一条边。  

我们用并查集优化，并查集维护 $1\sim n$ 这些点，把他们维护为一个连通分量，祖先节点为最右边的节点，这样对于每次询问，对于 $[l,r]$ 的每个连通分量，跟 $n+i$ 连边即可，最后把他们全部 merge 起来。

$O(Q(\log Q+\alpha(N))$ 。

tips ：

DSU（Disjoint Set Union） 的时间复杂度通常被表示为 O(α(N))，其中 α 是阿克曼函数的反函数。阿克曼函数 A(m,n) 是一个非常快增长的函数，而它的反函数 α(N) 增长得非常缓慢，几乎可以认为是常数。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, q;
struct info{
    int l, r, c;
    bool operator < (const info &T) const{
        return c < T.c;
    }
}infos[N];

int p[N];
int find(int x){
    if(x == p[x]) return x;
    return p[x] = find(p[x]);
}
void merge(int x, int y){
    x = find(x), y = find(y);
    if(x != y) p[x] = y;
}
void solve(){
    cin >> n >> q;
    for(int i = 1; i <= n; i ++){
        p[i] = i;
    }
    for(int i = 1; i <= q; i ++){
        int l, r, c;
        cin >> l >> r >> c;
        infos[i] = {l, r, c};
    }
    int res = 0;
    sort(infos + 1, infos + q + 1);
    for(int i = 1; i <= q; i ++){
        auto [l, r, c] = infos[i];
        int j = find(l); 
        res += c; 
        while(j < r){
            int t = find(j + 1); 
            merge(j, t);
            j = t; 
            res += c;
        } 
    }
    for(int i = 1; i <= n; i ++){
        if(find(i) != find(1)){
            res = -1;
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
```

## Problem Two : 带权并查集维护到根节点最大距离

[A-LCT_2024牛客暑期多校训练营4 (nowcoder.com)](https://ac.nowcoder.com/acm/contest/81599/A)

> Note the **unusual memory limit** for this problem.
> 
> Given a rooted tree with $\textstyle n$ nodes and $\textstyle n-1$ edges. The $\textstyle i$\-th edge can be described by $\textstyle (a_i, b_i)$, which represents an edge connecting node $\textstyle a_i$ and node $\textstyle b_i$, where node $\textstyle a_i$ is the parent of node $\textstyle b_i$.
> 
> There are $\textstyle n-1$ queries. The $\textstyle i$\-th query contains an integer $\textstyle c_i$, asking for the length of the longest simple path starting from node $\textstyle c_i$ in the graph (forest) formed by the first $\textstyle i$ edges. **It is guaranteed that there does not exist $\textstyle j$ such that $\textstyle 1 \leq j \leq i$ and $\textstyle b_j = c_i$, i.e., $\textstyle c_i$ is the root of a tree in the forest.**

给 $n$ 个点，添加 $n-1$ 条边，每次询问某个树根代表的树的最大深度，并查集路径压缩维护每个点到根节点的距离以及每棵树的最大深度。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n, p[N], d[N], mx[N];

int find(int x){
    if(x == p[x]) return x;
    int t = find(p[x]);
    d[x] += d[p[x]];
    return p[x] = t;
}

void merge(int x, int y){
    int fx = find(x), fy = find(y);
    if(fx != fy){
        p[x] = fy;
        d[x] = d[y] + 1;
        mx[fy] = max(mx[fy], d[y] + mx[fx] + 1);
    }
}

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        p[i] = i;
        d[i] = 0;
        mx[i] = 0;
    }
    for(int i = 1; i < n; i ++){
        int a, b, c;
        cin >> a >> b >> c;
        merge(b, a);
        cout << mx[find(c)] << ' ';
    }
    cout << '\n';
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

## Problem Three : 维护前缀和判定关系

> [4286. 多少个答案是错误的 - AcWing题库](https://www.acwing.com/problem/content/4289/) 
> 
> 有一个长度为 N 的整数序列。
> 
> 下面会按顺序给出 M 个对该序列的描述，每个描述给定三个整数 l,r,s，表示该序列的第 l 个元素至第 r 个元素相加之和为 s。
> 
> 对于每个描述，你需要判断该描述是否会与前面提到的描述发生冲突，如果发生冲突，则认为该描述是错误的。
> 
> 如果一个描述是错误的，则在对后续描述进行判断时，应当将其忽略。
> 
> 请你计算一共有多少个描述是错误的。

我们将每次查询区间元素之和转化为查询前缀和关系。

对于 $l,r,s$ ，如果 $l$ 与 $r$ 的前缀和关系确定，那么 $prefix_r-prefix_{l-1}$ 就应该等于 $s$ 。

如果当前前缀和关系尚未确定，那么维护这次关系 $l,r,s$ 。

注意要维护 $n+1$ 个点。

关于 : 为什么对于每个 $l,r$ ，不直接维护 $l,r$ 的关系，表示 $r$ 到 $l$ 的距离呢 ?

实际上确定区间 $l,r$ 的关系，只需要知道 $r$ 与 $l-1$ 是否存在关系即可，例如

$$
1\;5 \\
1\;3 \\
4\; 5
$$

这种询问， $4\;5$ 只需要知道 $5$ 跟 $3$ 是否存在关系即可，因此我们每次维护 $r$ 跟 $l-1$ 的关系即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, m;
int p[N], d[N];

int find(int x){
    if(x == p[x]) return x;
    int t = find(p[x]);
    d[x] += d[p[x]];
    return p[x] = t;
}

void solve(){
    cin >> n >> m;
    for(int i = 0; i <= n; i ++){
        p[i] = i;
        d[i] = 0;
    }
    int res = 0;
    while(m --){
        int l, r, s;
        cin >> l >> r >> s;
        l --;
        if(find(l) == find(r)){
            res += (s != d[r] - d[l]);
        }
        else{
            int pl = find(l), pr = find(r);
            if(pl < pr){
                p[pr] = pl;
                d[pr] = -d[r] + s + d[l]; 
            }
            else{
                p[pl] = pr;
                d[pl] = d[r] - s - d[l];
            }
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
```

## Problem Four : 维护前缀和判定关系

> [239. 奇偶游戏 - AcWing题库](https://www.acwing.com/problem/content/description/241/)

跟上一题的本质相同，还是维护前缀和之间的关系，不过我们这次的距离对 $2$ 取模，仅维护到根节点的奇偶性即可，$0$ 表示偶数。$1$ 表示奇数。尚未确定的查询维护出来，否则检查给出的奇偶性是否符合已有的奇偶性。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;

struct Query{
    int l, r, tp;
}q[5100];


unordered_map<int, int> p, d;
int find(int x, unordered_map<int, int> &mp){
    if(x == mp[x]) return x;
    int t = find(mp[x], mp);
    (d[x] += d[mp[x]]) %= 2;
    return mp[x] = t;
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        int l, r;
        string s;
        cin >> l >> r >> s;
        l --;
        q[i] = {l, r, s == "odd" ? 1 : 0};
        p[l] = l, p[r] = r;
        d[l] = d[r] = 0;
    }    
    for(int i = 1; i <= m; i ++){
        auto& [l, r, tp] = q[i];
        int pl = find(l, p), pr = find(r, p);
        if(pl == pr){
            if(((d[r] - d[l]) % 2 + 2) % 2 != tp){
                cout << i - 1 << '\n';
                return ;
            }
        }
        else{
            p[pr] = pl;
            d[pr] = ((d[l] + tp - d[r]) % 2 + 2) % 2;
        }
    }
    cout << m << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```

## Problem Five : 判定关系

> [4288. 研究虫子 - AcWing题库](https://www.acwing.com/problem/content/4291/)

这题比较简单，之所以拿出来，是加深并查集检查关系正确与否的思想。

关系尚不确定的，并查集维护关系。关系可以确定的，根据题目要求进行检查。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int p[2100], d[2100];

int find(int x){
    if(x == p[x]) return x;
    int t = find(p[x]);
    (d[x] += d[p[x]]) %= 2;
    return p[x] = t;
}

void solve(int yyy){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        p[i] = i;
        d[i] = 0;
    }
    bool fg = false;
    while(m --){
        int a, b;
        cin >> a >> b;
        int pa = find(a), pb = find(b);
        if(pa != pb){
            p[pb] = pa;
            d[pb] = ((1 + d[a] - d[b]) % 2 + 2) % 2;
        }
        else{
            if(((d[a] - d[b]) % 2 + 2) % 2 != 1){
                fg = true;
            }
        }
    }
    cout << "Scenario #"<<yyy<<":\n";
    cout << (fg ? "Suspicious bugs found!" : "No suspicious bugs found!") << '\n';
    cout << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    cin >> T;
    for(int i = 1; i <= T; i ++){
        solve(i);
    }

    return 0;
}
```

## Problem Six : 判定树 - 无向图

> [4290. 小希的迷宫 - AcWing题库](https://www.acwing.com/problem/content/4293/)  
> 
> 给你 $m$ 条无向边，构成无向图，判定图是不是树的形式

满足以下两个性质即可 :

- 连通性 : 树根只有一个

- 无环性 : 并查集判定是否有回路

（注意还要定义空图是不是树）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N = 1e5 + 10;
int a, b, p[N];

int find(int x){
    if(x == p[x]) return x;
    return p[x] = find(p[x]);
}

// t 数组用于维护 p 数组初始化
// 输入 n 次之后一定不是树，所以开 N << 1
int cnt = 0, t[N << 1]; 

void solve(){
    bool fg = true;
    for(int i = 1; i <= 100000; i ++){
        p[i] = i;
    }
    while(cin >> a >> b){
        if(a == -1 && b == -1){
            return ;
        }
        if(a == 0 && b == 0){ 
            for(int i = 1; fg && i < cnt; i ++){
                if(find(t[i]) != find(t[i + 1])){
                    fg = false;
                }
            }
            cout << (fg ? "Yes" : "No") << '\n';
            for(int i = 1; i <= cnt; i ++){
                p[t[i]] = t[i];
            }
            cnt = 0;
            fg = true;
            continue ;
        }
        if(fg == false) continue ; // 不再维护, 已经不合法
        t[++ cnt] = a, t[++ cnt] = b;
        if(find(a) == find(b)) fg = false;
        else p[find(b)] = find(a);
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```

## Problem Seven : 判定树 - 有向图

> [3409. 这是一棵树吗 - AcWing题库](https://www.acwing.com/problem/content/description/3412/)
> 
> 给你 $m$ 条有向边，判定是否是树

需要满足以下性质 :

- 除了根节点以外，所有点入度均为 $1$ 

- 整个图连通 或者 没有环

只满足性质 $1$ ，可能是外向基环树 + 有根树构成的森林，所以还要判定连通性，保证只有一颗树，就没有外向基环树了。

或者直接当成无向边判环，把外向基环树判掉。

判环 Code : 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int in[10010], p[10010];
int find(int x){
    if(x == p[x]) return x;
    return p[x] = find(p[x]);
}
void solve(){
    int a, b, cnt = 1;
    fill(in + 1, in + 10001, -1);
    for(int i = 1; i <= 10000; i ++){
        p[i] = i;
    }
    while(cin >> a >> b){
        if(a == -1 && b == -1) return ;
        if(a == 0 && b == 0){
            int s0 = 0, s1 = 0, s2 = 0;
            for(int i = 1; i <= 10000; i ++){
                p[i] = i;
                if(in[i] == -1) continue ;
                if(in[i] == 0) s0 ++;
                else if(in[i] == 1) s1 ++;
                else s2 ++;
            }
//             cout << s0 << ' ' << s1 << ' ' << s2 << '\n';
            if((s2 || s0 != 1) && ((!s0 && !s1 && !s2) == false)){
                cout << "Case " << cnt << " is not a tree.\n";
            }
            else{
                cout << "Case " << cnt << " is a tree.\n";
            }
            fill(in + 1, in + 10001, -1);
//             for(int i = 1; i <= 10000; i ++) in[i] = 0;
            cnt ++;
            continue ;
        }
        int pa = find(a), pb = find(b);
        if(pa == pb) in[b] = 2;
        else p[pb] = pa;
        if(in[b] == -1) in[b] = 0;
        if(in[a] == -1) in[a] = 0;
        if(a == b) in[b] = 2; // 自环的处理
        in[b] ++;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
// 只有一个 in[] = 0, else = 1
```

判联通性 Code

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int in[10010], p[10010];
int find(int x){
    if(x == p[x]) return x;
    return p[x] = find(p[x]);
}
void solve(){
    int a, b, cnt = 1;
    fill(in + 1, in + 10001, -1);
    for(int i = 1; i <= 10000; i ++){
        p[i] = i;
    }
    while(cin >> a >> b){
        if(a == -1 && b == -1) return ;
        if(a == 0 && b == 0){
            int s0 = 0, s1 = 0, s2 = 0;
            int fsP = -1;
            for(int i = 1; i <= 10000; i ++){
                if(in[i] == -1) continue ;
                fsP = (fsP == -1 ? i : fsP);
                if(in[i] == 0) s0 ++;
                else if(in[i] == 1) s1 ++;
                else s2 ++;
            }
            for(int i = 1; i <= 10000; i ++){
                if(in[i] == -1) continue ;
                if(find(i) != find(fsP)){
                    s2 = 1000;
                }
            }
//             cout << s0 << ' ' << s1 << ' ' << s2 << '\n';
            if((s2 || s0 != 1) && ((!s0 && !s1 && !s2) == false)){
                cout << "Case " << cnt << " is not a tree.\n";
            }
            else{
                cout << "Case " << cnt << " is a tree.\n";
            }
            for(int i = 1; i <= 10000; i ++){
                p[i] = i;
            }
            fill(in + 1, in + 10001, -1);
//             for(int i = 1; i <= 10000; i ++) in[i] = 0;
            cnt ++;
            continue ;
        }
        int pa = find(a), pb = find(b);
        if(pa == pb) {}//in[b] = 2;
        else p[pb] = pa;
        if(in[b] == -1) in[b] = 0;
        if(in[a] == -1) in[a] = 0;
        if(a == b) in[b] = 2; // 自环的处理
        in[b] ++;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
// 只有一个 in[] = 0, else = 1
```

## Problem Eight : 带权并查集维护距离

> [4287. 导航噩梦 - AcWing题库](https://www.acwing.com/problem/content/4290/)

$4$ 个方向有 $4$ 个距离，带权并查集维护两种距离，$dx$ 维护横轴距离，$dy$ 维护纵轴距离，对于每个查询，对应的曼哈顿距离 $|x_1-x_2|+|y_1-y_2|$ 的 $x$ 之差与 $y$ 之差是相互独立的，我们分别进行查询即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 40010;
int const M = 40010;

int n, m, k;
struct info{
    int a, b, l;
    char d;
    vector<pair< pair<int, int>, int> > ask;
}infos[M];

int ans[N];

int p[N], dx[N], dy[N];

int find(int x){
    if(x == p[x]) return x;
    int t = find(p[x]);
    dx[x] += dx[p[x]];
    dy[x] += dy[p[x]];
    return p[x] = t;
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        p[i] = i;
        dx[i] = 0;
        dy[i] = 0;
    }
    for(int i = 1; i <= m; i ++){
        int a, b, c;
        char x;
        cin >> a >> b >> c >> x;
        infos[i] = {a, b, c, x};
    }
    cin >> k;
    for(int i = 1; i <= k; i ++){
        int a, b, I;
        cin >> a >> b >> I;
        infos[I].ask.push_back({ {a, b}, i});
    }
    for(int i = 1; i <= m; i ++){
        auto &[a, b, d, x, vc] = infos[i];
        {
            int pa = find(a), pb = find(b);
            if(pa != pb){
                p[pb] = pa;
                dx[pb] = dx[a] + (x == 'E' ? d : (x == 'W' ? -d : 0)) - dx[b];
                dy[pb] = dy[a] + (x == 'N' ? d : (x == 'S' ? -d : 0)) - dy[b];
            }
        }
        if(vc.size()){
            for(auto& [pr, id] : vc){
                auto& [a, b] = pr;
                int pa = find(a), pb = find(b);
                ans[id] = (pa == pb ? abs(dx[b] - dx[a]) + abs(dy[b] - dy[a]) : -1); 
            }
        }
    }
    for(int i = 1; i <= k; i ++) cout << ans[i] << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```

## Problem Nine : 并查集维护连通分量信息

可以用并查集维护集合 $max$ ，集合 $min$ 等等集合信息。

本题是维护集合 $max$ 的编号，如果有多个 $max$ ，取最小编号。

注意这种维护只有祖先节点的值有意义，所以我们在 `find` 祖先节点的过程中不需要维护 $max$ 信息，因为他们已经位于同一个连通块。

进行合并的时候，指定一个祖先节点，将另一个祖先的 $max$ 与之比较，维护 $max$ 信息。

因为并查集删边很难，加边简单。所以先全删除要删除的边，然后维护并查集，倒着加边，根据需要输出信息即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 10010;
int const M = 20010;
int const Q = 50010;

struct Edge{
    int a, b; 
}edges[M];
set<pair<int, int> > st;
int n, m, q;
int v[N];
struct Query{
    int tp;
    int a, b;
}querys[Q];

int p[N], d[N];

// 注意这种维护只有祖先结点的值有意义
// 所以已经位于同一个连通块的点不用维护
int find(int x){
    if(x == p[x]) return x;
    return p[x] = find(p[x]);
}
int cal(int a, int b){
    if(v[a] == v[b]) return min(a, b);
    else if(v[a] > v[b]) return a;
    return b;
}
void merge(int a, int b){
    int pa = find(a), pb = find(b);
    if(pa != pb){
        p[pb] = pa;
        d[pa] = cal(d[pa], d[pb]);
    }
}

void solve(){
    for(int i = 1; i <= n; i ++){
        cin >> v[i];
        p[i] = i;
        d[i] = i;
    }
    st.clear();
    cin >> m;
    for(int i = 1; i <= m; i ++){
        int a, b;
        cin >> a >> b;
        if(a > b) swap(a, b);
        edges[i] = {++ a, ++ b};
    }
    cin >> q;
    for(int i = 1; i <= q; i ++){
        string op;
        int a, b;
        cin >> op;
        if(op == "query"){
            cin >> a; 
            querys[i] = {0, ++ a};
        }
        else{
            cin >> a >> b;
            if(a > b) swap(a, b);
            querys[i] = {1, ++ a, ++ b};
            st.insert({a, b});
        }
    }
    for(int i = 1; i <= m; i ++){
        auto& [a, b] = edges[i];
        if(st.count({a, b}) == false){
            // cout << "merge: " << a << ' ' << b << '\n'; 
            merge(a, b);
        }
    }
    std::vector<int> ans;
    for(int i = q; i >= 1; i --){
        int tp = querys[i].tp;
        if(tp == 0){
            int a = querys[i].a, pa = find(a);
            if(v[d[pa]] > v[a]){
                ans.push_back(d[pa] - 1);
            }
            else{
                ans.push_back(-1);
            }
        }
        else{
            int a = querys[i].a, b = querys[i].b;
            // cout << "Merge: " << i << ' ' <<  a << ' ' << b << '\n';
            // cout << d[find(a)] << '\n';
            merge(a, b);
        }
    }
    for(auto i = ans.rbegin(); i != ans.rend(); i ++){
        cout << (*i) << '\n';
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    int fg = 0;
    while(cin >> n){
        if(!fg) fg = 1;
        else cout << '\n';
        solve();        
    }
    return 0;
}
```

下面是对拍时用到的代码 :

```cpp
int cnt = 0;
pair<int, int> edge[1000];
set<pair<int, int> > st;

int main(){

    // 生成随机数种子，利用 timeb 生成毫秒级别随机数
    struct _timeb T;
    _ftime(&T);
    srand(T.millitm);    

    int n = Data(2, 5);
    cout << n << '\n';
    for(int i = 1; i <= n; i ++){
        cout << Data(1, 10) << " \n"[i == n];
    }
    int m = Data(1, n * (n - 1) / 2);
    cout << m << '\n';
    for(int i = 1; i <= m; i ++){
        int a, b;
        while(true){
            a = Data(1, n);
            b = Data(1, n);    
            if(a > b) swap(a, b);
            if(a == b) continue ;
            if(st.count({a, b}) == false) break;
        }
        -- a, -- b;
        st.insert({a, b});
        edge[++ cnt] = {a, b};
        cout << a << ' ' << b << '\n';
    }
    int q = Data(1, 5);
    cout << q << '\n';
    for(int i = 1; i <= q; i ++){
        int op = Data(1, 2);
        if(cnt == 0 && op == 1) op = 0;
        if(op == 1){
            cout << "destroy ";
            int e = Data(1, cnt);
            cout << edge[e].first << ' ' << edge[e].second << '\n';
            swap(edge[e], edge[cnt]);
            cnt --;
        }
        else{
            cout << "query ";
            int a = Data(1, n);
            -- a;
            cout << a << '\n';
        }
    }

    return 0;
} 
```

## Problem Ten : 并查集判定关系

[258. 石头剪子布 - AcWing题库](https://www.acwing.com/problem/content/solution/260/1/) 

这题题面有问题，我修改成了下面这个，并且提交了工单。

> 输出格式
> 
> 每组测试用例输出一行结果。
> 
> 如果只能有一个人是裁判，则输出他的编号和确定他是唯一裁判的轮数。
> 
> 如果裁判的人选多于 1 个，则输出 `Can not determine`。
> 
> 如果必须存在多名裁判或者必须没有裁判，则输出 `Impossible`。
> 
> 具体格式可参考样例。

做法如下 :

枚举每个人是否可能是裁判，如果当前枚举的人不可能是裁判，记录确定他一定不是裁判时的编号。

最后查看裁判人选，$\geq 2$ 时无法判定谁是裁判。

$=1$ 说明只有一个人可能是裁判，假设这个人编号为 $j$, 只要确定其他人全部不是就可以了，假设第 $i$ 个人第 $t_i$ 轮被确定不是裁判，$res=\max_{i\neq j} t_i$ 

$=0$ 说明只有一个裁判的情况，所有关系都不合法，也就是说必须有多个裁判。

至于必须没有裁判的情况，这是不可能的，如果没有裁判不发生冲突，此时我们任意指定一个人为裁判都合法，所以不可能必须没有裁判。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;

struct Info{
    int a, b, dis;
}infos[2100];

int p[510], d[510];

int find(int x){
    if(x == p[x]) return x;
    int t = find(p[x]);
    d[x] = (d[x] + d[p[x]]) % 3;
    return p[x] = t;
}

void merge(int a, int b, int dis){
    int pa = find(a), pb = find(b);
    p[pb] = pa;
    d[pb] = ((dis + d[a] - d[b]) % 3 + 3) % 3;
} 

void solve(){
    for(int i = 1; i <= m; i ++){
        string s;
        int pos;
        cin >> s;
        for(int j = 0; j < s.size(); j ++){
            if(isdigit(s[j]) == false){
                pos = j;
                break;
            }
        }
        int a = stoi(s.substr(0, pos));
        int b = stoi(s.substr(pos + 1));
        int dis = (s[pos] == '=' ? 0 : (s[pos] == '<' ? 2 : 1));
        ++ a, ++ b;
        infos[i] = {a, b, dis};
    } 
    vector<int> v, pos;
    for(int judge = 1; judge <= n; judge ++){
        for(int i = 1; i <= n; i ++){
            p[i] = i;
            d[i] = 0;
        }
        bool fg = true;
        for(int i = 1; i <= m; i ++){
            auto& [a, b, dis] = infos[i];
            if(a == judge || b == judge) continue ;
            int pa = find(a), pb = find(b);
            if(pa != pb){
                merge(a, b, dis);
            }
            else{
                if(((d[b] - d[a]) % 3 + 3) % 3 != dis){
                    pos.push_back(i);
                    fg = false;
                    break;
                }   
            }
        }
        if(fg){
            v.push_back(judge);
        }
    } 
    if(v.size() >= 2){
        puts("Can not determine");      
    }
    else if(v.size() == 1){
        int res = ((size_t)pos.size() ? *max_element(pos.begin(), pos.end()) : 0);
        printf("Player %lld can be determined to be the judge after %lld lines\n", v[0] - 1, res);
    }
    else{
        puts("Impossible");     
    }
}

signed main(){
    // ios::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0); 
    while(cin >> n >> m){
        solve();        
    }
    return 0;
}
```

需要对拍数据可以用下面的，加上 0 0 表示结尾

```cpp
#include<bits/stdc++.h>
using namespace std;

// 0 <= rand()%(a+1) <= a
// k <= rand()%(a+1) <= a+k
// windows : rand() 生成的随机数在 0~32767 之间
/*
    生成一个 1 <= a <= 1,000,000 
    long long Random(long long mod){
        long long ans = 2147483647;
        return ans * rand() % mod + 1;
    }
    取 mod = 1, 000, 000 
*/  

// [k, k+mod-1] 
long long Random(long long k, long long mod){
    long long ans = 2147483647;
    return ans * rand() % mod + k;
}

long long Data(long long l, long long r){
    return Random(l, r - l + 1);
}

int main(){
    // 生成随机数种子，利用 timeb 生成毫秒级别随机数
    struct _timeb T;
    _ftime(&T);
    srand(T.millitm);    

    int n, m;
    n = Data(2, 5);
    m = Data(1, 10);
    cout << n << ' ' << m << '\n';
    for(int i = 1; i <= m; i ++){
        int op = Data(1, 3);
        int a = Data(1, n), b = Data(1, n);
        while(a == b){
            a = Data(1, n);
            b = Data(1, n);
        }
        if(a > b) swap(a, b);
        -- a, -- b;
        char x;
        if(op == 1){
            x = '=';
        }
        else if(op == 2){
            x = '<';
        }
        else{
            x = '>';
        }
        string res = to_string(a) + x + to_string(b);
        cout << res << '\n';
    }
    cout <<"0 0";

    return 0;
} 
```

## Problem Eleven : 并查集维护位置信息

> [145. 超市 - AcWing题库](https://www.acwing.com/problem/content/147/)
> 
> 超市里有 N 件商品，每件商品都有利润 pi 和过期时间 di，每天只能卖一件商品，过期商品不能再卖。
> 
> 求合理安排每天卖的商品的情况下，可以得到的最大收益是多少。

没想出来，感觉要贪心，看看题解吧。

做法一 :

我们倒着枚举天数，对于每种天数，把当前能卖的放进来，因为是倒着枚举，那么以后这些商品都可以卖，我们当然优先卖最大的，大根堆维护一下。

每组测试用例 : $O(n \log n)$ 

```cpp
int n;
vector<int> goods[N];

void solve(){
    for(int i = 1; i <= 10000; i ++){
        goods[i].clear();
    }
    for(int i = 1; i <= n; i ++){
        int p, d;
        cin >> p >> d;
        goods[d].push_back(p);
    }
    int ans = 0;
    priority_queue<int> q;
    for(int i = 10000; i >= 1; i --){
        for(auto &p : goods[i]){
            q.push(p);
        }
        if(q.size()){
            ans += q.top();
            q.pop();
        }
    }
    cout << ans << '\n';
}
```

做法二 :

做法一的本质，实际上就是对于每个利润大的商品，把它安排尽量晚的卖出。那么我们并查集维护能卖的位置即可，对于 $p$ 如果使用了，就把他跟 $p-1$ 合并。

$O(n+\alpha(n))$ 

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int const N = 1e4 + 10;
int p[N]; // 维护每个位置的能用的最左边位置

struct node{
    int p, d;
    bool operator < (const node & T) const {
        return p > T.p;
    }
}goods[N];

int find(int x){
    if(x == p[x]) return x;
    return p[x] = find(p[x]);
}

void merge(int a, int b){
    int pa = find(a), pb = find(b);
    if(pa != pb){
        if(pa < pb) p[pb] = pa;
        else p[pa] = pb;
    }
}

void solve(){
    for(int i = 0; i <= 10000; i ++){
        p[i] = i;
    }
    for(int i = 1; i <= n; i ++){
        int p, d;
        cin >> p >> d;
        goods[i] = {p, d};
    }
    sort(goods + 1, goods + n + 1);
    int ans = 0;
    for(int i = 1; i <= n; i ++){
        auto &[p, d] = goods[i];
        int pos = find(d);
        if(pos){
            ans += p;
            merge(pos, pos - 1);
        }
    }
    cout << ans << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 

    while(cin >> n){
        solve();
    }

    return 0;
}
```

## Problem Twelve : 并查集维护关系

`kuangbin` 专题里我留到最后一题，耗时最久的一题。

实际不是很难，但自己的 DP 出了点小问题，找了好久，对拍一开始没写对，又浪费了很长时间。

如果 $a$ 说 $b$ 是天使，

假设 $a$ 是天使，那么 $b$ 也是天使 ；假设 $a$ 是魔鬼，那么 $b$ 也是魔鬼

如果 $a$ 说 $b$ 是魔鬼，

假设 $a$ 是魔鬼，那么 $b$ 是天使 ；假设 $a$ 是天使，那么 $b$ 是魔鬼。

所以不难看出，回答 $yes$ 是 $a$ 与 $b$ 是同类 ，回答 $no$ 时 $a$ 与 $b$ 是异类。

所以我们用并查集维护。

维护之后，会得到很多互不连通的并查集，每个并查集与根节点距离为 $0$ 的设有 $x$ 个，距离为 $1$ 设有 $y$ 个，$DP$ 求一下选出 $p1$ 个人的方案数，如果为 $1$ ，回溯输出天使编号 ；否则输出魔鬼编号。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, p1, p2;

struct info{
    int x, y, dis;
}infos[1100];

int p[610], d[610]; 

int find(int x){
    if(x == p[x]) return x;
    int t = find(p[x]);
    d[x] = (d[x] + d[p[x]]) % 2;
    return p[x] = t;
}

pair<int, int> bk[610]; // 每个连通块的 0 1 数量
vector<int> same[610];
vector<int> dif[610];
map<int, int> mp;
int cnt = 0;
void debug_print(vector<vector<int> > &f) {
    cout << "Union-Find state:\n";
    for (int i = 1; i <= n; i++) {
        cout << "Node " << i << ": parent = " << p[i] << ", distance = " << d[i] << '\n';
    }

    cout << "BK array:\n";
    for (int i = 1; i <= cnt; i++) {
        cout << "Block " << i << ": 0's = " << bk[i].first << ", 1's = " << bk[i].second << '\n';
    }

    cout << "DP table:\n";
    for (int i = 0; i <= cnt; i++) {
        for (int j = 0; j <= p1; j++) {
            cout << f[i][j] << ' ';
        }
        cout << '\n';
    }
}


void solve(){
    n = p1 + p2;
    cnt = 0;
    mp.clear();
    for(int i = 1; i <= n; i ++){
        p[i] = i;
        d[i] = 0;
        bk[i] = {0, 0};
        same[i].clear();
        dif[i].clear();
    }
    for(int i = 1; i <= m; i ++){
        int x, y;
        string s;
        cin >> x >> y >> s;
        infos[i] = {x, y, s == "no"};
        // cout << x << ' ' << y << ' ' << (s == "no") << '\n';
    }

    for(int i = 1; i <= m; i ++){
        auto &[x, y, tp] = infos[i];
        if(x == y) continue ;
        int px = find(x), py = find(y);
        if(px != py){
            p[py] = px;
            d[py] = ((d[x] + tp - d[y]) % 2 + 2) % 2;
        }
        else{
            int t = ((d[x] - d[y]) % 2 + 2) % 2;
            if(t != tp){
                cout << "break\n";
                return ;
            }
        }
    }

    // cout << find(1) << ' ' << find(2) << '\n';
    // cout << d[1] << ' ' << d[2] << '\n';

    for(int i = 1; i <= n; i ++){
        if(find(i) == i){
            mp[i] = ++ cnt;
        }
    }
    for(int i = 1; i <= n; i ++){
        int pi = find(i), id = mp[pi];
        if(d[i] == 0){
            bk[id].first ++;
            same[id].push_back(i);
        }
        else{
            bk[id].second ++;
            dif[id].push_back(i);
        }
    }



    // f[i][j] 表示考虑到第 i 个连通块, 划分出来 p1 个天使的方案数
    vector<vector<int> > f(cnt + 1, vector<int> (p1 + 1, 0));
    f[0][0] = 1;
    if(bk[1].first <= p1) f[1][bk[1].first] ++ ;
    if(bk[1].second <= p1) f[1][bk[1].second] ++ ;
    for(int i = 1; i < cnt; i ++){
        int fs = bk[i + 1].first, sc = bk[i + 1].second;
        for(int j = 0; j <= p1; j ++){
            if(f[i][j]){
                if(j + fs <= p1){
                    f[i + 1][j + fs] += f[i][j];
                    if(f[i + 1][j + fs] > 1e9) f[i + 1][j + fs] = 1e9;
                }
                if(j + sc <= p1){
                    f[i + 1][j + sc] += f[i][j];
                    if(f[i + 1][j + sc] > 1e9) f[i + 1][j + sc] = 1e9;
                }
            }
        }
    }
    
    // debug_print(f);
    // cout << "f[1][0] : " << f[1][0] << '\n';
    // cout << "f[1][1] : " << f[1][1] << '\n';
    // cout << "f[2][1] : " << f[2][1] << '\n';

    // for(int i = 1; i <= n; i ++){
    //     cout << i << ' ' << find(i) << '\n';
    // }

    // cout << "cnt: ";
    // cout << cnt << '\n';
    // for(int i = 1; i <= cnt; i ++){
    //     cout << bk[i].first << ' ' << bk[i].second << '\n';
    // }
    // cout << f[cnt][p1] << '\n';
    
    // if(p1 != p2 && f[cnt][p1] == 1){
    if(f[cnt][p1] == 1){
        vector<int> choose(cnt + 1);
        int now = p1;
        for(int i = cnt; i >= 1; i --){
            int fs = bk[i].first, sc = bk[i].second;
            if(now >= fs && f[i - 1][now - fs] == 1){
                now -= fs;
                // cout << fs << '\n';
                choose[i] = (fs);
            }
            else if(now >= sc && f[i - 1][now - sc] == 1){
                now -= sc;
                // cout << sc << '\n';
                choose[i] = (sc);
            }
        }
        vector<int> res;
        for(int i = 1; i <= cnt; i ++){
            int t = choose[i];
            // cout << "t: " << t << '\n';
            if(t == bk[i].first){
                for(int j = 0; j < same[i].size(); j ++){
                    res.push_back(same[i][j]);
                }
            }
            else{
                for(int j = 0; j < dif[i].size(); j ++){
                    res.push_back(dif[i][j]);
                }
            }
        }
        sort(res.begin(), res.end());
        for(auto &x : res) cout << x << '\n';
        cout << "end\n";
    }
    else{
        cout << "no\n";
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    
    while(cin >> m >> p1 >> p2, m || p1 || p2){
        solve();
    }

    return 0;
}
// 要求唯一确定每个居民的身份
// f[i][j] 表示考虑到第 i 个并查集, 得到 j 个天使的方案数

```

对拍数据 (不保证给定关系不发生冲突) :

```cpp
#include<bits/stdc++.h>
using namespace std;

// 0 <= rand()%(a+1) <= a
// k <= rand()%(a+1) <= a+k
// windows : rand() 生成的随机数在 0~32767 之间
/*
	生成一个 1 <= a <= 1,000,000 
	long long Random(long long mod){
		long long ans = 2147483647;
		return ans * rand() % mod + 1;
	}
	取 mod = 1, 000, 000 
*/  

// [k, k+mod-1] 
long long Random(long long k, long long mod){
	long long ans = 2147483647;
	return ans * rand() % mod + k;
}

long long Data(long long l, long long r){
	return Random(l, r - l + 1);
}

int main(){
	// 生成随机数种子，利用 timeb 生成毫秒级别随机数
	struct _timeb T;
	_ftime(&T);
	srand(T.millitm);	

	// set<pair<int, int> > est;
	// est.insert({1, 2});
	// cout <<est.count({1,2})<<'\n';
	// cout <<est.count({2,1})<<'\n';

	
	int t = Data(1, 2);
	while(t --){
		int n, m, p1, p2;
		set<pair<int, int> > st = set<pair<int, int> > ();
		p1 = Data(1, 3);
		p2 = Data(1, 3);
		n = p1 + p2;
		m = Data(1, n * (n - 1) / 2);
		cout << m << ' ' << p1 << ' ' << p2 << '\n';
		while(m --){
			int x, y;
			while(true){
				x = Data(1, p1 + p2);
	 			y = Data(1, p1 + p2);
	 			if(x > y) swap(x, y);
	 			if(st.count({x, y})) continue;
	 			else break;
			}
			st.insert({x, y});
			int c = Data(1, 2);
	 		if(x == y) c = 2;
	 		cout << x << ' ' << y << ' ';
	 		if(c == 1) cout << "no\n";
	 		else cout << "yes\n";
		}
	}
 	cout <<"0 0 0";

	return 0;
} 

```
