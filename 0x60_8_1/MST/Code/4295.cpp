#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 510;
int const M = 510000;

int n;
int w[N], p[N];

struct Edge{
	int u, v, w;
	bool operator < (const Edge & T) const {
		return w < T.w;
	}
}edges[M];

int cnt = 0;

int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}


void solve(){
	cnt = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++){
    	cin >> w[i];
    	p[i] = i;
    }
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
     		int c;
     		cin >> c;
     		edges[++ cnt] = {i, j, c + w[i] + w[j]};   
     		// edges[++ cnt] = {i, j, w[i] + w[j]};    
        }
    }
    sort(edges + 1, edges + cnt + 1);
    int res = 0;
    for(int i = 1; i <= cnt; i ++){
    	auto &[a, b, c] = edges[i];
    	int pa = find(a), pb = find(b);
    	if(pa != pb){
    		p[pb] = pa;
    		res += c;
    	}
    }
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