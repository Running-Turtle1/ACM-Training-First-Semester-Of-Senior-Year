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
// 	if(fg[u] == 0) return dp[u] = 0;
// 	dp[u] = 1;
// 	for(auto &v : e[u]){
// 		if(v == fa) continue ;
// 		dfs(v, u);
// 		if(fg[v]) dp[u] += dp[v];
// 	}
// 	return dp[u];
// }
// int p[N];
// int find(int u){
// 	return p[u] == u ? u : p[u] = find(p[u]);
// }
void solve(){
	cin >> n >> k;
	// for(int i = 1; i <= n; i ++){
	// 	cin >> p[i];
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