#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace MCMF
{
    constexpr int N = ___, M = 2E6 + 10, INF = 0x7fffffff;
    int h[N], cnt = 1;
    struct Edge{
        int v, w, c, ne; // 容量 w ; 单位费用 c
    } edges[M << 1];
    inline void add(int u, int v, int w, int c){
        edges[++ cnt] = {v, w, c, h[u]};
        h[u] = cnt;
    }
    inline void addEdge(int u, int v, int w, int c){
        add(u, v, w, c);
        add(v, u, 0, -c);
    }
    int s, t, d[N], cur[N]; // dinic 实现
    bool inq[N], vis[N];
    queue<int> q;
    bool spfa(){
        while(q.size()) q.pop();
        copy(h, h + N, cur);
        fill(d, d + N, INF);
        d[s] = 0;
        q.push(s);
        while(q.size()){
            int u = q.front();
            q.pop();
            inq[u] = 0;
            for(int i = h[u]; i; i = edges[i].ne){
                int v = edges[i].v, vol = edges[i].w;
                if(vol > 0 && d[v] > d[u] + edges[i].c && d[v] < 0){ // 只增广可以减少花费的路径
                    d[v] = d[u] + edges[i].c;
                    if(!inq[v]){
                        q.push(v);
                        inq[v] = 1;
                    }
                }
            }
        }
        return d[t] != INF;
    }
    int dfs(int u = s, int flow = INF){
        if(u == t) return flow;
        vis[u] = 1;
        int rmn = flow;
        for(int i = cur[u]; i && rmn; i = edges[i].ne){
            cur[u] = i;
            int v = edges[i].v, vol = edges[i].w;
            if(vol > 0 && !vis[v] && d[v] == d[u] + edges[i].c){
                int r = dfs(v, min(vol, rmn));
                rmn -= r;
                edges[i].w -= r, edges[i ^ 1].w += r;
            }
        }
        vis[u] = 0;
        return flow - rmn;
    }
    int maxflow = 0, mincost = 0;
    inline void run(){
        while(spfa()){
            int flow = dfs();
            maxflow += flow;
            mincost += d[t] * flow;
        }
    }
} 
/*
    namespace MCMF
    set N, M , N 越小跑得越快, M 尽量大点, 防止出错
    w 代表容量, c 代表单位流量费用
*/

void solve(){
    int n, m;
    cin >> n >> m >> MCMF::s >> MCMF::t;
    for(int i = 1; i <= m; i ++){
        int u, v, w, c; // w : 容量 ; c 单位流量花费
        cin >> u >> v >> w >> c;
        MCMF::addEdge(u, v, w, c);
    }
    MCMF::run();
    cout << MCMF::maxflow << ' ' << MCMF::mincost << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
