#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3e4 + 10;
int n, m, k;
int p[N];
int find(int x){
	return (x == p[x] ? x : p[x] = find(p[x]));
}
void merge(int x, int y){
	x = find(x);
	y = find(y);
	if(x != y){
		p[x] = y;
	}
}
int v[N];
void solve(){
	// cout << n << ' ' << m << '\n';
	for(int i = 1; i <= n; i ++){
		p[i] = i;
    }
	for(int i = 1; i <= m; i ++){
		cin >> k;
		// vector<int> v(k + 1, 0);
		for(int j = 1; j <= k; j ++){
			cin >> v[j];
			// ++ v[i];
		}
		for(int j = 1; j < k; j ++){
			merge(v[j], v[j + 1]);
		}
		// cout<<"k: "<<k<<'\n';
		// for(int j=1;j<=k;j++){
		// 	cout<<v[j]<<" \n"[j==k];
		// }
	}
	// for(int i = 1; i <= n; i ++){
	// 	cout<<i<<' '<<"fa "<<find(i)<<'\n';
    // }
	int res = 0;
	for(int i = 1; i <= n; i ++){
		// cout << find(1) << ' ' << find(i) << '\n';
		if(find(i) == find(1)) res ++;
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	while (cin >> n >> m, n || m){
		solve();
	}

	return 0;
}