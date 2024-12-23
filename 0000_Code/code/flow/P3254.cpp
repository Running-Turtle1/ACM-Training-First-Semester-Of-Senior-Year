#include<bits/stdc++.h>
using namespace std;
#define int long long

int m, n, r[200], c[300];

constexpr int N = 1E3 + 10;
constexpr int M = 3E5 + 10;

struct edge{
    int v, c, ne;
}e[M];

int h[N], cur[N], d[N];
int idx = 1;

void add(int a, int b, int c){
    e[++ idx] = {b, c, h[a]};
    h[a] = idx;
}

int S, T;

bool bfs(){
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

int dfs(int u, int rf){
    if(u == T) return rf;
    int sum = 0; 
    for(int i = cur[u]; i; i = e[i].ne){
        cur[u] = i;
        int v = e[i].v;
        if(d[v] == d[u] + 1 && e[i].c){
            int f = dfs(v, min(e[i].c, rf));
            e[i].c -= f, e[i ^ 1].c += f;
            sum += f, rf -= f;
            if(!rf) break; // 残量优化
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

void solve(){
    int sr = 0;
    cin >> m >> n;

    S = 0, T = n + m + 1;

    for(int i = 1; i <= m; i ++){
        cin >> r[i];
        sr += r[i];
    }
    for(int i = 1; i <= n; i ++){
        cin >> c[i];
    }
    for(int i = 1; i <= m; i ++){
        add(0, i, r[i]);
        add(i, 0, 0);
    }
    for(int i = 1; i <= n; i ++){
        add(m + i, T, c[i]);
        add(T, m + i, 0);
    }
    for(int i = 1; i <= m; i ++){
        for(int j = 1; j <= n; j ++){
            add(i, j + m, 1);
            add(j + m, i, 0);
        }
    }

    vector<vector<int> > res(m + 1);
    if(dinic() == sr){
        cout << "1\n";
        for(int i = 2; i <= idx; i ++){
            if(e[i].v > m && e[i].v <= n + m && e[i ^ 1].v >= 1 && e[i ^ 1].v <= m && e[i].c == 0){
                res[e[i ^ 1].v].push_back(e[i].v - m);
            }
        }
        for(int i = 1; i <= m; i ++){
            for(auto &nx : res[i]){
                cout << nx << ' ';
            }
            cout << '\n';
        }
    }
    else{
        cout << "0\n";
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
 
