#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, p, v;
int a[500010];
int idx = 0;

void solve(){
	cin >> n;
	int res = 0;
	while(n --){
		int p, v;
		cin >> p >> v;
		for(int i = idx; i > idx - p; i --){
			res -= i * a[i];
		}
		idx = idx - p;
		a[++ idx] = v;
		res += idx * a[idx];
		cout << res << '\n';
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
