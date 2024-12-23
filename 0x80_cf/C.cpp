#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n, m;
	cin >> n >> m;

	vector<string> s(n + 1);
	for(int i = 1; i <= n; i ++){
		cin >> s[i];
		s[i] = ' ' + s[i];
    }

    string ned = "narek";

    // 在 s[id] 中寻找后缀 tmp 的位置
    auto find = [&] (int id, string &tmp) {
    	int res = m;
    	for(int i = tmp.size() - 1; i >= 0; i --){
    		char fd = tmp[i];
    		while(res >= 1 && s[id][res] != fd) res --;
    	}
    	return res;
    };

    // // 在 s[id] 中寻找前缀 tmp 的位置
    auto find2 = [&] (int id, string &tmp){
    	int res = 1;
    	for(char fd : tmp){
    		while(res <= m && s[id][res] != fd) res ++;
    	}
    	return res;
    };

    // 检查 s[l ~ r] 中有几个 narek
    auto cal = [&] (string &s, int l, int r){
    	if(l > r) return 0LL; 
    	int i = l;
    	int res = 0;
    	int id = 0;
    	while(i <= r){
    		while(i <= r && s[i] != ned[id]) i ++;
    		if(i == r + 1) break;
    		if(id == 4){
    			id = 0;
    			res ++;
    		}
    		else{
    			id ++;
    		}
    	}
    	return res;
    };

    vector<vector<int> > f(n + 1, vector<int> (5, -1e9));
    f[0][0] = 0;
    for(int i = 1; i <= n; i ++){
    	int len = 0; // 特殊字符个数
    	for(int x = 1; x <= m; x ++){
			if(s[i][x] == 'n' || s[i][x] == 'a' || s[i][x] == 'r' || s[i][x] == 'e' || s[i][x] == 'k'){
				len ++;
			}
		}

    	for(int j = 0; j < 5; j ++){
    		// 不选
    		f[i][j] = max(f[i][j], f[i - 1][j]);
    		
    		// 选这一维 : [1, p] 可用
    		int p; 
    		if(j == 0){
    			p = m;
    		}
    		else{
    			string tmp = ned.substr(0, j);
    			int p = find(i, tmp);
    			if(p == 0) continue ;
    			-- p;
    		}

    		// k = 0
    		// cout << "p: " << p << '\n';
    		f[i][j] = max(f[i][j], f[i - 1][0] - len + 2LL * 5 * cal(s[i], 1, p)); 

    		for(int k = 1; k < 5; k ++){
    			
    			// 从 s[i] 的 [1, p - 1] 中寻找位置衔接
    			string fs = ned.substr(k); // 先找到 fs
    			int ps = find2(i, fs);
    			if(ps < p){
    				f[i][j] = max(f[i][j], f[i - 1][k] - len + 2 * 5 * cal(s[i], ps + 1, p));
    			}
    		}
    	}
    }
    cout << f[1][1] << '\n';
    cout << f[2][2] << '\n';
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