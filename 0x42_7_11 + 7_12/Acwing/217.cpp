#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int const N = 1e5 + 10;
vector<pair<int, int> > e[N];
double f[N];

double dfs(int u){
	if(fabs(f[u] + 1.0) > 1e-6) return f[u];
	f[u] = 0;
	int s = e[u].size();
	for(auto [v, w] : e[u]){
		f[u] += 1.0 / s * (w + dfs(v));
	}
	return f[u];
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= m; i ++){
		int a, b, c;
		cin >> a >> b >> c;
		e[a].push_back({b, c});
		f[i] = -1.0;
    }
    dfs(1);
    cout << fixed << setprecision(10) << f[1] << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
