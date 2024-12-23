## A

```cpp
void solve(){
    int k;
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> in[i];
    }
    for(int i = n - k + 1; i <= n; i ++) cout << in[i] << ' ';
    for(int i = 1; i <= n - k; i ++) cout << in[i] << ' ';
}
```

## B

模拟

```cpp
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> in[i];
    }
    int s = 0;
    while(true){
        sort(in + 1, in + n + 1, [](int a, int b){
            return a > b;
        });
        if(in[1] == 0 || in[2] == 0) break;
        in[1] --;
        in[2] --;
        s ++;
    }
    cout << s << '\n';
}
```

## C

发现对于对于每个怪物的伤害与轮数成正相关，二分。

```cpp
void solve(){
    int res = 0; // 已经经过的进攻回合
    cin >> n;
    auto f = [&] (int x) -> int {
        if(res % 3 == 0){
            return x / 3 * 5 + x % 3;
        }
        if(res % 3 == 1){
            if(x == 1) return 1;
            if(x == 2) return 4;
            x -= 2;
            return 4 + x / 3 * 5 + x % 3;
        }
        if(res % 3 == 2){
            if(x == 1) return 3;
            -- x;
            return 3 + x / 3 * 5 + x % 3;
        }
        return 0;
    };
    // cout << f(4) << '\n';
    for(int i = 1; i <= n; i ++){
        cin >> q;
        int l = 1, r = 1e9;
        while(l < r){    
            int mid = l + r >> 1;
            if(f(mid) >= q) r = mid;
            else l = mid + 1;
        }
        // cout << i << ' ' << l << '\n';
        res += l;
    }
    cout << res;
    // int l = 0, r = 1e18;
    // while(l < r){
        // int mid = l + r >> 1;
        // if(mid / 3 * 3 + mid % 3 >= s) r = mid;
        // else l = mid + 1;
    // }
    // cout << l;
}
```

## D

### sol1

只需要将每一对相邻点 $u$ ，$v$ 的最短路径的边全部加 $1$ 即可，最后统计所有边权 $\geq 1$ 的边的数量。

使用重链剖分完成。（有点小题大做）

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define lc u << 1
#define rc u << 1 | 1
int const N = 2e5 + 10;
std::vector<int> e[N];
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

int n, k, m, q, a, b, c;

int in[N];



int fg[N], dp[N];

// fg : 是否需要并到答案集合
// dp : 以 i 为根子树达成要求的最小花费

int v[N];
set<int> sp;

void dfs1(int u, int fa, int up){
    if(sp.count(u)) fg[u] = 1;
    int s = 0;
    for(auto &v : e[u]){
        if(v == fa) continue ;
        dfs1(v, u);
        if(fg[v]) s ++;
    }
    if(s >= 2) fg[u] = 1;
}
// int dfs(int u, int fa){
//     if(fg[u] == 0) return dp[u] = 0;
//     dp[u] = 1;
//     for(auto &v : e[u]){
//         if(v == fa) continue ;
//         dfs(v, u);
//         if(fg[v]) dp[u] += dp[v];
//     }
//     return dp[u];
// }
// int p[N];
// int find(int u){
//     return p[u] == u ? u : p[u] = find(p[u]);
// }
void solve(){
    cin >> n >> k;
    // for(int i = 1; i <= n; i ++){
    //     cin >> p[i];
    // }
    for(int i = 1; i < n; i ++){
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    for(int i = 1; i <= k; i ++){
        cin >> v[i];
        if(i >= 2){
            update_path(v[i], v[i - 1], 1);
            int Lca = lca(v[i], v[i - 1]);
            update_path(Lca, Lca, -1);
        }
        // sp.insert(v[i]);
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
        for(auto &j : e[i]){
            if(j > i){
                int Lca = lca(i,j);
                if(ask_path(i, j) - ask_path(Lca,Lca)>=1){
                    res ++;
                }
            }
        }    
    }
    res ++;
    cout <<res;// max(res,0LL);
    // for(int i = 1; )
    // dfs1(1, 0);
    // cout << dfs(1, 0) << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    while (T --){
        solve();
    }

    return 0;
}
```

### sol2

发现以随意一个需要选择的点以根节点。

这样形态的树，对于根节点的每个链，最深的被需要的儿子下面的都不选即可。

```cpp
int n, k;
vector<int> p;
vector<int> e[N];
int fg[N];

void dfs(int u, int fa){
    for(auto &v : e[u]){
        if(v == fa) continue ;
        dfs(v, u);
        fg[u] |= fg[v];
    }
}

void solve(){
    cin >> n >> k;
    for(int i = 1; i < n; i ++){
        int a, b;
        cin >> a >> b;
        e[a].push_back(b);
        e[b].push_back(a);
    }
    for(int i = 1; i <= k; i ++){
        int x;
        cin >> x;
        fg[x] = 1;
        p.push_back(x);
    }
    dfs(p[0], 0);
    cout << accumulate(fg + 1, fg + n + 1, 0LL) << '\n';
}
```

## E

参考 jiangly 的代码。

对于 $\forall j$ ，需要找到以下 $i$ :

$b_i=a_j，t_i\leq s_j$ ，

它们需要满足 :

$t_i+x_t\leq s_j+x_j$ ，即 $x_j\geq t_i+x_i-s_j$ 

那么为了让 $x$ 最小，$x$ 取 $\max _{b_i=a_j,t_i\leq s_j}{t_i+x_i-s_j} $ 即可。

按照时间排序，对于每个 $s$ 要处理询问，对于每个 $t$ 维护 $t+x$ 的最值即可。

```cpp
#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, X0;
    cin >> N >> M >> X0;
    
    vector<int> A(M), B(M), S(M), T(M);
    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> S[i] >> T[i];
        A[i]--;
        B[i]--;
    }
    
    vector<array<int, 3>> e(2 * M);
    for (int i = 0; i < M; i++) {
        e[2 * i] = {S[i], 1, i}; // 查询用 1
        e[2 * i + 1] = {T[i], 0, i}; // 更新用 0
    }
    
    sort(e.begin(), e.end());
 
    vector<int> X(M);
    vector<int> tm(N); // 表示 b[i] 的最大的 T[i] + X[i]
    X[0] = X0;
    for (auto [t, o, i] : e) {
        if (o == 1) { // 查询 X[i]
            X[i] = max(X[i], tm[A[i]] - S[i]);
        } else { // 
            tm[B[i]] = max(tm[B[i]], T[i] + X[i]);
        }
    }
    
    for (int i = 1; i < M; i++) {
        cout << X[i] << " \n"[i == M - 1];
    }
    
    return 0;
}
```

## F

F 是一个公平组合游戏，而且总状态有限，每个状态的后继状态在 $O(\sqrt x)$ 时间内即可枚举完。

所以使用 `sg` 定理求解

```cpp
int n;

int a[N];
int f[N];

int sg(int x){
    if(f[x] != -1) return f[x];
    unordered_set<int> q;
    for(int i = 1; i <= x / i; i ++){
        if(x % i == 0){
            if(x / i != x) q.insert(sg(x / i));
            if(i != x) q.insert(sg(i));
        }
    }
    for(int i = 0; ; i ++){
        if(!q.count(i)) return f[x] = i;
    }
}

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    memset(f, -1, sizeof f);
    int res = 0;
    for(int i = 1; i <= n; i ++){
        res ^= sg(a[i]);
    }

    cout << (res ? "Anna" : "Bruno") << '\n';
}
```

## G

特别需要注意到题目保证第三种询问的答案不会超过 $10^{18}$ ，又因为 $2^{59}<10^{18}<2^{60}$ ，

所以选择 $b$ 的次数一定不会超过 $60$ 次。

因此对于每个询问，可以选择的 $b$ 及其有限。

我们用一个 $set$ 维护所有 $b_i\neq 2$ 的位置，用 $BIT$ 维护 $a$ 的区间和。

那么对于每个询问，查询出来所有决策点，即 $b_i\geq 2$ 的位置，对于 $b_i=1$ 的位置，一定选择加法的，对于所有决策点，选择更优的。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, q, a[N], b[N];

int tr[N];

void add(int p, int v){
    for(int i = p; i < N; i += i & -i){
        tr[i] += v;
    }
}

int ask(int p){
    int res = 0;
    for(int i = p; i; i -= i & -i){
        res += tr[i];
    }
    return res;
}

int ask(int l, int r){
    if(l > r) return 0;
    return ask(r) - ask(l - 1);
}

set<int> pos;

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        add(i, a[i]);
    }
    for(int i = 1; i <= n; i ++){
        cin >> b[i];
        if(b[i] > 1){
            pos.insert(i);
        }
    }
    cin >> q;
    while(q --){
        int opt, l, r;
        cin >> opt >> l >> r;
        if(opt == 1){
            add(l, r - a[l]);
            a[l] = r;
        }
        else if(opt == 2){
            if(r == b[l]) continue ;
            if(b[l] == 1){ // 1 变非 1
                pos.insert(l);
            }
            if(r == 1){
                pos.erase(l);
            }
            b[l] = r;
        }
        else{
            int res = a[l];
            if(l != r){
                l ++;
                vector<int> p;
                auto it = pos.lower_bound(l);
                if(it != pos.end()){
                    while((*it) <= r && it != pos.end()){
                        p.push_back(*it);
                        it ++;
                    }
                }    
                // cout << "Pos: \n";
                // for(auto &ps : p) cout << ps << ' '; cout << '\n';
                if(p.size() == 0){
                    res += ask(l, r);
                }
                else{
                    res += ask(l, p[0] - 1);
                    res = max(res * b[p[0]], res + a[p[0]]);
                    // res *= b[p[0]];
                    for(int i = 0; i + 1 < p.size(); i ++){
                        res += ask(p[i] + 1, p[i + 1] - 1);
                        res = max(res * b[p[i + 1]], res + a[p[i + 1]]);
                        // res *= b[p[i + 1]];
                    }
                    res += ask(p.back() + 1, r);
                }
            }
            cout << res << '\n';
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
```
