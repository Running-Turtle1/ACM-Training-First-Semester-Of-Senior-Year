#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const N = 2e5 + 10;

int n, k, q, a[N];

struct treeNode {
    int l, r;
    int lmax, rmax, tmax;
    int first, last;
};

treeNode tr[N * 4];

void pushup(treeNode &u, const treeNode &l, const treeNode &r) {
	u.l = l.l, u.r = r.r;

    u.first = l.first;
    u.last = r.last;
    
    u.lmax = l.lmax;
    if (l.lmax == l.r - l.l + 1 && l.last + 1 == r.first) {
        u.lmax = l.lmax + r.lmax;
    }
    
    u.rmax = r.rmax;
    if (r.rmax == r.r - r.l + 1 && r.first == l.last + 1) {
        u.rmax = r.rmax + l.rmax;
    }
    
    u.tmax = max({l.tmax, r.tmax});
    if (l.last + 1 == r.first) {
        u.tmax = max(u.tmax, l.rmax + r.lmax);
    }
}

void pushup(int u) {
    pushup(tr[u], tr[lc], tr[rc]); // 递归更新父节点
}

void buildTree(int u, int l, int r) {
    if (l == r) {
        tr[u] = {l, r, 1, 1, 1, a[l], a[l]};
        return;
    }
    int mid = (l + r) >> 1;
    buildTree(lc, l, mid);
    buildTree(rc, mid + 1, r);
    pushup(u);
}

treeNode AskSegment(int u, int l, int r) {
    if (l <= tr[u].l && r >= tr[u].r) { // 当前区间被完全覆盖
        return tr[u];
    }
    int mid = (tr[u].l + tr[u].r) >> 1;
    if (r <= mid) return AskSegment(lc, l, r);
    else if (l >= mid + 1) return AskSegment(rc, l, r);
    else {
        treeNode lNode = AskSegment(lc, l, r);
        treeNode rNode = AskSegment(rc, l, r);
        treeNode res;
        pushup(res, lNode, rNode); // 合并结果
        return res;
    }
}

void solve(){
	cin >> n >> k >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    buildTree(1, 1, n);
    // cout << AskSegment(1, 1, 2).tmax << '\n';
    while(q --){
    	int l, r;
    	cin >> l >> r;
    	cout << k - AskSegment(1, l, r).tmax << '\n';
    }
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