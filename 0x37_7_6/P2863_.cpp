#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int const N = 2e5 + 10;
vector<int> e[N];
int dfn[N], low[N], tot;
int stk[N], instk[N], top; // 栈 以及 是否在栈中
int scc[N], siz[N], cnt; // cnt 表示强连通分量的个数

void tarjan(int x){
    dfn[x] = low[x] = ++ tot;
    stk[++ top] = x, instk[x] = 1;
    for(auto y : e[x]){
        if(!dfn[y]){
            tarjan(y);
            low[x] = min(low[x], low[y]);
        }
        else if(instk[y]){
            low[x] = min(low[x], dfn[y]);
        }
    }
    if(dfn[x] == low[x]){ // x 是根节点
        int y;
        cnt ++;
        do{
            y = stk[top --];
            instk[y] = 0;
            scc[y] = cnt; // scc 编号
            siz[cnt] ++; // scc 大小
        }
        while(y != x);
    }
}
void tarjan(){
    for(int i = 1; i <= n; i ++){
        if(!dfn[i]){
            tarjan(i);
        }
    }
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= m; i ++){
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
    }
    tarjan();
    int res = 0;
    for(int i = 1; i <= cnt; i ++){
        res += (siz[i] > 1);
    }
    cout << res;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
