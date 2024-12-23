#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;
int const inf = 9e18;

#define lc u << 1
#define rc u << 1 | 1

// 线段树维护两个信息
// s1 表示首项和
// s2 维护公差和, 每个位置 i = i * d
// 所以区间修改的时候, 以 [3, 5] 修改为 1 2 3 为例
// 我们维护的第二项公差是 3 4 5
// 每个位置多维护了 3, 所以首项都要减掉 3, 一般化就是减去 L * d
struct Node{
	int l, r;
	int s1, s2, lz1, lz2;
}tr[N << 2];

void work(int u, int lz1, int lz2){
	if(lz1 != inf){
		tr[u].s1 = (tr[u].r - tr[u].l + 1) * lz1;
		tr[u].lz1 = lz1;
	}
	if(lz2 != inf){
		tr[u].s2 = (tr[u].r - tr[u].l + 1) * (tr[u].l + tr[u].r) / 2 * lz2;
		tr[u].lz2 = lz2;
	}
}

void pushup(int u){
	tr[u].s1 = tr[lc].s1 + tr[rc].s1;
	tr[u].s2 = tr[lc].s2 + tr[rc].s2;
}

void pushdown(int u){
	work(lc, tr[u].lz1, tr[u].lz2);
	work(rc, tr[u].lz1, tr[u].lz2);
	tr[u].lz1 = tr[u].lz2 = inf;
}

// 建一颗空树
void build(int u, int l, int r){
	tr[u] = {l, r, 0, 0, inf, inf};
	if(l == r) return ;
	int mid = l + r >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	pushup(u);
}

// 把 [l, r] 范围修改为首项为 d1, 公差为 d2 的等差数列
// 主要传参 : modify(1, l, r, d1 - l * d2, d2)
void modify(int u, int l, int r, int d1, int d2){
	if(l <= tr[u].l && r >= tr[u].r){
		work(u, d1, d2);
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) modify(lc, l, r, d1, d2);
	if(r > mid) modify(rc, l, r, d1, d2);
	pushup(u);
}

int ask(int u, int l, int r){
	if(l <= tr[u].l && r >= tr[u].r){
		return tr[u].s1 + tr[u].s2;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	int res = 0;
	if(l <= mid) res += ask(lc, l, r);
	if(r > mid) res += ask(rc, l, r);
	return res;
}

void solve(){
	int n;
	cin >> n;
	build(1, 1, n);
	vector<int> x(n + 1);
	for(int i = 1; i <= n; i ++){
		cin >> x[i];
		modify(1, i, i, x[i], 0);
	} 
	int q, ans = 0;
	cin >> q;
	while(q --){
		int t, g;
		cin >> t >> g;
		int xt = ask(1, t, t);
		if(g > xt) {
			int l = t, r = n;
			while(l < r){
				int mid = l + r + 1 >> 1;
				if(ask(1, mid, mid) < g + mid - t) l = mid;
				else r = mid - 1;
			}	
			ans += (l - t + 1) * (2 * g + l - t) / 2 - ask(1, t, l);
			modify(1, t, l, g - t * 1, 1);
			 
		}
		else if(g < xt){
			int l = 1, r = t;
			while(l < r){
				int mid = l + r >> 1;
				if(ask(1, mid, mid) > g - (t - mid)) r = mid;
				else l = mid + 1; 
			}
			ans += ask(1, l, t) - (t - l + 1) * (2 * g + l - t) / 2 ;
			modify(1, l, t, g - t, 1);
		} 
	}
	cout << ans << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}