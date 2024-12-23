#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;
int const sz = 25;

int n, a[N];
int s0[N][sz], s1[N][sz];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		a[i] ^= a[i - 1];
		for(int j = 0; j < sz; j ++){
			s0[i][j] = s0[i - 1][j] + ((a[i] >> j & 1) == 0);
			s1[i][j] = s1[i - 1][j] + (a[i] >> j & 1);
		}
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	for(int j = 0; j < sz; j ++){
    		if(a[i] >> j & 1){
    			res = res + (1 + s0[i - 1][j]) * (1LL << j);
    		}
    		else{
    			res = res + (s1[i - 1][j]) * (1LL << j);
    		}
    	}
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
