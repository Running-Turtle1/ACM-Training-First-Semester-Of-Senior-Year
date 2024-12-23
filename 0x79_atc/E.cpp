#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, a[N];

#define lc u << 1
#define rc u << 1 | 1

// 维护端点, 线段和, 加法懒标记
struct treeNode{
    int l, r, sum, add;
}tr[N * 4];

// 向上更新
void pushup(int u){
    tr[u].sum = tr[lc].sum + tr[rc].sum;
}

// 向下更新
void pushdown(int u){
    if(tr[u].add){
        tr[lc].sum += tr[u].add * (tr[lc].r - tr[lc].l + 1);
        tr[rc].sum += tr[u].add * (tr[rc].r - tr[rc].l + 1);
        tr[lc].add += tr[u].add;
        tr[rc].add += tr[u].add;
        tr[u].add = 0;
    }
}

void buildTree(int u, int l, int r){
    tr[u] = {l, r, 0, 0};
    if(l == r) return ; // 是叶子结点则返回
    int mid = l + r >> 1; // 不是叶子结点就分裂
    buildTree(lc, l, mid);
    buildTree(rc, mid + 1, r);
    pushup(u);
}

// 区间加 (区间减也是区间加)
void segmentAdd(int u, int l, int r, int x){
    if(l <= tr[u].l && r >= tr[u].r){ // 覆盖则修改
        tr[u].sum += (tr[u].r - tr[u].l + 1) * x;
        tr[u].add += x;
        return ;
    }
    int mid = tr[u].l + tr[u].r >> 1; // 不覆盖就分裂
    pushdown(u);
    if(l <= mid) segmentAdd(lc, l, r, x);
    if(r > mid) segmentAdd(rc, l, r, x);
    pushup(u);
} 

// 区间求和
int askSegmentSum(int u, int l, int r){
    if(l <= tr[u].l && r  >= tr[u].r){ // 覆盖则返回
        return tr[u].sum;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    pushdown(u);
    int sum = 0;
    if(l <= mid) sum += askSegmentSum(lc, l, r);
    if(r > mid) sum += askSegmentSum(rc, l, r);
    return sum;
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }		
    buildTree(1, 1, n);
    map<int, int> pos;
    int ans = 0;
    for(int i = n; i >= 1; i --){
    	int p = n + 1;
    	if(pos.count(a[i])) p = pos[a[i]];
    	segmentAdd(1, i, p - 1, 1);
    	pos[a[i]] = i;
    	ans += askSegmentSum(1, i, n);
    	// cout << "change: " << i << ' ' << p - 1 << '\n';
    	// for(int i = 1; i <= n; i ++)
    	// 	cout << askSegmentSum(1, i, i) << " \n"[i == n];
    	// cout << i << ' ' << askSegmentSum(1, i, n) << '\n';
    }
    cout << ans << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
