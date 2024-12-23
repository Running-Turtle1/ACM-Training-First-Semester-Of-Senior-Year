#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n;
int p[N], d[N];

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	d[x] = (d[x] + d[p[x]]) % 2;
	return p[x] = t;
}

pair<int, int> ask[N];
int b[N << 1], e[N];

void solve(){
	cin >> n;
	for(int i = 1; i <= 2 * n; i ++){
		p[i] = i;
		d[i] = 0;
    }
    for(int i = 1; i <= n; i ++){
    	int x, y;
    	cin >> x >> y >> e[i];
    	ask[i] = {x, y};
    	b[i * 2 - 1] = x;
    	b[i * 2] = y; 
    }
    sort(b + 1, b + 2 * n + 1);
    int cnt = unique(b + 1, b + 2 * n + 1) - b - 1;
    for(int i = 1; i <= n; i ++){
    	ask[i].first = lower_bound(b + 1, b + cnt + 1, ask[i].first) - b;
    	ask[i].second = lower_bound(b + 1, b + cnt + 1, ask[i].second) - b;
    }
    // cout<<"Tet:\n";
    // for(int i = 1; i <= n; i ++){
    // 	auto &[l,r]=ask[i];
    // 	cout<<l<<' '<<r<<'\n';
    // }

    bool fg = true;
    for(int i = 1; i <= n; i ++){
    	auto &[x, y] = ask[i];
    	int px = find(x), py = find(y);
    	if(e[i] == 1){
    		p[px] = py;
    	}
    }
    for(int i = 1; i <= n; i ++){
    	auto &[x, y] = ask[i];
    	int px = find(x), py = find(y);
    	if(e[i] == 0){
    		if(p[px]==p[py]){
    			fg=false;
    		}
    	}
    }
    cout << (fg ? "YES" : "NO") << '\n';
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