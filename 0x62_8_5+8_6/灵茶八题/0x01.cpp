#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int a[200010];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	res = res + (n - i + 1) * i * a[i];
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
