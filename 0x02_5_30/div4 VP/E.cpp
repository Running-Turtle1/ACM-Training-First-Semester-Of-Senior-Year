#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k, q;
int a[100010], b[100010];
// v[i] = (a[i + 1] - a[i]) / (b[i + 1] - b[i])

void solve(){
	cin >> n >> k >> q;
	for(int i = 1; i <= k; i ++){
		cin >> a[i];
    }
    for(int i = 1; i <= k; i ++){
		cin >> b[i];
    }
    a[0] = 0, b[0] = 0;
    while(q --){
    	int d;
    	cin >> d;
    	if(d == n){
    		cout << b[k] << ' ';
    		continue;
    	}
    	int p = upper_bound(a + 1, a + k + 1, d) - a - 1;
    	// cout << "p: " << p << '\n';
    	int res = b[p];
    	int dis = d - a[p];
    	int tim = dis * (b[p + 1] - b[p]) / (a[p + 1] - a[p]);
    	cout << res + tim << ' ';
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


