#include<bits/stdc++.h>
using namespace std;
#define int long long

int const M = 250010;

int s, p;

struct Edge{
	int u, v;
	double w;
	bool operator < (const Edge & T) const {
		return w < T.w;
	}
}edges[M];
int cnt = 0;

pair<int, int> pos[510];

int fa[510];
int find(int x){
	return (x == fa[x] ? x : fa[x] = find(fa[x]));
}

void solve(){
	cnt = 0;
	cin >> s >> p;
	for(int i = 1; i <= p; i ++){
		fa[i] = i;
		cin >> pos[i].first >> pos[i].second;
	}
	if(s == p){
		cout << "0.00\n";
	}
	for(int i = 1; i <= p; i ++){
		for(int j = 1; j <= p; j ++){
			auto &[x1, y1] = pos[i];
			auto &[x2, y2] = pos[j];
			edges[++ cnt] = {i, j, sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2))};
		}
	}
	sort(edges + 1, edges + cnt + 1);
	vector<double> res;
	for(int i = 1; i <= cnt; i ++){
		auto &[u, v, w] = edges[i];
		int pu = find(u), pv = find(v);
		if(pu != pv){
			fa[pu] = pv;
			res.push_back(w);
		}
	}
	// for(int i = 0; i < res.size(); i ++)
	cout << fixed << setprecision(2) << res[res.size() - s] << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 

	int T;
	cin >> T;
	while(T --){
		solve();
	}	
	return 0;
}
