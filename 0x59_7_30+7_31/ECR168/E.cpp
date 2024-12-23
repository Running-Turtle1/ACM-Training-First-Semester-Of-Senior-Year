#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, q, p, x;
int a[N];
// 4 3
void simulate(){
	int level = 1;
	int s = 0;
	for(int i = 1; i <= n; i ++){
		if(i < p && level + (p - i + 1 + s) / x <= a[p]){
			// cout << "I: " << i << '\n';
			// cout << level << '\n';
			cout << "YES\n";
			return ;
		}
		if(i == p){
			if(level > a[p]){
				cout << "NO\n";
				return;
			}
			else{
				cout << "YES\n";
				return ;
			}
		}
		if(level > a[i]) continue ;
		s ++;
		if(s == x) s = 0, level ++;
	}
}
// int res[N][(int)sqrt(N)];
void solve(){
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }

    int lim = (int)sqrt(n);

    int nlim = lim / 10;
    if(nlim < 0) nlim = 1;

    // 0 表示不战斗
    // 1 表示战斗
    vector<vector<int> > res(nlim + 1, vector<int> (n + 1, 0));
    for(int k = 1; k <= lim; k ++){ // 预处理 sqrt {x} 个答案
    	auto &vc = res[k];
    	int level = 1;
		int s = 0;
    	for(int i = 1; i <= n; i ++){  
			if(level > a[i]) vc[i] = 0;
			else vc[i] = 1, s ++;
			if(s == k) s = 0, level ++;
    	}
    }

    // for(int i = 1; i <= lim; i ++){

    // }

    while(q --){
    	cin >> p >> x;
    	// cout << p << ' ' << x << '\n'
    	if(x <= nlim){
    		cout << (res[x][p] ? "YES" : "NO") << '\n';
    		// return ;
    		continue ;
    	}
    	if(x > n){
    		int mxLevel = n / x;
    		if(p > mxLevel){
    			cout << "YES\n";
    			continue ;
    			// return ;
    		}
    	}
    	// cout << "simulate\n";
    	simulate();
    }

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	// cin >> T;
	while (T --){
		solve();
	}

	return 0;
}