#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int const M = 2e5 + 10;

struct Edge{
	int u, v, w;
	bool operator < (const Edge & T) const {
		return w < T.w;
	}
}edges[M];

int n, m, q;
int p[N];

int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}

void solve(){
	cin >> n;
	m = n * n;
	for(int i = 1; i <= n; i ++){
		p[i] = i;
		for(int j = 1; j <= n; j ++){
			int c;
			cin >> c;
			edges[(i - 1) * n + j] = {i, j, c};
		}
    }
    cin >> q;
    for(int i = 1; i <= q; i ++){
    	int a, b;
    	cin >> a >> b;
    	p[find(a)] = find(b);
    }
    int res = 0;
    sort(edges + 1, edges + m + 1);
    for(int i = 1; i <= m; i ++){
    	auto &[a, b, c] = edges[i];
    	if(find(a) != find(b)){
    		res += c;
    		p[find(b)] = find(a);
    	}
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	solve();
	return 0;
}
