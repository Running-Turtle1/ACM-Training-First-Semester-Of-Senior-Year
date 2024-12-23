constexpr int N = 210, M = 1E4 + 10;

struct edge{
    int v, c, ne;
}e[M];

int S, T;
int h[N], idx = 1; // idx = 1 方便找反向边
int d[N], cur[N];

void add(int a, int b, int c) {
    e[++ idx] = {b, c, h[a]}; 
    h[a] = idx; 
}

bool bfs(){ // 对点分层
    memset(d, 0, sizeof d);
    queue<int> q;
    q.push(S);
    d[S] = 1;
    while(q.size()){
        int u = q.front();
        q.pop();
        for(int i = h[u]; i; i = e[i].ne){
            int v = e[i].v;
            if(d[v] == 0 && e[i].c){
                d[v] = d[u] + 1;
                q.push(v);
                if(v == T) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int rf){ // 从 u 点出发, 有 rf 流量, 留到终点最大流
    if(u == T) return rf;
    int sum = 0; // 最大流
    for(int i = cur[u]; i; i = e[i].ne){
        cur[u] = i; // 当前弧优化
        int v = e[i].v;
        if(d[v] == d[u] + 1 && e[i].c){
            int f = dfs(v, min(e[i].c, rf));
            e[i].c -= f;
            e[i ^ 1].c += f;
            sum += f;
            rf -= f;
            if(!rf) break; // 剩余流量优化
        }
    }
    if(sum == 0) d[u] = 0; // 残枝优化
    return sum;
}

int dinic(){
    int flow = 0;
    while(bfs()){
        memcpy(cur, h, sizeof h);
        flow += dfs(S, 1e18);
    }
    return flow;
}
/*
    set N, M
    initialize S, T ;
    for (u, v, w), add(u, v, w), add(v, u, 0)
*/  