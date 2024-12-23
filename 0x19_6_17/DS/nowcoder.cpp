#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;
int const M = N;

int n, q, a[N];
int num[N];

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
void add(int p, int v){ // 将位置 p 异或 v
	for(int i = p; i < N; i += i & -i){
		tr[i] ^= v;
	}
}
int ask(int p){ // 查询 [1, p] 的异或和
	int res = 0;
	for(int i = p; i; i -= i & -i){
		res ^= tr[i];
	}
	return res;
}
int ask(int l, int r) {return ask(r) ^ ask(l - 1);}

int pos[N];
int s[N];
void solve(){
	int nowR = 0;
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		num[i] = a[i];
		tr[i] = 0;
		pos[i] = 0;
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
    			add(nepos, num[nepos]); // 加入
    		}
    		else{
    			int lastPos = pos[a[nepos]];
    			add(lastPos, num[lastPos]); // 异或抵消 
    			pos[a[nepos]] = nepos;
    			add(nepos, num[nepos]); // 加入
    		}
    		nowR ++;
    	}
    	ans[id] = ask(l, r);
    }
    for(int i = 1; i <= n; i ++){
        s[i] = num[i] ^ s[i - 1];
    }
    for(int i = 1; i <= q; i ++){
    	auto &[l, r, id] = query[i];
    	ans[id] = ask(l, r) ^ (s[r] ^ s[l - 1]);
    }
    for(int i = 1; i <= q; i ++){
        cout << ans[i] << '\n';
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

