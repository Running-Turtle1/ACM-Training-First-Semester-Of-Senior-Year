#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, k, vc[7];

struct judge{
	int x, y, op, a, b, d, v;
	judge() {

	}
	judge(int x, int y, int op, int a, int b, int d, int v) :
		x(x), y(y), op(op), a(a), b(b), d(d), v(v) {

		}
}J[110];

int mx = 0;

void dfs(int u){
	if(u == n + 1){
		int s = 0;
		for(int i = 1; i <= m; i ++){
			auto [x, y, op, a, b, d, v] = J[i];
			if(op == 0){
				if(a * vc[x] + b * vc[y] <= d) s += v;
			}
			else{
				if(a * vc[x] + b * vc[y] >= d) s += v;
			}
		}
		mx = max(mx, s);
		return ;
	}
	for(int i = 0; i <= k; i ++){
		vc[u] = i;
		dfs(u + 1);
	}
}

void solve(){
	cin >> n >> m >> k;
	for(int i = 1; i <= m; i ++){
		int x, y, op, a, b, d, v;
		cin >> x >> y >> op >> a >> b >> d >> v;
		J[i] = judge(x, y, op, a, b, d, v);
    }
    dfs(1);
    cout << mx;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
