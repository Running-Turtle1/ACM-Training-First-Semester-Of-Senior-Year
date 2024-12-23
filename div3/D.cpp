#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n;
int a[N], s[N];

map<int, int> mp;

void solve(){
	mp.clear();
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
    }

    mp[0] = 0;

    vector<int> f(n + 1, 0);
    f[0] = 0;

    for(int i = 1; i <= n; i ++){
    	if(!a[i]){ // 直接拼接
    		f[i] = max(f[i], f[i - 1] + 1);
    	}
    	else if(mp.count(s[i])){
    		f[i] = max({f[i], f[i - 1], f[mp[s[i]]] + 1});
    	}
    	else f[i] = max(f[i], f[i - 1]); // 找不到拼接位置
    	mp[s[i]] = i;
    }
    cout << f[n] << '\n';
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