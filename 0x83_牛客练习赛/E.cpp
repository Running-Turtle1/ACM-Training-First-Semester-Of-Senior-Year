#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1
 
int const P = 13331;
int const mod = 1e9 + 7;
int const N = 1e5 + 10;

int p[N];
int invP;

int ksm(int a, int k, int p){
    int res = 1;
    a %= p;
    while(k){
        if(k & 1) res = res * a % p;
        k >>= 1;
        a = a * a % p;
    }
    return res;
}

int inv(int x){
	return ksm(x, mod - 2, mod);
}

struct node{
	int l, r, ln;
	int hash1, hash2, tag;
}tr[N << 2];

int n, m;
string s;

void pushup(node &u, node &lson, node &rson){
	u.l = lson.l, u.r = rson.r;
	u.ln = lson.ln + rson.ln;
	(u.hash1 = lson.hash1 * p[rson.ln] % mod + rson.hash1) %= mod;
	(u.hash2 = rson.hash2 * p[lson.ln] % mod + lson.hash2) %= mod;
}

void pushup(int u){
	pushup(tr[u], tr[lc], tr[rc]);
}

void pushdown(int u, int tag){
	tag %= 26;
	if(tag){
		int tmp = p[tr[u].ln] - 1;
		if(tmp < 0) tmp += mod;
		tmp = tmp * invP % mod;
		tmp = tmp * P % mod;
		tmp = tmp * tag % mod;
		tr[u].hash1 = (tr[u].hash1 + tmp) % mod;
		tr[u].hash2 = (tr[u].hash2 + tmp) % mod;
		(tr[u].tag += tag) %= 26;
	}
}

void pushdown(int u){
	pushdown(lc, tr[u].tag);
	pushdown(rc, tr[u].tag);
	tr[u].tag = 0;
}

void build(int u, int l, int r){
	tr[u] = {l, r, 1, 0, 0, 0};
	if(l == r) return ;
	int mid = l + r >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	pushup(u);
}

int segAdd(int u, int l, int r, int x){
	if(l <= tr[u].l && r >= tr[u].r){
		pushdown(u, x);
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) segAdd(lc, l, r, x);
	if(r < mid) segAdd(rc, l, r, x);
	pushup(u);
}

node ask(int u, int l, int r){
	if(l <= tr[u].l && r >= tr[u].r){
		return tr[u];
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(r <= mid) return ask(lc, l, r);
	else if(l >= mid + 1) return ask(rc, l, r);
	else{
		node lnode = ask(lc, l, r);
		node rnode = ask(rc, l, r);
		node res;
		pushup(res, lnode, rnode);
		return res;
	}
}

void solve(){
	cin >> n >> 
	m >> s;
	s = ' ' + s;
	build(1, 1, n);
	for(int i = 1; i <= n; i ++){
		segAdd(1, i, i, s[i] - 'a');
	}
	while(m --){
		int op, l, r, x;
		cin >> op >> l >> r;
		if(op == 1){
			node res = ask(1, l, r);
			cout << (res.hash1 == res.hash2 ? "YES" : "NO") << '\n'; 
		}	
		else{
			x %= 26;
			segAdd(1, l, r, x);
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	invP = inv(P - 1);

	p[0] = 1;
	for(int i = 1; i < N; i ++){
		p[i] = p[i - 1] * P % mod;
	}

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}