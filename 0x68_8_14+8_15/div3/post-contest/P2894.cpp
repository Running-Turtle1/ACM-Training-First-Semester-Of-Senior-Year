#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const N = 5e4 + 10;

struct seg{
	int l, r;
	int s, ls, rs; // s 是最大连续点数量 ; ls/rs 是左/右边最大连续点的数量
	int tg; // 懒标记, 0/1 : 改为无/有用点
}tr[N * 4];

seg merge(seg lseg, seg rseg){
	seg res;
	res.l = lseg.l, res.r = rseg.r;
	res.s = max({lseg.s, rseg.s, lseg.rs + rseg.ls});
	if(lseg.ls == lseg.r - lseg.l + 1){
		res.ls = lseg.ls + rseg.ls;
	}
	else{
		res.ls = lseg.ls;
	}
	if(rseg.rs == rseg.r - rseg.l + 1){
		res.rs = rseg.rs + lseg.rs;
	}
	else{
		res.rs = rseg.rs;
	}
	return res;
}

void pushup(int u){
	tr[u] = merge(tr[lc], tr[rc]);
	return ;
	tr[u].s = max({tr[lc].s, tr[rc].s, tr[lc].rs + tr[rc].ls});
	if(tr[lc].ls == tr[lc].r - tr[lc].l + 1){
		tr[u].ls = tr[lc].ls + tr[rc].ls;
	}
	else{
		tr[u].ls = tr[lc].ls;
	}
	if(tr[rc].rs == tr[rc].r - tr[rc].l + 1){
		tr[u].rs = tr[rc].rs + tr[lc].rs;
	}
	else{
		tr[u].rs = tr[rc].rs;
	}
}

void pushdown(int u){
	if(tr[u].tg == 0){
		tr[lc].s = tr[lc].ls = tr[lc].rs = 0;
		tr[rc].s = tr[rc].ls = tr[rc].rs = 0;
		tr[lc].tg = tr[rc].tg = 0;
	}
	if(tr[u].tg == 1){
		tr[lc].s = tr[lc].ls = tr[lc].rs = tr[lc].r - tr[lc].l + 1;
		tr[rc].s = tr[rc].ls = tr[rc].rs = tr[rc].r - tr[rc].l + 1;
		tr[lc].tg = tr[rc].tg = 1;
	}
	tr[u].tg = -1;
}

void buildTree(int u, int l, int r){
	tr[u] = {l, r, 1, 1, 1, -1};
	// tr[u] = {l, r, r - l + 1, r - l + 1, r - l + 1, -1};
	if(l == r) return ;
	int mid = l + r >> 1;
	buildTree(lc, l, mid);
	buildTree(rc, mid + 1, r);
	pushup(u);
}

void segChange(int u, int l, int r, int tp){
	if(l <= tr[u].l && r >= tr[u].r){
		// cout << u << ' ' <<tr[u].l << ' ' << tr[u].r << '\n';
		tr[u].s = tr[u].ls = tr[u].rs = tp * (tr[u].r - tr[u].l + 1);
		tr[u].tg = tp;
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) segChange(lc, l, r, tp);
	if(r > mid){
		// cout << "shit\n";
		segChange(rc, l, r, tp);
	}
	pushup(u);
}

// 查询 [l, r] 的最长连续有用段
seg ask(int u, int l, int r){
	if(l <= tr[u].l && r >= tr[u].r){
		// cout << "ask: " << u << ' ' <<tr[u].l<<' '<<tr[u].r<<'\n';
		return tr[u];
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid && r > mid){
		return merge(ask(lc, l, r), ask(rc, l, r));
	}
	if(l <= mid){
		return ask(lc, l, r);
	}
	if(r > mid){
		return ask(rc, l, r);
	}
	// pushup(u);
	// return *(new seg);
}

// 查询长度为 len 的有用段的最左的左端点
int ask(int u, int len){
	if(tr[u].l == tr[u].r){
		return tr[u].l;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u); 
	if(tr[lc].s >= len) return ask(lc, len);
	else if(tr[lc].rs + tr[rc].ls >= len) return mid - tr[lc].rs + 1;
	return ask(rc, len);
}

void solve(){
	int n, m;
	cin >> n >> m;
	buildTree(1, 1, n);

	// cout<<tr[1].l<< ' '<<tr[1].r<<'\n';
	// cout<<tr[2].l<< ' '<<tr[2].r<<'\n';
	// cout<<tr[3].l<< ' '<<tr[3].r<<'\n';
	// // for(int i = 1; i <= n; i ++){
	// // 	cout << ask(1,i,i).s << " \n"[i == n];
    // // }
    // cout<<"fs: \n";
    // cout<<tr[2].l<<' '<<tr[2].r<<'\n';
    // segChange(1, 1, 3, 0);
    // cout<<"sc: \n";
    // cout<<tr[2].l<<' '<<tr[2].r<<'\n';
    // cout<<ask(1,1,3).s<<'\n';
    // cout<<tr[2].s<<'\n';
    // // for(int i = 1; i <= n; i ++){
	// // 	cout << ask(1,i,i).s << " \n"[i == n];
    // // } 

	// return ;
	// cout << tr[1].l << ' ' << tr[1].r << '\n';
	// cout << tr[1].s << '\n';
	// cout << ask(1, 1, n).s << '\n';
	// return ;
	for(int i = 1; i <= m; i ++){
		int tp, x, y;
		cin >> tp;
		if(tp == 1){
			cin >> x;
			if(tr[1].s < x){
			// if(ask(1, 1, n).s < x){
				cout << "0\n";
			}
			else{
				int p = ask(1, x);
				segChange(1, p, p + x - 1, 0);
				cout << p << '\n';
				// cout<<ask(1,1,n).s<<'\n';
			}
		}
		else{
			cin >> x >> y;
			segChange(1, x, x + y - 1, 1);
		}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
