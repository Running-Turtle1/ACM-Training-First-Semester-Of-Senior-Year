#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const N = 2e6 + 10;

struct seg{
	int l, r;
	int s, ls, rs; // s 是最大连续点数量 ; ls/rs 是左/右边最大连续点的数量
	int tg; // 懒标记, 0/1 : 改为无/有用点
}tr[N * 4];
 
void pushup(int u){ 
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
		tr[u].s = tr[u].ls = tr[u].rs = tp * (tr[u].r - tr[u].l + 1);
		tr[u].tg = tp;
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) segChange(lc, l, r, tp);
	if(r > mid) segChange(rc, l, r, tp);
	pushup(u);
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
	segChange(1, 1, 2000000, 1); // [1, 2e6] 可以使用

	set<int> st;

	int n, m, x;
	cin >> n;
	
	for(int i = 1; i <= n; i ++){
		cin >> x;
		st.insert(x);
		segChange(1, x, x, 0);
    }

	cin >> m;
	for(int i = 1; i <= m; i ++){
		char opt;
		cin >> opt >> x;
		switch(opt) {
			case '+' : {
				segChange(1, x, x, 0);
				st.insert(x);
				break;
			}
			case '-' : {
				segChange(1, x, x, 1);
				st.erase(x);
				break;
			}
			case '?' : {
				if(tr[1].s < x){
					cout << (st.size() ? *st.rbegin() + 1 : 1) << ' '; // 正常找不到答案, 实际就是最后一个出现的数字 + 1
				}
				else{
					cout << ask(1, x) << ' ';
				}
				break;
			}
		}
    }
    cout << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 

	buildTree(1, 1, 2000000); // 构建线段树, [1, 2000000] 个有用点

	int T;
	cin >> T;
	while(T --){
		solve();
	}
	return 0;
}
