#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;

vector<int> vc[200010]; // 存储每个数组

pair<int, int> mex(int id){
	auto &vec = vc[id];
	int fs, sz = vec.size();
	unordered_set<int> st;
	for(int i = 0; i < sz; i ++){
		st.insert(vec[i]);
	}
	bool fg = true;
	for(int i = 0; ; i ++){
		if(st.count(i) == false){
			if(fg){
				fg = false;
				fs = i;
			}
			else return {fs, i};
		}
	}
}

vector<int> e[200010];

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		vc[i].clear();
    }
    for(int i = 1; i <= n; i ++){
    	int sz, x;
    	cin >> sz;
    	for(int j = 1; j <= sz; j ++){
    		cin >> x;
    		vc[i].push_back(x);
    	}
    }

    int maxu = -2e9;
    int maxv = -2e9;

    vector<pair<int, int>> edge;

    for(int i = 1; i <= n; i ++){
    	edge.push_back(mex(i));
    	maxu = max(maxu, edge.back().first);
    	maxv = max(maxv, edge.back().second);
    }

    vector<int> out(maxv + 1, 0);
    for(int i = 0; i <= maxv; i ++){
    	e[i].clear();
    }

    for(auto &[u, v] : edge){
    	e[u].push_back(v);
    	out[u] ++;
    }
 	
 	// f[i] : 从 i 最远到哪
 	vector<int> f(maxv + 1, -1);
 	f[maxv] = maxv;

    function<int(int)> dfs = [&] (int u) {
    	if(f[u] != -1) return f[u];
    	int mx = u; // 
    	for(auto &v : e[u]){
    		mx = max(mx, f[v]);
    	}
    	return f[u] = mx;
    };

    for(int i = maxv - 1; i >= 0; i --){
    	dfs(i);
    }

    int mx = -2e9;
    for(int i = 0; i <= maxv; i ++){
    	if(out[i] > 1) mx = max(mx, f[i]);
    }

    for(int i = 0; i <= maxv; i ++){
    	f[i] = max({f[i], maxu, mx});
    }

    int ans = 0;
    if(m > maxv) {
    	ans = (m - maxv) * (m + 1 + maxv) / 2;
    	for(int i = 0; i <= maxv; i ++) ans += f[i];
    }
	else{
		for(int i = 0; i <= m; i ++) ans += f[i];
	}
	cout << ans << '\n';
 
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