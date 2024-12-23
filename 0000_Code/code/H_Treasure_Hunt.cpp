#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace MCMF
{
    constexpr int N = 210, M = 2E6 + 10, INF = 0x7fffffff;
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
                if(vol > 0 && d[v] > d[u] + edges[i].c){
                    d[v] = d[u] + edges[i].c;
                    if(!inq[v]){
                        q.push(v);
                        inq[v] = 1;
                    }
                }
            }
        }
        return d[t] != INF && d[t] < 0; // 只增广减少花费的路径
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
    cin >> n >> m;

    MCMF::s = 0, MCMF::t = 2 * n + 1;
    for(int i = 1; i <= n; i ++){ // 拆点
        int x;
        cin >> x;
        MCMF::addEdge(i, n + i, 1e9, -x);
    }
    for(int i = 1; i <= m; i ++){
        int u, v, c;
        cin >> u >> v >> c;
        MCMF::addEdge(n + u, v, c, 0);
    }
    MCMF::addEdge(MCMF::s, 1, 1e9, 0);
    MCMF::addEdge(2 * n, MCMF::t, 1e9, 0);
    MCMF::run();
    cout << -(MCMF::mincost) << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
