#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int N = 210, M = 1E4 + 10;

struct edge{
    int v, c, ne;
}e[M];

int n, m, S, T;
int h[N], idx = 1; // idx = 1 方便找反向边
int mxf[N], pre[N]; // mxf[v] 从 s ~ v 路径上的流量上限 ; pre[v] 存前驱边

void add(int a, int b, int c) {
    e[++ idx] = {b, c, h[a]}; 
    h[a] = idx; 
}

bool bfs(){ // 找增广路, 最短路思想
    memset(mxf, 0, sizeof mxf);
    mxf[S] = 1e18;
    queue<int> q;
    q.push(S);
    while(q.size()){
        int u = q.front();
        q.pop();
        for(int i = h[u]; i; i = e[i].ne){
            int v = e[i].v;
            if(mxf[v] == 0 && e[i].c){
                mxf[v] = min(mxf[u], e[i].c);
                pre[v] = i;
                q.push(v);
                if(v == T) return true;
            }
        }
    }
    return false;
}

int EK(){ // 累加可行流
    int flow = 0;
    while(bfs()){
        int v = T;
        while(v != S){ // 更新残留网
            int i = pre[v];
            e[i].c -= mxf[T];
            e[i ^ 1].c += mxf[T];
            v = e[i ^ 1].v;
        }
        flow += mxf[T];
    }
    return flow;
}

void solve(){
    cin >> n >> m >> S >> T;
    for(int i = 1; i <= m; i ++){
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w), add(v, u, 0);
    }
    cout << EK() << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
