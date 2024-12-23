#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
char g[110][110];

void solve(){
	set<pair<int,int>> pl, sea;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		cin >> g[i][j];       
     		if(g[i][j] == 'X'){
     			pl.insert({i, j});
     		}
     		if(g[i][j] == 'L'){
     			sea.insert({i, j});
     		}
        }
    }
    int res = 0;
    while(sea.size() && pl.size()){
    	int dis = 1e9;
    	unordered_map<int, vector<int> > mp;
    	// 三元组 : 存 {dis, sea, p}
    	// 找离乘客最近的座位以及距离
    	// 对于 dis = dis_min 的, sea.push(p) ; 不能超过两次
    	vector<pair<int, pair<int, int>> > vc;
    	for(auto &p : pl){ // 枚举所有乘客
    		auto &[px, py] = p;
    		int tmp = 1e9;
    		for(auto &l : sea){
    			auto &[sx, sy] = l;
    			int ds = (px - sx) * (px - sx) + (py - sy) * (py - sy);
    			tmp = min(tmp, ds);
    		}
    		for(auto &l : sea){ // 所有座位
    			auto &[sx, sy] = l;
    			int ds = (px - sx) * (px - sx) + (py - sy) * (py - sy);
    			if(ds == tmp){
    				vc.push_back({ds, {sx * 100000 + sy, px * 100000 + py}});
    			}
    		}
    		dis = min(dis, tmp);
    	}

    	for(auto &e : vc){
    		auto d = e.first;
    		auto &[sa, p] = e.second;
    		// cout << d << ' ' << sa << ' ' << p << '\n';
    		if(d == dis){
    			mp[sa].push_back(p);
    		}
    	}

    	// 模拟一次抢座位
    	for(auto &[sa, v] : mp){
    		if(v.size() >= 2){
    			res ++;
    		}
    		sea.erase({sa / 100000, sa % 100000});
    		for(auto & hm : v){
    			pl.erase({hm / 100000, hm % 100000});
    		}
    	}
    }
    cout << res;
}
// 2 2
// .X
// XL
// 1 200002 100002
signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}