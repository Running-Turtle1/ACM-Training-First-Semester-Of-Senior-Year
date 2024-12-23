#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, q;
long long V;
// vector<pair<int, int>> e[100010];
// vector<pair<int, long long>> e[100010];
vector<int> e[100010];
vector<long long> ed[100010];
int query[500010][2];
int ans[500010], bel[100010];

void bfs(int s, long long t){
	queue<int> q;
	q.push(s);
	bel[s] = s;
	while(q.size()){
		auto id = q.front();
		q.pop();
		for(int i = 0; i < e[id].size(); i ++){
			// int v = e[id][i].first;
			// long long w = e[id][i].second;
			int v = e[id][i];
			long long w = ed[id][i];
			if(bel[v] || (w & t) != t) continue;
			q.push(v);
			bel[v] = s;
		}
		// for(auto &x : e[id]){
		// 	int v = x.first;
		// 	long long w = x.second;
		// 	if(bel[v] || (w & t) != t) continue;
		// 	q.push(v);
		// 	bel[v] = s;
		// }
	}
}

void sol(long long t){
	memset(bel, 0, sizeof(int) * (n + 3));
	for(int i = 1; i <= n; i ++){
		if(!bel[i]) bfs(i, t);
	}
	for(int i = 1; i <= q; i ++){
		if(bel[query[i][0]] == bel[query[i][1]]){
			ans[i] = 1;
		}
	}
}

void solve(){
	// scanf("%d%d%d%lld", &n, &m, &q, &V);
	cin >> n >> m >> q >> V;
	for(int i = 1; i <= m; i ++){
		int u, v;
		long long w;
		cin >> u >> v >> w;
		// scanf("%d%d%lld", &u, &v, &w);
		// e[u].push_back({v, w});
		// e[v].push_back({u, w});
		e[u].push_back(v); e[v].push_back(u);
		ed[u].push_back(w); ed[v].push_back(w);
	}
	for(int i = 1; i <= q; i ++){
		cin >> query[i][0] >> query[i][1];
		// scanf("%d%d", &query[i][0], &query[i][1]);
	}
	if(V == 0) sol(V);
	else{
		for(long long i = V; i < (1LL << 60); i += i & -i){
			sol(i);
		}
	}
	for(int i = 1; i <= q; i ++){
		cout << (ans[i] ? "Yes" : "No") << '\n';
		// if(ans[i]){
		// 	printf("Yes\n");
		// 	// puts("Yes");
		// }
		// else{
		// 	printf("No\n");
		// 	// puts("No");
		// }
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}