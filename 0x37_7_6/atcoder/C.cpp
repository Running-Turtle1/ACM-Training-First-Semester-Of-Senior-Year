#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
int const N = 2e5 + 10;
int a[N];

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    int res = LLONG_MAX;
    for(int l = 0; l <= k; l ++){
    	// 左边删除 l 个, a[l + 1]
    	int lval = a[l + 1];
    	// 右边删除 k-l 个, n-(k-l)
    	int rval = a[n - k + l];
    	// cout << l << ' ' << lval << ' ' << rval << '\n';
    	res = min(res, rval - lval);
    }
    cout << res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
