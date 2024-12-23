#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3e5 + 10;
vector<int> e[N];
vector<pair<int, int> > edge;
int n, r, num[N];

void dfs(int u, int fa){
    int las = -1, son = (int)e[u].size() - (u != r);
    int fg = (son & 1);
    for(auto v : e[u]){
        if(v == fa) continue ;
        dfs(v, u);
        if(fg){
            num[u] = num[v];
            fg = 0;
            continue ;
        }
        if(las == -1) las = num[v];
        else edge.push_back({las, num[v]}), las = -1;
    }
} 

void solve(){
    cin >> n;
    edge.clear();
    vector<int> d(n + 1, 0);
    for(int i = 1; i <= n; i ++){
        e[i].clear();
        num[i] = i;
    }
    r = -1;
    for(int i = 1; i < n; i ++){
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
        d[u] ++, d[v] ++;
    }
    for(int i = 1; i <= n; i ++){
        if(d[i] % 2 == 0){
            r = i;
            break;
        }
    }
    if(r == -1) {
        cout << r << '\n';
    }
    else{
        dfs(r, 0);
        cout << edge.size() << '\n';
        for(auto &[x, y] : edge) cout << x << ' ' << y << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}