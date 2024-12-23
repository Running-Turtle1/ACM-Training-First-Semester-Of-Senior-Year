#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;
int const sz = __lg(N) + 3;

int n, m, k;

int a[N], s[N], f[N][sz];
int Log2[N];

int ask(int l, int r){
	return s[r] - s[l - 1];
}

int t[N];

void solve(){
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		s[i] = s[i - 1] + a[i];
    }
    for(int i = 1; i <= n + 1; i ++){
    	for(int j = 0; j < sz; j ++){
    		f[i][j] = n + 1;
    	}
    }
    if(m > n) m = n;
    int use = 0;
    for(int i = 1; i <= n; i ++){
    	int l = i, r = n;
    	while(l < r){
    		int mid = l + r + 1 >> 1;
    		if(ask(i, mid) <= k) l = mid;
    		else r = mid - 1;
    	}
    	f[i][0] = l + 1;
    	// cout << "f[i][0]: " << i << ' ' << l + 1 << '\n'; 
    	// use ++;
    	// for(int j = i; j <= l; j ++) t[j] = use;
    	// i = l;
    }
    for(int j = 1; j < sz; j ++){
    	for(int i = 1; i + (1 << j) <= n; i ++){
    		f[i][j] = f[f[i][j - 1]][j - 1];
    	}
    }
    int res = 0;
    // for(int i = 1; i <= n; i ++){
    // 	if(t[i] <= m) res = i;
    // 	// cout << t[i] << " \n"[i == n];
    // }
    for(int i = 1; i <= n; i ++){
    	int now = i;
    	for(int j = 0; j < sz; j ++){
    		if(m >> j & 1){
    			now = f[now][j];
    		}
    	}
    	// cout << i << ' ' << now - 1 << '\n';
    	res = max(res, now - 1 - i + 1);
    	// cout << res << '\n';
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	for(int i = 2; i < N; i ++){
		Log2[i] = Log2[i / 2] + 1;
	}

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}