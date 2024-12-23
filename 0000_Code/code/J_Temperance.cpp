#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

void solve(){
    cin >> n;
    map<int, int> mp[3];
    vector<int> x(n + 1), y(n + 1), z(n + 1);
    for(int i = 1; i <= n; i ++){
        cin >> x[i] >> y[i] >> z[i];
        mp[0][x[i]] ++;
        mp[1][y[i]] ++;
        mp[2][z[i]] ++;
    }
    vector<int> res (n + 1);
    for(int i = 1; i <= n; i ++){
        res[i] = max({mp[0][x[i]], mp[1][y[i]], mp[2][z[i]]}) - 1;
    }
    vector<int> cnt(n + 1, 0);
    for(int i = 1; i <= n; i ++){
        cnt[res[i]] ++;
    }
    int s = 0;
    for(int k = 0; k < n; k ++){
        cout << s << ' ';
        s += cnt[k]; 
    }
    cout << '\n';
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