#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, a[200010], b[200010];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    for(int i = 1; i <= n + 1; i ++){
    	cin >> b[i];
    }
    int res = 0;
    int mn = 2e9;
    for(int i = 1; i <= n; i ++){
    	res += abs(a[i] - b[i]);
    	int l = min(a[i], b[i]), r = max(a[i], b[i]);
    	if(l <= b[n + 1] && b[n + 1] <= r) mn = 0;
    	else{
    		mn = min({mn, abs(l - b[n + 1]), abs(r - b[n + 1])});
    	}
    }
    cout << res + mn + 1 << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	int t;
	cin>>t;
	while(t--)
	solve();
	return 0;
}