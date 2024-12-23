#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int mod = 1E9 + 7, N = 2E6 + 10;

int fact[N], infact[N];

int ksm(int a, int k){
	int res = 1;
	while(k){
		if(k & 1) res = res * a % mod;
		k >>= 1;
		a = a * a % mod;
	}
	return res;
}

vector<int> e[N];
int a[N], b[N], w[N], st[N], p[N], len[N];
set<int> ts;
vector<int> t;

void dfs(int u){
	ts.insert(a[u]);
	t.push_back(u);
	st[u] = 1;
	for(auto v : e[u]){
		if(!st[v]){
			dfs(v);
		}
	}
}
int ss = 0;
pair<int, int> ask(int x){
	if(p[x] != -1) return {p[x], len[x]};
	// if(st[x]) {
	// 	p[x] = 0;
	// 	return {p[x], 0};
	// }
	// st[x] = 1;
	
	pair<int, int> pr = ask(b[x]);
	if(p[b[x]] == 0){
		p[x] = 0;
	}
	else{
		len[x] = pr.second + 1;
		p[x] = infact[len[x]];
	}
	++ ss;
	if(ss == 1e7){
		vector<int> mle(1e9, 0);
		fill(mle.begin(), mle.end(), 10);
	}
	return {p[x], len[x]};
} 
 
void solve(){
	ss = 0;
	int n;
	cin >> n;
	
	for(int i = 1; i <= n; i ++){
		e[i].clear();
		st[i] = 0;
		p[i] = -1;
		len[i] = 0;
		ts.clear();
		t.clear();
	}
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
	}
	for(int i = 1; i <= n; i ++){
		 cin >> b[i];
	}
	for(int i = 1; i <= n; i ++) {
		cin >> w[i];
	}
	for(int i = 1; i <= n; i ++){
		e[i].push_back(b[i]);
	}
	for(int i = 1; i <= n; i ++){
		if(!st[i]){
			dfs(i);
			if((int)ts.size() == 1){
				for(auto &id : t) {
					p[id] = 0; 
					len[id] = 1;
				}
			}
			ts.clear();
			t.clear();
		}
	}
	for(int i = 1; i <= n; i ++){
		if(a[i] < a[b[i]]){
			p[i] = 1;
			len[i] = 1;
		}
		if(a[i] >= a[b[i]] + w[b[i]]){
			 p[i] = 0;
			 len[i] = 1;
		}
	}
	
	for(int i = 1; i <= n; i ++){
		ask(i);
		cout << (a[i] + p[i] * w[i] % mod) % mod << ' ';
	}
	cout << '\n'; 	 
}

signed main() {
	
	ios::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);

	fact[0] = 1;
	for(int i = 1; i < N; i ++){
		fact[i] = fact[i - 1] * i % mod;
	}
	infact[N - 1] = ksm(fact[N - 1], mod - 2);
	for(int i = N - 2; i >= 0; i --){
		infact[i] = infact[i + 1] * (i + 1) % mod;
	}
 
	int T;
	cin >> T;
	while(T --){
		solve();
	}
	
	return 0;
}