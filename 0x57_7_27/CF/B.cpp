#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
char g[1100][1100];

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
     		cin >> g[i][j];       
        }
    }
    for(int i = 1; i <= n; i += k){
    	for(int j = 1; j <= n; j += k){
    		cout << g[i][j] - '0';
    	}
    	cout << '\n';
    }
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