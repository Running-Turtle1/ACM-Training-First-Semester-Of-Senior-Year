#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;
int n, m, w[N];

#define lc u << 1
#define rc u << 1 | 1

int const INF = 2e18;

struct treeNode{
    int l, r;
    int sum, lmax, rmax, tmax;
}tr[N * 4];

void pushup(treeNode &u, treeNode &l, treeNode &r){
    u.tmax = max({l.rmax + r.lmax, l.tmax, r.tmax});
    u.lmax = max(l.lmax, l.sum + r.lmax);
    u.rmax = max(r.rmax, r.sum + l.rmax);
    u.sum = l.sum + r.sum;
}

void pushup(int u){ 
    pushup(tr[u], tr[lc], tr[rc]); // 重载更新
}

void buildTree(int u, int l, int r){
    tr[u] = {l, r, w[l], w[l], w[l], w[l]};
    if(l == r) return ;
    int mid = l + r >> 1;
    buildTree(lc, l, mid);
    buildTree(rc, mid + 1, r);
    pushup(u);
}

void Modify(int u, int p, int v){
    if(tr[u].l == tr[u].r){ // 查询到叶子结点
        tr[u] = {p, p, v, v, v, v};
        return ;    
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if(p <= mid) Modify(lc, p, v);
    else Modify(rc, p, v);
    pushup(u);
}

// 查询区间最大连续子段和
treeNode AskSegment(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){ // 当前线段被查询区间完全覆盖
        return tr[u];
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if(r <= mid) return AskSegment(lc, l, r);
    else if(l >= mid + 1) return AskSegment(rc, l, r);
    else{
        treeNode lNode = AskSegment(lc, l, r);
        treeNode rNode = AskSegment(rc, l, r);
        treeNode res;
        pushup(res, lNode, rNode); // 合并子节点信息
        return res;
    }
}

void solve( ){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		cin >> w[i];
    } 
    buildTree(1, 1, n); 
    for(int i = 1; i <= m; i ++){
    	int k, a, b;
    	cin >> k >> a >> b;
    	if(k == 1){
    		if(a > b) swap(a, b);
    		cout << AskSegment(1, a, b).tmax << '\n';
    	}
    	else{
    		Modify(1, a, b);
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	solve();

	return 0;
}
