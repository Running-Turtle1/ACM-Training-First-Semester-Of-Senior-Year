#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace MCMF
{
    constexpr int N = 2E3 + 10, M = 2E6 + 10, INF = 0x7fffffff;
    int h[N], cnt = 1;
    struct Edge{
        int v, w, c, ne; // 容量 w ; 单位费用 c
    } edges[M << 1];
    inline void add(int u, int v, int w, int c){
        edges[++ cnt] = {v, w, c, h[u]};
        h[u] = cnt;
    }
    inline void addEdge(int u, int v, int w, int c){
        c = -c;
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
        return d[t] != INF && d[t] < 0;
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

int x[35][35];

void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    MCMF::s = 0, MCMF::t = 2 * n * m + 1;
    // 拆点
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            cin >> x[i][j];
            if(x[i][j] == 0) {
                MCMF::addEdge((i - 1) * m + j, (i - 1) * m + j + n * m, 1, -1);
            }   
            else if(x[i][j] == 1){
                MCMF::addEdge((i - 1) * m + j, (i - 1) * m + j + n * m, 1, 0);
            }   
            else if(x[i][j] == -1) {
                
            } 
        }
    }
    for(int i = 1; i <= k; i ++){
        int xx, yy;
        cin >> xx >> yy;
        MCMF::addEdge(MCMF::s, (xx - 1) * m + yy, 1, 100);
    }
    for(int i = 1; i <= k; i ++){
        int xx, yy;
        cin >> xx >> yy;
        MCMF::addEdge((xx - 1) * m + yy + n * m, MCMF::t, 1, 0);
    }
    int dx[] = {1, -1, 0, 0};
    int dy[] = {0, 0, 1, -1};
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            if(x[i][j] == 0 || x[i][j] == 1) {
                for(int d = 0; d < 4; d ++){
                    int nx = i + dx[d], ny = j + dy[d];
                    if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && x[nx][ny] != -1) {
                        MCMF::addEdge((i - 1) * m + j + n * m, (nx - 1) * m + ny, 1e9, 0);
                    }
                }
            }       
        }
    }
    MCMF::run();
    cout << -MCMF::mincost << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
