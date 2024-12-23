#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n, m, q;

int a[N], b[N], c[N];
int f[1100][1100];

void solve(){
	int l, r;
	cin >> l >> r;
	cout << f[l][r] << '\n';
}


int g[1100][1100];
int ask(int l, int r){
	if(f[l][r] != -1){
		return f[l][r];
	}
	if(r - l + 1 < 3) return f[l][r] = 0;
	if(r - l + 1 == 3){
		if(g[l][l + 1] == 1 && g[l][l + 2] == 1 && g[l + 1][l + 2] == 1) return f[l][r] = 1;
		else return f[l][r] = 0;
	}
	int mx = 0;
	for(int k = l; k < r; k ++){
		mx = max(mx, ask(l, k) + ask(k + 1, r));
	}
	return f[l][r] = mx;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	memset(f, -1, sizeof f);

	for(int i = 1; i <= 1000; i ++){
        for(int j = 1; j <= 1000; j ++){
            g[i][j] = __gcd(i, j);
        }
    }

	for(int l = 1; l <= 1000; l ++){
		for(int r = l; r <= 1000; r ++){
			ask(l, r); 
			// for(int k = l; k < r; k ++){
				// int t = ask(l, k) + ask(k + 1, r);
				// if(ask(l, k) != -1 && ask(k + 1, r) != -1){
				// 	f[l][r] = max(f[l][r], f[l][k] + f[k + 1][r]);
				// }
			// }
		}
	}

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}