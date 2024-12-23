#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 4e5 + 10;

int n, m, k, p[N];

unordered_set<int> mp;
vector<int> e[N];

int ans[N];
int idx[N];

int find(int x){
	if(x == p[x]) return p[x];
	return p[x] = find(p[x]);
}

void solve(){
	cin >> n >> m;
	for(int i = 0; i < n; i ++){
		p[i] = i;
    }
    for(int i = 0; i < m; i ++){
		int x, y;
		cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
    }
    cin >> k;
    for(int i = 0; i < k; i ++){
    	cin >> idx[i];
    	mp.insert(idx[i]); // 灭亡星球 id
    }

    for(int i = 0; i < n; i ++){
    	if(mp.count(i)) continue; // i 必须活下来
    	for(int j = 0; j < e[i].size(); j ++){
    		int v = e[i][j];
    		if(mp.count(v)) continue; // v 也是
    		p[find(i)] = find(v);
    	}
    }
    ans[k] = 0;
    for(int i = 0; i < n; i ++){
		if(p[i] == i && mp.count(i) == false) ans[k] ++;
    }

    // unordered_set<int> add;
    for(int i = k - 1; i >= 0; i --){
    	int id = idx[i]; // 复活的星球
    //	unordered_set<int> tmp;
    	ans[i] = ans[i + 1] + 1;
    	for(auto &v : e[id]){
    		if(mp.count(v)) continue;
    		int pid = find(id), pv = find(v);
    		if(pid != pv){
    			p[pv] = p[pid];
    			ans[i] --;
    		}	
    //		if(mp.count(v) == false) tmp.insert(v);
    //		p[find(v)] = find(id);
    //		add.insert(find(v));
    	}
    	mp.erase(id);
    //	ans[i] = ans[i + 1] - tmp.size() + 1;
    }
    for(int i = 0; i <= k; i ++){
    	cout << ans[i] << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

// 倒着做，最开始所有星球被摧毁了，算一下连通块数量 res；
// 之后相当于加边，看看边涉及了多少连通块，假设涉及了 x 个，res = res - x + 1