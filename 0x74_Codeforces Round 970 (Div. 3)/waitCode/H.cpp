#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, q, a[N], cnt[N];

void solve(){
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		cnt[i] = 0;
	}
	for(int i = 1; i <= n; i ++){
		cnt[a[i]] ++;
    }
    for(int i = 1; i <= n; i ++){
    	cnt[i] += cnt[i - 1];
    }
    vector<int> f(n + 1, -1);
    int x;
    int lim = ((n & 1) ? ((n + 1) / 2) : (n + 2) / 2); // 中位数位置
    // cout << lim << '\n';
    function<bool(int)> check = [&] (int mid) -> bool {
    	int res = 0;
    	for(int i = 0; i <= n; i += x){
    		// [i, i + mid]
    		int r = i + mid > n ? n : i + mid;
    		res += (i ? cnt[r] - cnt[i - 1] : cnt[r]);
    	}
    	return res >= lim;
    };

    for(int i = 1; i <= q; i ++){
    	cin >> x;
    	if(f[x] != -1){
    		cout << f[x] << ' ';
    		continue ;
    	}
    	int l = 0, r = x - 1;
    	while(l < r){
    		int mid = l + r >> 1;
    		if(check(mid)) r = mid;
    		else l = mid + 1;
    	}
    	f[x] = l;
    	cout << f[x] << ' ';
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