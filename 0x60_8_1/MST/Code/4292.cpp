#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 60;

int n, m;
vector<pair<int, int> > e[N];
int d[N], st[N];

int prim(){
	for(int i = 1; i <= n; i ++){
		d[i] = 2e9;
		st[i] = 0;
	}
	int res = 0;
	d[1] = 0;
	for(int i = 1; i <= n; i ++){
		int t = -1;
		for(int j = 1; j <= n; j ++){
			if(!st[j] && (t == -1 || d[j] < d[t])){
				t = j;
			}
		}
		if(d[t] == 2e9) return -1;
		st[t] = true;
		res += d[t];
		for(auto &[v, w] : e[t]){
			d[v] = min(d[v], w);
		}
	}
	return res;
}

void solve(){
	for(int i = 1; i <= n; i ++){
		e[i].clear();
	}
	for(int i = 1; i <= m; i ++){
		int a, b, w;
		cin >> a >> b >> w;
		e[a].push_back({b, w});
		e[b].push_back({a, w});
	}
	cout << prim() << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	while(cin >> n, n){
		cin >> m;
		solve();
	}

	return 0;
}