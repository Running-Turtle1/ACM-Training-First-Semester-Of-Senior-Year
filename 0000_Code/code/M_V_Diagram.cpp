#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n, p;
    cin >> n;

    vector<int> a(n + 1), s(n + 1, 0);
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        s[i] = s[i - 1] + a[i];
    }
    for(int i = 1; i <= n; i ++){
        if(a[i] < a[i + 1]){
            p = i;
            break;
        }
    }
    // [1, n] ; [1, p + 1] ; [p - 1, n]
    double res = max({(double)(s[n]) / n, (double)(s[n] - s[p - 2]) / (n - p + 2), (double)(s[p + 1]) / (p + 1)});
    cout << fixed << setprecision(12) << res << '\n';
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