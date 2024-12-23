#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int N = 110, M = 5210;

int m, n, S, T;

struct edge{
    int v, c, ne;
}e[M];

int d[N], cur[N], h[N];

int idx = 1;

void add(int a, int b, int c){
    e[++ idx] = {b, c, h[a]};
    h[a] = idx;
}

bool bfs(){ // 对点分层, 寻找增广路
    memset(d, 0, sizeof d);
    queue<int> q;
    q.push(S);
    d[S] = 1;
    while(q.size()){
        auto u = q.front();
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

int dfs(int u, int rf){
    if(u == T) return rf;
    int sum = 0;
    for(int i = cur[u]; i; i = e[i].ne){
        int v = e[i].v;
        cur[u] = i;
        if(d[v] == d[u] + 1 && e[i].c){
            int f = dfs(v, min(e[i].c, rf));
            e[i].c -= f, e[i ^ 1].c += f;
            sum += f, rf -= f;
            if(!rf) break;
        }
    }
    if(sum == 0) d[u] = 0;
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

void solve(){
    cin >> m >> n;

    S = 0, T = n + 1;
    for(int i = 1; i <= m; i ++){
        add(S, i, 1);
        add(i, S, 0);
    }
    for(int i = m + 1; i <= n; i ++){
        add(i, T, 1);
        add(T, i, 0);
    }
    
    int u, v;
    while(cin >> u >> v, u != -1){
        add(u, v, 1);
        add(v, u, 0);
    }

    cout << dinic() << '\n';
    for(int i = 2; i <= idx; i ++){
        if((e[i].v > m && e[i].v <= n) && (e[i ^ 1].v >= 1 && e[i ^ 1].v <= m) && !e[i].c){
            cout << e[i ^ 1].v << ' ' << e[i].v << '\n';
        }
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
