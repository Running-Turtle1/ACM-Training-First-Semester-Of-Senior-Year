#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	cin >> n;

	vector<int> a(n + 1);
	vector<int> to(n + 1);
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }

    for(int i = 1; i <= n; i ++){
    	to[i] = a[n - i + 1];
    }

    vector<array<int, 2> > f(n + 1, {(int)1e9, (int)1e9});

    f[1][0] = f[1][1] = 0;

    int r = n / 2;
	for(int i = 2; i <= r; i ++){
		f[i][0] = min(f[i][0], f[i - 1][0] + (a[i - 1] == a[i]) + (to[i - 1] == to[i]));
		f[i][0] = min(f[i][0], f[i - 1][1] + (to[i - 1] == a[i]) + (a[i - 1] == to[i]));
		f[i][1] = min(f[i][1], f[i - 1][0] + (a[i - 1] == to[i]) + (to[i - 1] == a[i]));
		f[i][1] = min(f[i][1], f[i - 1][1] + (a[i] == a[i - 1]) + (to[i] == to[i - 1]));
		// cout << i << ' ' << f[i][0] << ' ' << f[i][1] << '\n';
	}	
	if(n % 2 == 0){
		f[r][0] += (a[r] == a[r + 1]);
		f[r][1] += (a[r] == a[r + 1]);
	}
	if(n & 1){
		cout << min(f[r][0] + (a[r + 1] == a[r]) + (to[r] == a[r + 1]), f[r][1] + (a[r + 1] == to[r]) + (a[r] == a[r + 1])) << '\n';
	}   
	else{
		cout << min(f[r][0], f[r][1]) << '\n';
	} 
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