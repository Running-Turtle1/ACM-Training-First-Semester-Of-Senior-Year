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
    // 	res[l]+=v;
    // 	res[r+1]-=v;
    // };
    // for(auto &[u, v] : edge){
    // 	i ++;
    // 	int LCA = lca(u, v);
    // 	ss[i] = ask_path(u,v) - ask_path(LCA,LCA);
    // 	tms[i] = ss[i] + tms[i - 1];
    // 	cout<<ss[i]<< ' '<<t[i]<<'\n';
    // 	// res[i] += ss[i] * t[i];
    // 	add(i, n, ss[i] * t[i]);
    // 	// res[n] += ss[i] * t[i];
    // }
    // for(int i = 1; i <= edge.size()+1; i ++){
    // 	res[i]+=res[i-1];
    // 	cout<<"i: "<<i<<' '<<res[i]<<'\n';
    // }
    // cout<<res[n]<<'\n';
    // int mx = -2e9;
    // int st = 0;
    // for(int i = edge.size() - 1; i > 0; i --){
    // 	i ++;
    // 	auto &[u, v] = edge[i];
    // 	mx = max(mx, t[i + 1]);
    // 	int tmp = sw - tms[i] - ((edge.size() - 1) - i);
    // 	cout<<"St:\n";
    // 	cout << tmp << '\n';
    // 	cout <<mx <<'\n';
    // 	cout<<st<<'\n';
    // 	res[i] += tmp * mx + st;
    // 	// res[i] =  
    // 	st += t[i];
    // 	i --;
    // }	
    // for(int i = 1; i <= n; i ++){
    // 	cout<<res[i]<<" \n"[i==n];
    // }
    // // for(int i = 1; i <= n; i ++){
    // // 	int u = i, v = (i == n ? 1 : i + 1);
    // 	// int LCA = lca(u, v);
    // 	// ss[i] = ask_path(u,v) - ask_path(LCA,LCA);
    // 	// cout<<ss[i]<<'\n';
    // 	// res[n] = ss[i] * t[i];
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