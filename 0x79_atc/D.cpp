#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;
int cnt = 0, t[N], x[N], p[N], l[N], r[N], s[N];
int n, q;

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> x[i];
		t[++ cnt] = x[i];
	}
	for(int i = 1; i <= n; i ++){
		cin >> p[i];
		// t[++ cnt] = p[i];
    }
    cin >> q;
    for(int i = 1; i <= q; i ++){
    	cin >> l[i] >> r[i];
    	t[++ cnt] = l[i];
    	t[++ cnt] = r[i];
    }
    sort(t + 1, t + cnt + 1);
    int sz = unique(t + 1, t + cnt + 1) - t - 1;
    for(int i = 1; i <= n; i ++){
    	x[i] = lower_bound(t + 1, t + sz + 1, x[i]) - t;
    }
    for(int i = 1; i <= q; i ++){
    	l[i] = lower_bound(t + 1, t + sz + 1, l[i]) - t;
    	r[i] = lower_bound(t + 1, t + sz + 1, r[i]) - t;
    	// cout << x[i] << ' ' << l[i] << ' ' << r[i] << '\n';
    }
    for(int i = 1; i <= n; i ++){
    	s[x[i]] += p[i];
    }
    for(int i = 1; i <= cnt; i ++){
    	s[i] += s[i - 1];
    }
    for(int i = 1; i <= q; i ++){
    	cout << s[r[i]] - s[l[i] - 1] << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
