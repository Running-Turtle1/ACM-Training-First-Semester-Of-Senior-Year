#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int a[N], b[N];
int n, mid;
vector<int> e[N];

int x = 0;
bool fg = true;

int lim = 1e9;

// 看看以 u 为根的子树, 能不能让最小值达到 avg
void dfs(int u, int fa, int avg){
	if(fg == false || avg > lim){
		fg = false;
		return ;
	} 
	if(a[u] >= avg){
		for(int v: e[u]){
			if(v == fa) continue ;
			dfs(v, u, avg);
		}
	}
	else{ // a[u] < avg
		if(e[u].size() == 1){
			fg = false;
			return ;
		}
		for(int v: e[u]){
			if(v == fa) continue ;
			dfs(v, u, avg + (avg - a[u]));
		}
	}
}

bool check(){
	fg = true;
	for(auto v : e[1]){ 
		dfs(v, 1, mid);
	} 
	return fg;
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		e[i].clear();
    }
    for(int i = 2; i <= n; i ++){
    	int p;
    	cin >> p;
    	e[p].push_back(i);
    	e[i].push_back(p);
    }

    if(n == 1){
    	cout << a[1] << '\n';
    	return ;
    } 

    int l = 0, r = 1e9;
    while(l < r){
    	mid = l + r + 1 >> 1;
    	if(check()) l = mid;
    	else r = mid - 1;
    } 
    cout << a[1] + l << '\n';
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