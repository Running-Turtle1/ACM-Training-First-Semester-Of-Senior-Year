#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, m;
int t0, t1, t2;

vector<tuple<int, int, int> > e[N];

int d[N], st[N];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > heap;

bool check(int mid) {
	for(int i = 1; i <= n; i ++){
		d[i] = 2e18;
		st[i] = 0;
    }
    d[1] = mid;
    heap.push({mid, 1});
    while(heap.size()){
    	auto const [dis, u] = heap.top();
    	heap.pop();

    	if(st[u]) continue ;
    	st[u] = 1;

    	for(auto &[v, w1, w2] : e[u]) {
    		if(t1 >= dis + w1 || t2 <= dis) { // 可以乘坐, 一定坐车
    			if(dis + w1 < d[v]){
    				d[v] = dis + w1;
    				heap.push({d[v], v});
    			}
    		}
    		// int t = min(dis + w2, t2 + w1);
    		// if(t < d[v]){
    		// 	d[v] = t;
    		// 	heap.push({d[v], v});
    		// }
    		if(dis + w2 < d[v]){ // 选择走路
    			d[v] = dis + w2;
    			heap.push({d[v], v});
    		}
    		if(dis <= t2 && t2 + w1 < d[v]){ // 证明里的等待就是这种情况, 等打完电话直接出发就好
    			d[v] = t2 + w1;
    			heap.push({d[v], v});
    		}
    	}
    }
    // cout << d[n] << '\n';
    return d[n] <= t0;
}

void solve(){
	cin >> n >> m >> t0 >> t1 >> t2;
	for(int i = 1; i <= n; i ++){
		e[i].clear();
    }
    for(int i = 1; i <= m; i ++){
    	int u, v, w1, w2;
    	cin >> u >> v >> w1 >> w2;
    	e[u].push_back({v, w1, w2});
    	e[v].push_back({u, w1, w2});
    }
    int l = 0, r = 1e9;
    // 特判无论如何不能到达的情况
    if(check(0) == false) {
    	cout << "-1\n";
    	return ;
    }
    while(l < r){
    	int mid = l + r + 1 >> 1;
    	if(check(mid)) l = mid;
    	else r = mid - 1;
    }
    cout << l << '\n';
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