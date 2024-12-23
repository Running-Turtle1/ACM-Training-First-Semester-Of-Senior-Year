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
	tr[u] = {l, r, a[l], 0};
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

void solve(int fase){
	cout << "Case " << fase << ":\n";
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    buildTree(1, 1, n);
    string s;
    while(cin >> s, s != "End"){
    	if(s[0] == 'Q'){
    		int l, r;
    		cin >> l >> r;
    		cout << askSegmentSum(1, l, r) << '\n';
    	}
    	else if(s[0] == 'A'){
    		int p, x;
    		cin >> p >> x;
    		segmentAdd(1, p, p, x);
    	}
    	else{
    		int p, x;
    		cin >> p >> x;
    		segmentAdd(1, p, p, -x);
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T;
	cin >> T;
	for(int i = 1; i <= T; i ++){
		solve(i);	
	} 
	
	return 0;
}
