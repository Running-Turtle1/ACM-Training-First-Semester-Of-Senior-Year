#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 105;

int n, m, k, ans;

struct Node{
	int x, y, op, a, b, d, v;
	Node() {};
	Node(int x, int y, int op, int a, int b, int d, int v) : 
	x(x), y(y), op(op), a(a), b(b), d(d), v(v) {};
};

int val[N];
Node opt[N];

void dfs(int p) {

	if(p == n + 1) {
		int now = 0ll;
		for(int i=1;i<=m;i++) {
			auto &[x, y, op, a, b, d, v] = opt[i];
			if(op == 0 && a * val[x] + b * val[y] <= d) {
				now += v;
			} else if(op == 1 && a * val[x] + b * val[y] >= d) {
				now += v;
			}
		}
		ans = max(ans, now);
		// for(int i=1;i<=n;i++) {
		// 	cout << val[i] <<" \n"[i==n];
		// }
		return ;
	}

	for(int i=0;i<=k;i++) {
		val[p] = i;
		dfs(p + 1);
	}

}

void solve(){

	cin >> n >> m >> k;

	int x, y, op, a, b, d, v;

	for(int i=1;i<=m;i++) {
		cin >> x >> y >> op >> a >> b >> d >> v;
		opt[i] = Node(x, y, op, a, b, d, v);
	}


	ans = 0ll;
	dfs(1);

	cout << ans << '\n';

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
