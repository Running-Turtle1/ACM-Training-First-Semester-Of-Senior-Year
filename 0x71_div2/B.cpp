#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, a[100010];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    sort(a + 1, a + n + 1, [&] (int a, int b){
    	return a > b;
    });
    cout << a[(n + 1) / 2] << '\n';
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