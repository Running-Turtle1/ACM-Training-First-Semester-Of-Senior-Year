#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, a[200010];

void solve(){
	int res = 0, sum = 0;
	map<int, int> mp;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		sum += a[i];
		mp[a[i]] ++;
		if(sum % 2 == 0 && mp.count(sum / 2)){
			res ++;
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