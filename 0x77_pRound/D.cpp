#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int const mod = 998244353;
int const N = 2e6 + 10;

vector<int> e[N];

int f[N][2];

void dfs(int u, int fa){
    f[u][0] = 1;
    f[u][1] = 1;
    
    for(auto v : e[u]){
        if(v == fa) continue ;
        dfs(v, u);
        (f[u][0] *= (f[v][0] + f[v][1])) %= mod;
        (f[u][1] *= f[v][0]) %= mod;
    }
}

void solve(){
    cin >> n;
    for(int i = 2; i <= n; i ++){
        int p;
        cin >> p;
        e[p].push_back(i);
        e[i].push_back(p);
    }
    dfs(1, 0);
    cout << f[1][0] + f[1][1] << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
