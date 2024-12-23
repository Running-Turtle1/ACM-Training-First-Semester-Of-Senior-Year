#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;
int n, m, a[N];

#define lc u << 1
#define rc u << 1 | 1

int const INF = 2e18;

// 维护端点, 线段和, 最大值
// 加法懒标记, 修改懒标记, 是否存在修改懒标记
struct treeNode{
	int l, r, sum, mx;
	int change, update, add; 
}tr[N * 4];

// 向上更新
void pushup(int u){
	tr[u].sum = tr[lc].sum + tr[rc].sum;
	tr[u].mx = max(tr[lc].mx, tr[rc].mx);
}

// 向下更新
void pushdown(int u){
	if(tr[u].update){
		int nval = tr[u].change + tr[u].add;

		tr[lc].sum = nval * (tr[lc].r - tr[lc].l + 1);
		tr[rc].sum = nval * (tr[rc].r - tr[rc].l + 1);

		tr[lc].mx = nval;
		tr[rc].mx = nval;

		tr[lc].change = tr[rc].change = tr[u].change;
		tr[lc].update = tr[rc].update = 1;
		tr[lc].add = tr[rc].add = tr[u].add;

		tr[u].change = tr[u].update = tr[u].add = 0;
	}
	else if(tr[u].add){
		tr[lc].sum += tr[u].add * (tr[lc].r - tr[lc].l + 1);
		tr[rc].sum += tr[u].add * (tr[rc].r - tr[rc].l + 1);

		tr[lc].mx += tr[u].add;
		tr[rc].mx += tr[u].add;

		tr[lc].add += tr[u].add;
		tr[rc].add += tr[u].add;

		tr[u].add = 0;
	}
}

void buildTree(int u, int l, int r){
	tr[u] = {l, r, a[l], a[l], 0, 0, 0};
	if(l == r) return ; // 是叶子结点则返回
	int mid = l + r >> 1; // 不是叶子结点就分裂
	buildTree(lc, l, mid);
	buildTree(rc, mid + 1, r);
	pushup(u);
}

// 区间修改为 x
void segmentChange(int u, int l, int r, int x){
	if(l <= tr[u].l && r >= tr[u].r){
		tr[u].sum = x * (tr[u].r - tr[u].l + 1);
		tr[u].mx = x;
		tr[u].change = x;
		tr[u].update = 1;
		tr[u].add = 0;
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) segmentChange(lc, l, r, x);
	if(r > mid) segmentChange(rc, l, r, x);
	pushup(u);
}

// 区间加 x
void segmentAdd(int u, int l, int r, int x){
	if(l <= tr[u].l && r >= tr[u].r){
		tr[u].sum += x * (tr[u].r - tr[u].l + 1);
		tr[u].mx += x;
		tr[u].add += x;
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) segmentAdd(lc, l, r, x);
	if(r > mid) segmentAdd(rc, l, r, x);
	pushup(u);
}
  
int askSegmentMax(int u, int l, int r){
	if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].mx;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    int tmpMax = LLONG_MIN;
    if(l <= mid) tmpMax = max(tmpMax, askSegmentMax(lc, l, r));
    if(r > mid) tmpMax = max(tmpMax, askSegmentMax(rc, l, r));
    return tmpMax;
}

void solve( ){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    } 
    buildTree(1, 1, n);
    while(m --){
    	int op, l, r, x;
    	cin >> op >> l >> r;
    	if(op != 3) cin >> x;
    	if(op == 1){
    		segmentChange(1, l, r, x);
    	}
    	else if(op == 2){
    		segmentAdd(1, l, r, x);
    	}
    	else{
    		cout << askSegmentMax(1, l, r) << '\n';
    	}
    	// cout << "After: \n";
	    // for(int i = 1; i <= n; i ++){
	    // 	cout << askSegmentMax(1, i, i) << " \n"[i==n];
	    // }
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	solve();

	return 0;
}
