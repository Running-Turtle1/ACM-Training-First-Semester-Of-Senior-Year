#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n, k;
	cin >> n >> k;

	vector<int> v(n + 3);
	for(int i = 1; i <= n; i ++){
		cin >> v[i];
    }
    sort(v.begin() + 1, v.begin() + n + 1, [&] (auto &a, auto &b) {
    	return a > b;
    });
    v[++ n] = 1e9;
    int sum = 0;
    for(int i = 1; i <= n; i ++){
    	sum += v[i];
    	if(sum > k) {
    		sum -= v[i];
    		cout << k - sum << '\n';
    		return ;
    	}
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