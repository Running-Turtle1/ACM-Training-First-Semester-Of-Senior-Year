#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3100;

int n, m;

int w[N], v[N];

vector<int> vc[N];

int f[N];

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		cin >> w[i] >> v[i];
		int now = v[i] - 1;
		for(int j = 1; j * w[i] <= m; j ++){
			vc[w[i]].push_back(now);
			now -= 2;
		}
    }
    for(int i = 1; i <= m; i ++){
    	sort(vc[i].begin(), vc[i].end(), [&] (auto &a, auto &b){return a > b;});
    }

    // f[j] 背包为 j 的最大价值
    for(int i = 1; i <= m; i ++){ // 考虑物品的重量
    	for(int k = 0; k < vc[i].size(); k ++){ // 考虑物品
    		if(k > m / i) break;
    		for(int j = m; j >= i; j --){
    			f[j] = max(f[j], f[j - i] + vc[i][k]);
    		}
    	} 
    }
    int res = 0;
    for(int j = 0; j <= m; j ++){
    	res = max(res, f[j]);
    }
    cout << res << '\n';
}	

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
