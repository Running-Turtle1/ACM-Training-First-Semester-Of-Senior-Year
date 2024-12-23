#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 30;

int n;
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
	for(int i = 1; i < n; i ++){
		char x;
		int k;
		cin >> x >> k;
		for(int j = 1; j <= k; j ++){
			int dis;
			cin >> x >> dis;
			e[i].push_back({x - 'A' + 1, dis});
			e[x - 'A' + 1].push_back({i, dis});
		}
	}
	// for(int i = 1; i <= n; i ++){
	// 	cout << "i: " << i << '\n';
	// 	for(auto &[j, w] : e[i]){
	// 		cout << j << ' ' << w << '\n';
	// 	}
	// }
	cout << prim() << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	while(cin >> n, n){
		solve();
	}

	return 0;
}