#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n;
vector<int> e[N];
vector<int> dep[N]; // 深度 i 有多少节点
int s[N]; // 深度 i 多少叶子结点
int d[N];
bool isLeaf[N];

void dfsInit(int u, int fa){
    d[u] = d[fa] + 1;
    dep[d[u]].push_back(u);
    if(e[u].size() == 1 && u != 1){
        isLeaf[u] = true;
    }
    for(int v : e[u]){
        if(v == fa) continue; 
        dfsInit(v, u);
    }
}
int E[N];
int Eofdep[N];
int const mod = 998244353;
int ksm(int a, int k, int p){
    int res = 1;
    a %= p;
    while(k){
        if(k & 1) res = res * a % p;
        k >>= 1;
        a = a * a % p;
    }
    return res;
}
int inv(int x){
    return ksm(x, mod - 2, mod);
}
void solve(){
    cin >> n;
    for(int i = 1; i < n; i ++){
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfsInit(1, 0);
    memset(E, -1, sizeof E);
    for(int i = 1; i <= n; i ++){
        if(isLeaf[i]){
            s[d[i]] ++;
        }
    }
    // cout << Eofdep[2] << '\n';
    memset(Eofdep,-1,sizeof Eofdep);
    for(int i = n; i >= 1; i --){
        if(dep[i].size() == 0) continue;
        if(Eofdep[i + 1] == -1) Eofdep[i] = 0;
        else{
            int sum = dep[i + 1].size();
            int lf = s[i + 1];
            int nlf = sum - lf;
            // if(i==1){
            //     cout<<nlf<<' '<<sum<<'\n';
            // }
            Eofdep[i] = (1 + (nlf)*inv(sum)%mod*Eofdep[i+1]) % mod;
        }
    }
    // cout << 5 * inv(3)%mod<<'\n';
    for(int i = 1; i <= 4;i++)
    cout << Eofdep[i]<<'\n';;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}
