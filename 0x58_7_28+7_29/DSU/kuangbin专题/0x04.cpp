#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, m;
int p[N], d[N];

int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
}

void solve(){
	cin >> n >> m;
	for(int i = 0; i <= n; i ++){
		p[i] = i;
		d[i] = 0;
	}
	int res = 0;
	while(m --){
		int l, r, s;
		cin >> l >> r >> s;
		l --;
		if(find(l) == find(r)){
			res += (s != d[r] - d[l]);
		}
		else{
			int pl = find(l), pr = find(r);
			if(pl < pr){
				p[pr] = pl;
				d[pr] = -d[r] + s + d[l]; 
			}
			else{
				p[pl] = pr;
				d[pl] = d[r] - s - d[l];
			}
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
