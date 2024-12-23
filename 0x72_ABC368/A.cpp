#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, m, q, a, b, c, d, e, f;

int in[N];

void solve(){
	int k;
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		cin >> in[i];
    }
    for(int i = n - k + 1; i <= n; i ++) cout << in[i] << ' ';
	for(int i = 1; i <= n - k; i ++) cout << in[i] << ' ';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}