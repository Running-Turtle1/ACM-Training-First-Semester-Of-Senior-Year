#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 110;

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int>> > heap;
vector<pair<int, int> > e[N];
int n;
int d[N], weight[N], vis[N]; // 从起点 s 到其他点的距离 + 点权数组

void dijkstra(int s){
	for(int i = 1; i <= n; i ++) d[i] = 2e18;
	d[s] = weight[s];
	heap.push({d[s], s});
	while(heap.size()){
		auto const [dis, u] = heap.top();
		heap.pop();
		if(vis[u]) continue ;
		vis[u] = 1;
		for(auto &[v, w] : e[u]){
			if(d[u] + weight[v] + w < d[v]){
				d[v] = d[u] + weight[v] + w;
				heap.push({d[v], v});
			}
		}
	}
}

void solve(){	
	cin >> n ;
	for(int i = 2; i <= n; i ++){
		for(int j = 1; j < i; j ++){
			string s;
			cin >> s;
			if(s != "x"){
				int num = stoi(s);
				e[i].push_back({j, num});
				e[j].push_back({i, num});
			}
		}
	}
	dijkstra(1);
	cout << *max_element(d + 2, d + n + 1) << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
