#include<bits/stdc++.h>
using namespace std;
#define int long long
 
void solve(){
	int n, m;
	string tar = "narek";

	cin >> n >> m;
 
	vector<string> s(n + 1);
	for(int i = 1; i <= n; i ++){
		cin >> s[i]; 
    }
 
    // 在 str 中寻找后缀 tmp 的位置 
    auto find1 = [&] (string &str, string &tmp) {
    	int res = str.size();
    	for(int i = tmp.size() - 1; i >= 0; i --){
    		char fd = tmp[i];
    		while(res >= 0 && str[res] != fd) res --;
    	}
    	return res;
    };
 
    // 检查 s[l ~ r] 中有几个 narek
    auto cal = [&] (string &s, int l, int r){
    	if(l > r) return 0LL; 
    	int i = l, res = 0, id = 0;
    	while(i <= r){
    		while(i <= r && s[i] != tar[id]) i ++;
    		if(i == r + 1) break;
    		if(id == 4) id = 0, res ++;
    		else id ++;
    	}
    	return res;
    };
 
    vector<vector<int> > f(n + 1, vector<int> (5, -1e9));
    f[0][0] = 0;
    for(int i = 1; i <= n; i ++){
    	int len = 0; // 特殊字符个数
    	for(int x = 0; x < m; x ++){
    		if(tar.find(s[i][x]) != string::npos) len ++;
		}
 
    	for(int j = 0; j < 5; j ++){
    		// 不选
    		f[i][j] = max(f[i][j], f[i - 1][j]);
    		
    		for(int k = 0; k < 5; k ++){
    			string ns; // 暴力拼接
    			if(!k) ns = s[i];
    			else ns = tar.substr(0, k) + s[i];
 
    			int p; // 掏出来后缀
    			if(j == 0) p = ns.size();
    			else{
    				string ttt = tar.substr(0, j);
    				p = find1(ns, ttt); 
    				if(p == -1) continue ;
    			} 
    			// 算一下得分
    			f[i][j] = max(f[i][j], f[i - 1][k] - len + 2LL * 5 * cal(ns, 0, p - 1)); 
    		}
    	}
    } 
    cout << f[n][0] << '\n';
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