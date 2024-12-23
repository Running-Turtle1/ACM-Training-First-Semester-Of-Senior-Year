#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
vector<int> e[N];

void solve(){
	int n;
	cin >> n;
	vector<int> a(n + 1);
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		e[i].clear();
    }

    map<int, int> mp;
    int cnt = 0;
    for(int i = 1; i <= n; i ++){
    	if(mp.count(a[i])){
    		e[mp[a[i]]].push_back(i);
    	}
    	else{
    		mp[a[i]] = ++ cnt;
    		e[cnt].push_back(i);
    	}
    }

    // for(int i = 1; i <= cnt; i ++){
    // 	cout << i << ": ";
    // 	for(auto & v : e[i]){
    // 		cout << v << ' ';
    // 	}
    // 	cout << '\n';
    // }


    int q;
    cin >> q;
    while(q --){
    	string s;
    	cin >> s;
    	int m = s.size();
    	s = ' ' + s;
    	bool fg = true;
    	if(n != m){
    		fg = false; 
    	}
    	// 检查 a 位置 s 是否符合 
    	for(int i = 1; i <= cnt; i ++){ 
    		// 所有应该相同的位置
    		for(int j = 0; j < e[i].size(); j ++){
    			int p0 = e[i][0], p = e[i][j];
    			if(s[p0] != s[p]){
    				fg = false; 
    			}
    		} 
	    }
	    vector<vector<int> > tmp(26);
	    for(int i = 1; i <= m; i ++){
	    	tmp[s[i] - 'a'].push_back(i);
	    }
	    for(int i = 0; i < 26; i ++){
	    	for(int j = 0; j < tmp[i].size(); j ++){
	    		int p0 = tmp[i][j], p = tmp[i][0];
	    		if(a[p0] != a[p]){
	    			fg = false; 
	    		}
	    	}
	    }
	    cout << (fg ? "YES" : "NO") << '\n';
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