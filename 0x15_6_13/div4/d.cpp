#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;

void solve(){
	cin >> n >> m;
	char g[n + 10][m + 10];
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            cin >> g[i][j];
        }
    }
    int mx = 0, row = 0;
    for(int i = 1; i <= n; i ++){
    	int s = 0;
        for(int j = 1; j <= m; j ++){
            s += g[i][j] == '#';
        }
        if(s > mx){
        	mx = s;
        	row = i;
        }
    }
    // row
    int l, r;
    for(int i = 1; i <= m; i ++){
    	if(g[row][i] == '#'){
    		l = i;
    		break;
    	}
    }
    for(int i = m; i >= 1; i --){
    	if(g[row][i] == '#'){
    		r = i;
    		break;
    	}
    }
    cout << row << ' ' << (l + r) / 2 << '\n';
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