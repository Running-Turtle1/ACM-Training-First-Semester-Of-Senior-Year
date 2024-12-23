#include<bits/stdc++.h>
using namespace std;
#define int long long

#define wpc 0

int const N = 1100;

int n, k;
vector<int> e[N];
int d[N]; // 到根节点距离
bool isLeaf[N];
int p[N]; // 父亲节点

int dep[N], fa[N][N];
// dfs(s, 0) 初始化 ; h 要 memset 
void dfs2(int u, int father){
    dep[u] = dep[father] + 1;
    // 向上跳 1, 2, 4, ... 步的祖先节点
    fa[u][0] = father;
    for(int i = 1; i <= 19; i ++)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];

    for(auto v : e[u]){
    	if(v != father){
    		dfs2(v, u);
    	}
    }
    // for(int i = h[u]; i != -1; i = ne[i]){
    //     if(e[i] != father) dfs2(e[i], u);
    // }
}

int Lca(int u, int v){
    if(dep[u] < dep[v]) swap(u, v);
    // 先跳到同一层
    for(int i = 19; i >= 0; i --)
        if(dep[fa[u][i]] >= dep[v]) 
            u = fa[u][i];
    if(u == v) return v;
    // 再跳到 LCA 的下一层
    for(int i = 19; i >= 0; i --)
        if(fa[u][i] != fa[v][i]) 
            u = fa[u][i], v = fa[v][i];
    return fa[u][0]; 
}

// 预处理根节点距离
void dfs(int u, int fa){
	p[u] = fa;
	if(e[u].size() == 1){
		isLeaf[u] = true;
	}
	for(auto &v : e[u]){
		if(v == fa) continue;
		if(d[v] == 0 && v != 1){
			d[v] = d[u] + 1;
			dfs(v, u);
		}
	}
}

// 只要图中有点距离超过 x 就非法
bool check(int x){
	// 存放所有叶子结点 : {到根节点距离, 编号}
	set<pair<int, int> > st;
	for(int i = 1; i <= n; i ++){
		if(isLeaf[i]){
			st.insert({d[i], i});
		}
    }
    // 最多染色 n-2 个点, st 里面永远有 2 个点
    for(int i = 1; i <= k; i ++){
    	// auto e1 = *st.begin(); 
    	auto e2 = *st.rbegin();
    	// auto [d1, id1] = e1;
    	auto [d2, id2] = e2;
    	st.erase(e2);
    	if(p[id2]){
    		st.insert({d[p[id2]], p[id2]});
    		if(wpc) cout << "inserted: " << id2 << '\n';
    	}
    	if(wpc) cout << id2 << '\n'; // 染色的点
    }
    auto e1 = *st.begin(); 
    auto e2 = *st.rbegin();
   	auto [d1, id1] = e1;
   	auto [d2, id2] = e2;
   	if(wpc) cout << id1 << ' ' << id2 << '\n'; // 剩的点
    int mx = max(d2, d1 + d2 - 2 * d[Lca(id1, id2)]);
    return mx <= x;
}

void solve(){
	cin >> n >> k;
	for(int i = 1; i < n; i ++){
		int u, v;
		cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
    }
    d[1] = 0;
    dfs(1, 0);
    dfs2(1, 0);
    for(int i = 1; i <= n; i ++){
    	cout << i << ' ' << p[i] << " \n"[i == n];
    }
    // cout << Lca(2, 4) << '\n';
    // cout << d[1] << ' ' << d[2] << '\n';
    // // cout << check(0) << '\n';
    if(wpc) cout << check(0) << '\n';
    // cout << check(2) << '\n';
    int l = 0, r = 1000;
    while(l < r){
    	int mid = l + r >> 1;
    	if(check(mid)) r = mid;
    	else l = mid + 1;
    }
    cout << l << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
