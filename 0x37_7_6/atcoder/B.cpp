#include<bits/stdc++.h>
using namespace std;
#define int long long

int a, b, c, d, e, f;
int g, h, i, j, k, l;

void solve(){
	// (a, b, c) (d, e, f)
	cin >> a >> b >> c >> d >> e >> f;
	// (g, h, i) (j, k, l)
	cin >> g >> h >> i >> j >> k >> l;
	int zmax = min(f, l), zmin = max(c, i);
	int ymax = min(e, k), ymin = max(b, h);
	int xmax = min(d, j), xmin = max(a, g);
	int res = (zmax - zmin) * (ymax - ymin) * (xmax - xmin);
	if(res > 0) cout << "Yes";
	else cout << "No";
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
