#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 5e4 + 10;

int n, k;
int p[N], d[N];

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	d[x] = (d[x] + d[p[x]]) % 3;
	return p[x] = t;
}

void solve(){
	int res = 0;
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		p[i] = i;
    }
	for(int i = 1; i <= k; i ++){
		int op, x, y;
		cin >> op >> x >> y;
		// cout<<"Data
// cout<<		x<<' '<<y<<'\n';
		if(x > n || y > n){
			res ++;
			continue;
		}
		int px = find(x), py = find(y);
		// cout<<"find: " <<px<<' '<<py<<'\n';
		if(px == py){
			if(((d[x] - d[y]) % 3 + 3) %3 != op -1){
				res ++;
			}
		}
		else{
			// cout<<"Merge: " << x<<' '<<y<<'\n';
			p[py] = px;
			d[py] = ((d[x] - d[y] - (op - 1)) % 3 + 3) % 3;
		}
		// cout << i << ' ' << res << '\n';
	}
	// cout<<d[2]<<' '<<d[3]<<'\n';
	cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
