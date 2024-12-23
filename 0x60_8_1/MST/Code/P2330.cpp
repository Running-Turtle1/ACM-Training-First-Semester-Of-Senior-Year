#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 310;


int p[N];
int n, m;
vector<tuple<int, int, int> > edges;
int find(int x);

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		p[i] = i;
    }
	for(int i = 1; i <= m; i ++){
		int u, v, w;
		cin >> u >> v >> w;
		edges.push_back({w, u, v});
	}
	sort(edges.begin(), edges.end());
	int ans = -2e9;
	for(auto &[w, u, v] : edges){
		int pu = find(u), pv = find(v);
		if(pu != pv){
			p[pu] = pv;
			ans = max(ans, w);
		}
	}	
	cout << n - 1 << ' ' << ans << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
int find(int x){return (x == p[x] ? x : p[x] = find(p[x])); }