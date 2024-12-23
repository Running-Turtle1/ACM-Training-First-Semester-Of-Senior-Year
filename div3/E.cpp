#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n, p[N], fa[N], sz[N];

int find(int x){
	if(x == fa[x]) return x;
    return fa[x] = find(fa[x]); // 路径压缩
	// return fa[u] == u ? fa[u] : fa[u] = find(fa[u]);
}

void merge(int u, int v){
	int pu = find(u), pv = find(v);
	if(pu != pv){
		sz[pu] += sz[pv];
		fa[pv] = pu;
	}
}

int f[N];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> p[i];
		sz[i] = 1;
		fa[i] = i;
    }
    for(int i = 1; i <= n; i ++){
    	merge(p[i], i);
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	if(find(i) == i){
    		// res += f[sz[i]];
    		if(sz[i] > 2){
    			res += (sz[i] - 2 + 1) / 2;
    		}
    	}
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	f[1] = f[2] = 0;
	for(int i = 3; i < N; i ++){
		f[i] = f[i / 2] + f[i - i / 2] + 1;
	}

	// cout << f[8] << '\n';
	// cout << f[9] << '\n';
	// cout <<f[10]<<'\n';

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}