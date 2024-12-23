#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, m, k, pos, val, sum[N], ans[N];
pair<int, int> a[N];

bool check(int i, int x){
	pos = upper_bound(a + 1, a + n + 1, make_pair(val + x, LLONG_MAX)) - a;
	if(pos - 1 != i && val + x + 1 - a[pos - 1].first > k - x) return (n - pos + 1) < m;
	int l = 1, r = pos - 1;
	while(l < r){
		int mid = l + r >> 1;
		(pos - mid) * (val + x + 1) - (sum[pos - 1] - sum[mid - 1]) - (x + 1) * (mid <= i) <= k - x ? r = mid : l = mid + 1;
	} 
	return (l <= i ? n - l : n - l + 1) < m;
}

void solve(){
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i ++){
		cin >> a[i].first;
		a[i].second = i;
		k -= a[i].first;
    }
    sort(a + 1, a + n + 1, [&] (auto &a, auto &b){
    	return a.first < b.first;
    });
    for(int i = 1; i <= n; i ++){
    	sum[i] = sum[i - 1] + a[i].first;
    }
    for(int i = 1; i <= n; i ++){
    	val = a[i].first;
    	int id = a[i].second;
    	if(n - (upper_bound(a + 1, a + n + 1, make_pair(val + k, LLONG_MAX)) - a) + 1 >= m){
    		ans[id] = -1;
     		continue ;
    	}
    	int l = 0, r = k;
    	while(l < r){
    		int mid = l + r >> 1;
    		if(check(i, mid)) r = mid;
    		else l = mid + 1;
    	}
    	ans[id] = l;
    }
    for(int i = 1; i <= n; i ++){
    	cout << ans[i] << ' ';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
