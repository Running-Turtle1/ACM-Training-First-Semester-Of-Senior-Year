#include<bits/stdc++.h>
using namespace std;
#define int long long

string s;

int const N = 1e5 + 10;

#define lc u << 1
#define rc u << 1 | 1
 
int const P = 13331;
int const mod = 1e9 + 7;

int p[N];

struct node{
	int l, r, ln;
	int hash1[26], hash2[26];
	int tag;
}tr[N << 2];

void pushup(node &u, node &lson, node &rson){
	u.l = lson.l, u.r = rson.r, u.ln = lson.ln + rson.ln;
	for(int i = 0; i < 26; i ++){ 
		u.hash1[i] = (lson.hash1[i] + rson.hash1[i] * p[lson.ln] % mod) % mod;
		u.hash2[i] = (rson.hash2[i] + lson.hash2[i] * p[rson.ln] % mod) % mod;
	}
}

void pushup(int u){
	pushup(tr[u], tr[lc], tr[rc]);
}

void build(int u, int l, int r){
	tr[u].l = l, tr[u].r = r, tr[u].ln = 1, tr[u].tag = 0;
	memset(tr[u].hash1, 0, sizeof tr[u].hash1);
	memset(tr[u].hash2, 0, sizeof tr[u].hash2);
	tr[u].hash1[s[l] - 'a'] = tr[u].hash2[s[l] - 'a'] = p[0]; // can delete later
	if(l == r) return ; 
	int mid = l + r >> 1;
	build(lc, l, mid), build(rc, mid + 1, r);
	pushup(u);
}  

void pushdown(int u, int tag){
	tag %= 26;
	if(tag){
		vector<int> t1(26, 0), t2(26, 0);
		for(int i = 0; i < 26; i ++){
			t1[i] = tr[u].hash1[i];
			t2[i] = tr[u].hash2[i];
		}
		for(int i = 0; i < 26; i ++){ 
			int las = (i + tag) % 26;
			tr[u].hash1[las] = t1[i];
			tr[u].hash2[las] = t2[i];
		}
		tr[u].tag = (tr[u].tag + tag) % 26;
	}
}

void pushdown(int u){
	pushdown(lc, tr[u].tag);
	pushdown(rc, tr[u].tag);
	tr[u].tag = 0;
}

void segMove(int u, int l, int r, int v){
	if(l <= tr[u].l && r >= tr[u].r){
		pushdown(u, v);
		return ;
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(l <= mid) segMove(lc, l, r, v);
	if(r > mid) segMove(rc, l, r, v);
	pushup(u);
}

node askHash(int u, int l, int r){
	if(l <= tr[u].l && r >= tr[u].r){
		return tr[u];
	}
	int mid = tr[u].l + tr[u].r >> 1;
	pushdown(u);
	if(r <= mid) return askHash(lc, l, r);
	else if(l > mid) return askHash(rc, l, r);
	else{
		node res, lres = askHash(lc, l, r), rres = askHash(rc, l, r);
		pushup(res, lres, rres);
		return res;
	}
}

void solve(){
	int n, m;
	cin >> n >> m >> s;
	s = ' ' + s;
	build(1, 1, n);  

	while(m --){
		int op, l, r, v;
		cin >> op >> l >> r;
		if(op == 1){
			node res = askHash(1, l, r);
			int hash1 = 0, hash2 = 0;
			for(int i = 0; i < 26; i ++){
				hash1 = (hash1 + i * res.hash1[i] % mod) % mod;
				hash2 = (hash2 + i * res.hash2[i] % mod) % mod;
			} 
			cout << (hash1 == hash2 ? "YES" : "NO") << '\n';
		}
		else{
			cin >> v;
			segMove(1, l, r, v);
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 

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