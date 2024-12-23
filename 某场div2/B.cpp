#include<bits/stdc++.h>
using namespace std;
#define int long long

pair<int, int> tmp[1100];

void solve(){
	int n;
	cin >> n;

	vector<int> a(n + 1);
	vector<int> s(n + 1, 0);
	vector<int> get(n + 1, 0);

	for(int i = 1; i <= n; i ++) {
		cin >> a[i];
		++ s[a[i]];
	}

	for(int i = 1; i <= n; i ++){
		tmp[i] = {s[i], i};
    }
    sort(tmp + 1, tmp + n + 1);

    int cnt = 0;
    for(int i = 1; i <= n; i ++) {
    	for(int j = 1; j <= tmp[i].first; j ++) {
    		a[++ cnt] = tmp[i].second;
    	}
    }

    // for(int i = 1; i <= n; i ++){
    // 	cout << a[i] << " \n"[i == n];
    // }

	for(int i = 1; i <= n; i += 2) {
		++ get[a[i]];
	}

	int res = 0;
	for(int i = 1; i <= n; i ++){
		if(get[i]) {
			res ++;
			if(get[i] == s[i]) res ++;	
		}
    }

    cout << res << '\n';
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