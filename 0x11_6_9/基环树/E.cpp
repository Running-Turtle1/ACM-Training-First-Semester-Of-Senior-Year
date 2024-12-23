#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, a[N], f[N], vis[N];
vector<int> e[N];

int dfs(int u){
	if(f[u] != -1) return f[u];
	return f[u] = dfs(a[u]) + 1;
}

void solve(){
	memset(f, -1, sizeof f);
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    for(int i = 1; i <= n; i ++){
    	if(vis[i] == 0){ // 未被访问过
    		vis[i] = i; // 第 i 次访问过
    		int x = a[i];
    		while(true){
    			x = a[x];
    			if(vis[x]){ // 访问过
    				if(vis[x] == vis[i]){
    					// x 是环上的点
    					int now = x, sz = 0;
    					while(true){
    						now = a[now];
    						sz ++;
    						if(now == x) break;
    					}
    					now = x;
    					while(true){
    						f[now] = sz;
    						now = a[now];
    						if(now == x) break;
    					}
    					break;
    				}
    				else{ // 以前访问过
    					break;
    				}
    			}
    			vis[x] = i;
    		}
    	}
    }
    // for(int i = 1; i <= n; i ++){
    // 	cout << f[i] << " \n"[i == n];
    // }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	res += dfs(i);
    	// cout<<f[i]<<" \n"[i==n];
    }
    cout << res <<'\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}