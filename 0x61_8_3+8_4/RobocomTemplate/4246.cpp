#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

typedef pair<int, int> pii;
priority_queue<pii, vector<pii>, greater<pii> > heap;
int n, m;
vector<pii> e[N][2];
int d[N], st[N];

int dijkstra(int s, int id){
	while(heap.size()) heap.pop();
	for(int i = 1; i <= n; i ++){
		d[i] = 2e18;
		st[i] = 0;
    }
    d[s] = 0;
    heap.push({d[s], s});
    while(heap.size()){
    	auto const [dis, u] = heap.top();
    	heap.pop();
    	if(st[u]) continue ;
    	st[u] = 1;
    	for(auto &[v, w] : e[u][id]){
    		if(d[u] + w < d[v]){
    			d[v] = d[u] + w;
    			heap.push({d[v], v});
    		}
    	}
    }
    // cout << d[1] << ' ' << d[2] << '\n';
    int res = 0;
    for(int i = 2; i <= n; i ++) res += d[i];
    return res;
    return accumulate(d + 2, d + n + 1, 0LL) << '\n';
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		e[i][0].clear();
		e[i][1].clear();
    }
    for(int i = 1;i <= m; i ++){
    	int a, b, c;
    	cin >> a >> b >> c;
    	e[a][0].push_back({b, c});
    	e[b][1].push_back({a, c});
    }
    // cout << dijkstra(1, 0) << '\n';
    cout << dijkstra(1, 0) + dijkstra(1, 1) << '\n';
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
