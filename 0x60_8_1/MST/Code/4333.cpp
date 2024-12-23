#include<bits/stdc++.h>
using namespace std;
#define int long long

int const M = 6e5 + 10;
struct Edge{
	int u, v;
	double w;
	bool operator < (const Edge & T) const {
		return w < T.w;
	}
}edges[M];
int cnt = 0;

pair<int, int> pos[760];

int fa[760];
int find(int x){
	return (x == fa[x] ? x : fa[x] = find(fa[x]));
}
int n, m;

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		fa[i] = i;
		cin >> pos[i].first >> pos[i].second;
    }
    for(int i = 1; i <= n; i ++){
    	for(int j = 1; j < i; j ++){
    		auto &[x1, y1] = pos[i];
    		auto &[x2, y2] = pos[j];
    		edges[++ cnt] = {i, j, sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))};
    	}
    }
    int m;
    cin >> m;
    for(int i = 1; i <= m; i ++){
    	int a, b;
    	cin >> a >> b;
    	a = find(a), b = find(b);
    	fa[a] = b;
    }
    sort(edges + 1, edges + cnt + 1);
    for(int i = 1; i <= cnt; i ++){
    	auto &[u, v, w] = edges[i];
    	int pu = find(u), pv = find(v);
    	if(pu != pv){
    		fa[pu] = pv;
    		cout << u << ' ' << v << '\n';
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 

	int T = 1;
	while(T --){
		solve();
	}	
	return 0;
}
