#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e4 + 10;

int n, m, s;
int v[N], w[N], p[N];

int find(int x){
	return x == p[x] ? x : find(p[x]);
}

int f[N];

int cnt = 0;
pair<int, int> commodity[N];
int to[N];

void solve(){
	cin >> n >> m >> s;
	for(int i = 1; i <= n; i ++){
		cin >> v[i] >> w[i];
		p[i] = i;
    }
    for(int i = 1; i <= m; i ++){
    	int x, y;
    	cin >> x >> y;
    	p[find(x)] = find(y);
    }

    for(int i = 1; i <= n; i ++){
    	if(find(i) == i){
    		to[i] = ++ cnt;
    	}
    }

    for(int i = 1; i <= n; i ++){
    	commodity[to[find(i)]].first += v[i];
    	commodity[to[find(i)]].second += w[i];
    }


    for(int i = 1; i <= cnt; i ++){
    	auto &[fs, sc] = commodity[i];
    	for(int j = s; j >= fs; j --){
    		f[j] = max(f[j], f[j - fs] + sc);
    	}
    }

    cout << f[s] << '\n';
}


// 并查集处理一下物品, 套一下 0-1 背包就可以了

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}