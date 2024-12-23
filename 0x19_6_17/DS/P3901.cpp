#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;
int const M = 2e5 + 10;

int n, q, a[N];

struct Q{
	int l, r, id;
	bool operator < (const Q & T) const {
		return r < T.r;
	}
}query[M];
int ans[M]; // 记录第 i 次询问的答案

void Discretization(int n, int *a){
	vector<int> b(n + 1);
	for(int i = 1; i <= n; i ++){
		b[i] = a[i];
    }
    sort(b.begin() + 1, b.begin() + n + 1);
    int sz = unique(b.begin() + 1, b.begin() + n + 1) - b.begin() - 1;
    for(int i = 1; i <= n; i ++){
    	a[i] = lower_bound(b.begin() + 1, b.begin() + sz + 1, a[i]) - b.begin();
    }
}

int tr[N];
void add(int p, int v){
	for(int i = p; i < N; i += i & -i){
		tr[i] += v;
	}
}
int ask(int p){
	int res = 0;
	for(int i = p; i; i -= i & -i){
		res += tr[i];
	}
	return res;
}
int ask(int l, int r) {return ask(r) - ask(l - 1); }
int pos[N];

void solve(){
	int nowR = 0;
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    Discretization(n, a);
    for(int i = 1; i <= q; i ++){
    	int l, r, id;
    	cin >> l >> r;
    	query[i] = {l, r, i};
    }
    sort(query + 1, query + q + 1);
    for(int i = 1; i <= q; i ++){
    	auto &[l, r, id] = query[i];
    	while(nowR < r){
    		int nepos = nowR + 1;
    		if(pos[a[nepos]] == 0){
    			pos[a[nepos]] = nepos;
    			add(nepos, 1);
    		}
    		else{
    			add(pos[a[nepos]], -1);
    			pos[a[nepos]] = nepos;
    			add(nepos, 1);
    		}
    		nowR ++;
    	}
    	ans[id] = ask(r) - ask(l - 1) == r - l + 1;
    }
    for(int i = 1; i <= q; i ++){
    	cout << (ans[i] ? "Yes" : "No") << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}


