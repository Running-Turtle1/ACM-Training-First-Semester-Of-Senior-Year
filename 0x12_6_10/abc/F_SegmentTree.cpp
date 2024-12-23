#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const N = 2e5 + 10;
struct TreeNode{
	int l, r;
	int sumA, sumB, sumAmulB; // 维护信息
	int addA, addB; // 区间加懒标记
}tr[N * 4];

int a[N], b[N];

// 向上更新
void pushup(int u){
	tr[u].sumA = tr[lc].sumA + tr[rc].sumA;
	tr[u].sumB = tr[lc].sumB + tr[rc].sumB;
	tr[u].sumAmulB = tr[lc].sumAmulB + tr[rc].sumAmulB;
}

// 向下更新
void pushdown(int u){
	if(tr[u].addA || tr[u].addB){
		int llen = tr[lc].r - tr[lc].l + 1;
		tr[lc].sumAmulB += tr[u].addA * tr[u].addB * llen + tr[u].addA * tr[lc].sumB + tr[u].addB * tr[lc].sumA;
		tr[lc].sumA += tr[u].addA * llen;
		tr[lc].sumB += tr[u].addB * llen;

		int rlen = tr[rc].r - tr[rc].l + 1;
		tr[rc].sumAmulB += tr[u].addA * tr[u].addB * rlen + tr[u].addA * tr[rc].sumB + tr[u].addB * tr[rc].sumA;
		tr[rc].sumA += tr[u].addA * rlen;
		tr[rc].sumB += tr[u].addB * rlen;

		tr[u].addA = tr[u].addB = 0;
	}
}

void buildTree(int u, int l, int r){
	tr[u] = {l, r, a[l], b[l], a[l] * b[l], 0, 0};
	if(l == r) return ;
	int mid = l + r >> 1;
	buildTree(lc, l, mid);
	buildTree(rc, mid + 1, r);
	pushup(u);
}

void SegmentAddOfA(int u, int l, int r, int v){
	if(l <= tr[u].l && r >= tr[u].r){
		int len = tr[u].r - tr[u].l + 1;
		tr[u].sumA += len * v;
		tr[u].sumAmulB += v * tr[u].sumB;
		tr[u].addA += v;
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) SegmentAddOfA(lc, l, r, v);
	if(r > mid) SegmentAddOfA(rc, l, r, v);
	pushup(u);
}

void SegmentAddOfB(int u, int l, int r, int v){
	if(l <= tr[u].l && r >= tr[u].r){
		int len = tr[u].r - tr[u].l + 1;
		tr[u].sumB += len * v;
		tr[u].sumAmulB += v * tr[u].sumA;
		tr[u].addB += v;
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) SegmentAddOfB(lc, l, r, v);
	if(r > mid) SegmentAddOfB(rc, l, r, v);
	pushup(u);
}

int AskSegmentSum(int u, int l, int r){
    if(l <= tr[u].l && r  >= tr[u].r){ // 覆盖则返回
        return tr[u].sumAmulB;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    int sum = 0;
    if(l <= mid) sum += AskSegmentSum(lc, l, r);
    if(r > mid) sum += AskSegmentSum(rc, l, r);
    return sum;
}

int n, q;

void solve(){
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    for(int i = 1; i <= n; i ++){
    	cin >> b[i];
    }
    buildTree(1, 1, n); // 建树
    while(q --){
    	int opt, l, r, x;
    	cin >> opt >> l >> r;
    	if(opt == 1){
    		cin >> x;
    		SegmentAddOfA(1, l, r, x);
    	}
    	else if(opt == 2){
    		cin >> x;
    		SegmentAddOfB(1, l, r, x);
    	}
    	else{
    		cout << AskSegmentSum(1, l, r) << '\n';
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}