#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
vector<tuple<int, int, int> > edges;
int p[110];
int find(int x){return (x == p[x] ? x : p[x] = find(p[x])); }
void solve(){
	edges.clear();
	for(int i = 1; i <= n; i ++){
		p[i] = i;
    }
	m = n * (n - 1) / 2;
	for(int i = 1; i <= m; i ++){
		int a, b, c;
		cin >> a >> b >> c;
		edges.push_back({c, a, b}); 
	}
	sort(edges.begin(), edges.end());
	int res = 0;
	for(int i = 0; i < m; i ++){
		auto &[w, u, v] = edges[i];
		int pu = find(u), pv = find(v);
		if(pu != pv){
			p[pu] = pv;
			res += w;
		}
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 

	while(cin >> n, n){
		solve();
	}
	return 0;
}