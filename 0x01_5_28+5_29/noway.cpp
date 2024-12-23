#include<bits/stdc++.h>
using namespace std;
#define int long long

int T;
int const N = 3e4 + 10;
int p[N], sz[N], d[N];

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	d[x] += d[p[x]];
	return p[x] = t;
}

void solve(){
	for(int i = 1; i < N; i ++){
		p[i] = i;
		sz[i] = 1;
		d[i] = 0;
    }
    cin >> T;
	while(T --){
		string opt;
		int x, y;
		cin >> opt >> x >> y;
		int px = find(x), py = find(y);
		if(opt == "M"){
			p[px] = py;
			d[px] = sz[py];
			sz[py] += sz[px];
		}
		else{
			cout << (px == py ? abs(d[x] - d[y]) - 1 : -1) << '\n';
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}