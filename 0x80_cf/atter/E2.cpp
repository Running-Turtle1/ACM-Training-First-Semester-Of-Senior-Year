#include<bits/stdc++.h>
using namespace std;
#define int long long

int l, n, m;
int const N = 1510;
int a[N * N], b[N][N];

#define lc u << 1
#define rc u << 1 | 1

int const inf = 9e18;

struct node{
	int l, r;
	int sum, tag;
}tr[N << 2];

void pushup(int u){
	tr[u].sum = tr[lc].sum + tr[rc].sum;
}

void work(int u, int tag){
	tr[u].sum = (tr[u].r - tr[u].l + 1)  * tag;
	tr[u].tag = tag;
}

void pushdown(int u){
	if(tr[u].tag != inf){
		work(lc, tr[u].tag);
		work(rc, tr[u].tag);
		tr[u].tag = inf;
	}
}

void build(int u, int l, int r){
	tr[u] = {l, r, 0, inf};
	if(l == r) return ;
	int mid = l + r >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	pushup(u);
}

void modify(int u, int l, int r, int v){
	if(l <= tr[u].l && r >= tr[u].r){
		work(u, v);
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) modify(lc, l, r, v);
	if(r > mid) modify(rc, l, r, v);
	pushup(u);
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
	return res;
}

map<int, int> pos[N];
// int pos[N][N]; // 每一行每个数最靠右的位置
int has[N]; // 第 i 条轮廓线是否存在可选点
int f[N];

int cnt = 0, t[3000010];

void solve(){
	cnt = 0;
	cin >> l >> n >> m;
	for(int i = 1; i <= l; i ++){
		cin >> a[i];
		has[i] = false;
		t[++ cnt] = a[i];
	}
	for(int i = 1; i <= n; i ++){
		pos[i].clear();
        for(int j = 1; j <= m; j ++){
     		cin >> b[i][j];
     		t[++ cnt] = b[i][j];       
        }
    }

    // 离散化
    sort(t + 1, t + cnt + 1);
    int sz = unique(t + 1, t + cnt + 1) - t - 1;
    for(int i = 1; i <= l; i ++){
    	a[i] = lower_bound(t + 1, t + sz + 1, a[i]) - t;
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		b[i][j] = lower_bound(t + 1, t + sz + 1, b[i][j]) - t;     
        }
    }

    // 每一行每个数最靠右的位置
    for(int i = 1; i <= n; i ++){ // 初始化 pos 数组
        for(int j = 1; j <= l; j ++){
     		pos[i][j] = 0;       
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
    		pos[i][b[i][j]] = j;       
        }
    }

    build(1, 1, n); // 建线段树 : 存枚举每一行时当前轮廓线的最右位置 

    // 处理轮廓线
   	int dg = 0;
    for(int k = 1; k <= l; k ++){ // 第 k 次做出选择
    	bool fg = false; // 是否选出了合法点
    	for(int i = 1; i <= n; i ++){ // 按行处理轮廓线
    		if(pos[i][a[k]] > ask(1, i, i)){
    			if(dg) cout << "seg: " << k << '\n';
    			if(dg) cout << "point: " << i << ' ' << pos[i][a[k]] << '\n';
    			if(dg) cout << "row: " << i << '\n';
    			fg = true; 
    			modify(1, i, i, pos[i][a[k]]);
    			if(i != 1 && pos[i][a[k]] > ask(1, i - 1, i - 1)){
    				int l = 1, r = i - 1;
    				while(l < r){
    					int mid = l + r >> 1;
    					if(ask(1, mid, mid) < pos[i][a[k]]) r = mid;
    					else l = mid + 1;
    				}
    				modify(1, l, i - 1, pos[i][a[k]]);
    			}
    		}
    		else{ // 选不出来点
    			if(i != 1) modify(1, i, i, ask(1, i - 1, i - 1));
    		}
    		if(dg) cout << "segTree:\n";
    		for(int i = 1; dg && i <= n; i ++){
    			cout << ask(1, i, i) << " \n"[i == n];
		    }
    	}
    	if(fg){
    		if(dg) cout << "K: " <<k << '\n';
    		has[k] = true;
    	}

    }
    if(has[l]) f[l] = 1;
    else f[l] = 0;
    for(int i = l - 1; i >= 1; i --){
    	if(has[i] == 0 || f[i + 1] == 1) f[i] = 0;
    	else f[i] = 1;
    }
    cout << (f[1] ? "T" : "N") << '\n';
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