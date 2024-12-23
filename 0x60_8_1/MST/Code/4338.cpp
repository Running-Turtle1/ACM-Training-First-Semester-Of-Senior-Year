#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
vector<tuple<double, int, int> > edges;
vector<pair<int, int> > points;
int p[110];
int find(int x){return (x == p[x] ? x : p[x] = find(p[x])); }
void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		int x, y;
		cin >> x >> y;
		points.push_back({x, y});
		p[i] = i;
	}
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j < i; j ++){
			auto &[x1, y1] = points[i - 1];
			auto &[x2, y2] = points[j - 1];
			double dis = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
			if(dis >= 10.0 && dis <= 1000.0){
				edges.push_back({dis, i, j});
			}
		}
	}
	double sum = 0;
	int cnt = 0;
	for(auto &[w, u, v] : edges){
		int pu = find(u), pv = find(v);
		if(pu != pv){
			p[pu] = pv;
			sum += w;
			cnt ++;
		}
	}
	if(cnt == n - 1){
		cout << fixed << setprecision(1) << sum << '\n';
	}
	else{
		cout << "oh!\n"
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}