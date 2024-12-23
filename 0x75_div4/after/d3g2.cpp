#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const N = 2e5 + 10;
int const inf = 2e9;

struct node{
	int l, r;
	int sum;
	int tag;
}tr[N << 2];

int n, k, q, a[N], ans[N];

void pushup(int u){
	tr[u].sum = tr[lc].sum + tr[rc].sum;
}

void pushdown(int u){
	if(tr[u].tag != -1){
		tr[lc].sum = (tr[lc].r - tr[lc].l + 1) * tr[u].tag;
		tr[rc].sum = (tr[rc].r - tr[rc].l + 1) * tr[u].tag;
		tr[lc].tag = tr[rc].tag = tr[u].tag;
		tr[u].tag = -1;
	}
}

void build(int u, int l, int r){
	tr[u] = {l, r, inf, -1};
	if(l == r) return ;
	int mid = l + r >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
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

void change(int u, int l, int r, int v){
	if(l <= tr[u].l && r >= tr[u].r){
		tr[u].sum = (tr[u].r - tr[u].l + 1) * v;
		tr[u].tag = v;
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) change(lc, l, r, v);
	if(r > mid) change(rc, l, r, v);
	pushup(u);
}

void solve(){
	map<int, int> cnt;
	multiset<int> st;
	cin >> n >> k >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		cnt[i] = 0;
    }
    for(int i = 1; i <= n; i ++){
    	a[i] -= (i - 1);
    }
    st.insert(0); //
    auto add = [&] (int x) -> void {
    	if(cnt[x]) st.erase(st.find(cnt[x]));
    	cnt[x] ++;
    	st.insert(cnt[x]);
    };
    auto del = [&] (int x) -> void {
    	st.erase(st.find(cnt[x]));
    	cnt[x] --;
    	st.insert(cnt[x]);
    };
    for(int i = 1; i <= k; i ++){
    	add(a[i]);
    }
    ans[1] = k - (*st.rbegin());
    for(int i = k + 1; i <= n; i ++){
    	int l = i - k + 1;
    	del(a[l - 1]);
    	add(a[i]);
    	ans[l] = k - (*st.rbegin());
    }

    // 构建线段树
    build(1, 1, n);

    vector<array<int, 3> > query(q + 1);
    vector<int> queryAnswer(q + 1);

    for(int i = 1; i <= q; i ++) {
    	int l, r;
    	cin >> l >> r;
    	query[i] = {l, r, i};
    }
    sort(query.begin() + 1, query.begin() + q + 1, [&] (auto &a, auto &b){
    	return a[0] > b[0]; // 按照 l 从大到小排序
    });

    // 预处理
    int now = n - k + 1;
    change(1, now, now, ans[now]);

    for(int i = 1; i <= q; i ++){
    	auto &[l, r, id] = query[i];
    	r = r - k + 1;
    	while(now > l){ 
    		now --;
	    	change(1, now, now, ans[now]);
	    	if(now != n - k + 1 && ans[now] < ask(1, now + 1, now + 1)){
	    		int lidx = now + 1, ridx = n - k + 1;
	    		while(lidx < ridx){
	    			int mid = 1 + lidx + ridx >> 1;
	    			if(ask(1, mid, mid) >= ans[now]) lidx = mid;
	    			else ridx = mid - 1;
	    		}
	    		change(1, now + 1, lidx, ans[now]);
	    	}
    	}
    	queryAnswer[id] = ask(1, l, r);
    }
    for(int i = 1; i <= q; i ++){
    	cout << queryAnswer[i] << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T;
	cin >> T;
	while(T --){
		solve();
	}

	return 0;
}