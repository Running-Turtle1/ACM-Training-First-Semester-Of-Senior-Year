#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n, k, a[N], p[N];

int find(int x){
	return x == p[x] ? x : p[x] = find(p[x]);
}

void merge(int u, int v){
	int pu = find(u), pv = find(v);
	if(pu != pv){
		p[pu] = pv;
	}
}

int del[N];
int cnt = 0, arr[N];

void solve(){
	cin >> n >> k;
    // n = 100000;
    // k = 1e18;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
        // a[i] = 1e18;
		p[i] = i;
		del[i] = 0;
    } 

    for(int j = 60; j >= 0; j --){
    	cnt = 0;
    	int t = (k >> j & 1); 
    	for(int i = 1; i <= n; i ++){
    		if(del[i]) continue ;
    		if(a[i] >> j & 1){
    			if(t == 0) arr[++ cnt] = i;
    			else{
    				if(j == 0) arr[++ cnt] = i;
    				continue ;
    			}
    		}
    		else{
    			if(t == 1) del[i] = 1;
    			else{
    				if(j == 0) arr[++ cnt] = i;
    				continue ;
    			}
    		}
    	} 
    	for(int i = 1; i + 1 <= cnt; i ++){
    		merge(arr[i], arr[i + 1]);
    	}
    } 
	map<int, int> mp;
	for(int i = 1; i <= n; i ++){
		mp[find(i)] ++;
	}
	int res = 0;
	for(auto [x, y] : mp) res = max(res, y);
	cout << res << '\n';
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