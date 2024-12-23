#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 4e5 + 10;
int const sz = __lg(N) + 3;

int n, k;
int a[N], s[N], f[N][sz];

int ask(int l, int r){
	return s[r] - s[l - 1];
}

bool check(int mid){
	for(int i = 1; i <= 2 * n + 1; i ++){
		for(int j = 0; j < sz; j ++){
			f[i][j] = 2 * n + 1;
		}
	}
	for(int i = 1, j = 1; i <= 2 * n; i ++){
		while(j <= 2 * n && ask(i, j) < mid) j ++;
		if(j <= 2 * n) f[i][0] = j + 1;
		else f[i][0] = j;
	}
	for(int j = 1; j < sz; j ++){
		for(int i = 1; i + (1 << j) <= 2 * n; i ++){
			f[i][j] = f[f[i][j - 1]][j - 1];
		}
	}
	for(int i = 1; i <= n; i ++){
		int p = i;
		for(int j = 0; j < 20; j ++){
			if(k >> j & 1){
				p = f[p][j];
			}
		}
		if(p - 1 <= i + n - 1) return true;
	}
	return false;
}

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		a[i + n] = a[i];
    }
    for(int i = 1; i <= 2 * n; i ++){
    	s[i] = s[i - 1] + a[i];
    }
    int l = 1, r = 2e9;
    while(l < r){
    	int mid = l + r + 1 >> 1;
    	if(check(mid)) l = mid;
    	else r = mid - 1;
    }
    cout << l << ' ';

    {
    	vector<int> res(n + 1, 0);
    	int mid = l;
	    for(int i = 1; i <= 2 * n; i ++){
			for(int j = 0; j < sz; j ++){
				f[i][j] = 2 * n + 1;
			}
		}
		for(int i = 1, j = 1; i <= 2 * n; i ++){
			while(j <= 2 * n && ask(i, j) < mid) j ++;
			if(j <= 2 * n) f[i][0] = j + 1;
			else f[i][0] = j;
		}
		for(int j = 1; j < sz; j ++){
			for(int i = 1; i + (1 << j) <= 2 * n; i ++){
				f[i][j] = f[f[i][j - 1]][j - 1];
			}
		}
		for(int i = 1; i <= n; i ++){
			int p = i;
			for(int j = 0; j < 20; j ++){
				if(k >> j & 1){
					p = f[p][j];
				}
			}
			if(p - 1 <= i + n - 1) res[i] = 1;
		}
		int ans = 0;
		for(int i = 1; i <= n; i ++){
			if(!res[i]){
				ans ++;
			}
		}
		cout << ans << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
