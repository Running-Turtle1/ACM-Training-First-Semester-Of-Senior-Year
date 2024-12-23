#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, q, v;
vector<int> e[100010], eg[100010];
int ans[500010], query[500010][2];
int bel[100010];

void bfs(int s, int t){
	queue<int> q;
	bel[s] = s;
	q.push(s);
	while(q.size()){
		auto u = q.front(); q.pop();
		for(int i = 0; i < e[u].size(); i ++){
			int v = e[u][i], w = eg[u][i];
			if(bel[v] || (w & t) != t) continue;
			bel[v] = s;
			q.push(v);
		}
	}
}

void sol(int t){
	memset(bel, 0, sizeof(int) * (n + 1));
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
	cin >> n >> m >> q >> v;
	for(int i = 1; i <= m; i ++){
		int u, v, w;
		cin >> u >> v >> w;
		e[u].push_back(v);
		e[v].push_back(u);
		eg[u].push_back(w);
		eg[v].push_back(w);
    }
    for(int i = 1; i <= q; i ++){
    	cin >> query[i][0] >> query[i][1];
    }
    if(v == 0) sol(v);
    else{
    	for(int i = v; i < (1LL << 60); i += i & -i){
    		sol(i);
    	}
    }
    for(int i = 1; i <= q; i ++){
    	cout << (ans[i] ? "Yes" : "No") << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}