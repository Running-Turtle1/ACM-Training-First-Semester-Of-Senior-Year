#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 40010;
int const M = 40010;

int n, m, k;
struct info{
	int a, b, l;
	char d;
	vector<pair< pair<int, int>, int> > ask;
}infos[M];

int ans[N];

int p[N], dx[N], dy[N];

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	dx[x] += dx[p[x]];
	dy[x] += dy[p[x]];
	return p[x] = t;
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		p[i] = i;
		dx[i] = 0;
		dy[i] = 0;
	}
	for(int i = 1; i <= m; i ++){
		int a, b, c;
		char x;
		cin >> a >> b >> c >> x;
		infos[i] = {a, b, c, x};
	}
	cin >> k;
	for(int i = 1; i <= k; i ++){
		int a, b, I;
		cin >> a >> b >> I;
		infos[I].ask.push_back({ {a, b}, i});
	}
	for(int i = 1; i <= m; i ++){
		auto &[a, b, d, x, vc] = infos[i];
		{
			int pa = find(a), pb = find(b);
			if(pa != pb){
				p[pb] = pa;
				dx[pb] = dx[a] + (x == 'E' ? d : (x == 'W' ? -d : 0)) - dx[b];
				dy[pb] = dy[a] + (x == 'N' ? d : (x == 'S' ? -d : 0)) - dy[b];
			}
		}
		if(vc.size()){
		    for(auto& [pr, id] : vc){
		        auto& [a, b] = pr;
		        int pa = find(a), pb = find(b);
    		    ans[id] = (pa == pb ? abs(dx[b] - dx[a]) + abs(dy[b] - dy[a]) : -1); 
		    }
		}
	}
	for(int i = 1; i <= k; i ++) cout << ans[i] << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
