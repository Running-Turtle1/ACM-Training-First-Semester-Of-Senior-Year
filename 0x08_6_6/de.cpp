#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii; // {距离, 编号} 
priority_queue<pii, vector<pii>, greater<pii> > heap;

int n, m;
int const N = 2e5 + 10, M = 2e5 + 10;
int h[N], w[M], e[M], ne[M], idx;
bool st[N];
int d[N];

void add(int a, int b, int c){
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

void dijkstra(int s){
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    heap.push({0, s});
    while(heap.size()){
        auto &[dis, u] = heap.top(); 
        heap.pop();
        if(st[u]) continue;
        st[u] = true;
        for(int i = h[u]; ~i; i = ne[i]){
            int v = e[i];
            if(d[u] + w[i] < d[v]){
                d[v] = d[u] + w[i];
                heap.push({d[v], v});
            }
        }
    }
}

int main(){
    memset(h, -1, sizeof h);
    cin>>n>>m;
    for(int i=1; i<=m; i++){
        int a, b, c;
        cin>>a>>b>>c;
        add(a, b, c);
    }
    dijkstra(1);
    cout<<(d[n]==0x3f3f3f3f ? -1 : d[n]) << '\n';
	
	return 0;
} 