#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, m, a[N];

#define lc u << 1
#define rc u << 1 | 1

// 维护端点, 线段和, 加法懒标记
struct treeNode{
	int l, r;
	int mn, mx;
}tr[N * 4];

// 向上更新
void pushup(int u){
	tr[u].mx = max(tr[lc].mx, tr[rc].mx);
    tr[u].mn = min(tr[lc].mn, tr[rc].mn);
}
 
void buildTree(int u, int l, int r){
	tr[u] = {l, r, a[l], a[l]};
	if(l == r) return ; // 是叶子结点则返回
	int mid = l + r >> 1; // 不是叶子结点就分裂
	buildTree(lc, l, mid);
	buildTree(rc, mid + 1, r);
	pushup(u);
}
 
void Modify(int u, int p, int x){
	if(tr[u].l == tr[u].r){
		tr[u] = {p, p, x, x};
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	if(p <= mid) Modify(lc, p, x);
	else Modify(rc, p, x);
	pushup(u);
} 

int askSegmentMax(int u, int l, int r){
	if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].mx;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    int tmpMax = LLONG_MIN;
    if(l <= mid) tmpMax = max(tmpMax, askSegmentMax(lc, l, r));
    if(r > mid) tmpMax = max(tmpMax, askSegmentMax(rc, l, r));
    return tmpMax;
}

int askSegmentMin(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].mn;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    int tmpMin = LLONG_MAX;
    if(l <= mid) tmpMin = min(tmpMin, askSegmentMin(lc, l, r));
    if(r > mid) tmpMin = min(tmpMin, askSegmentMin(rc, l, r));
    return tmpMin;
}

void solve( ){
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    } 
    buildTree(1, 1, n);
    while(m --){
    	char x;
    	int a, b;
    	cin >> x >> a >> b;
    	if(x == 'Q'){
    		cout << askSegmentMax(1, a, b) << '\n';
    	}
    	else{
    		Modify(1, a, b);
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	while(cin >> n >> m)
	solve();

	return 0;
}
