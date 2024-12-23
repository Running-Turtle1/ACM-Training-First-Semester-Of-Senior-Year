#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int a[510][510];

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
        	char x;
        	cin >> x;
        	a[i][j]=x-'0';
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            int x;
            char t;
            cin >> t;
            x=t-'0';
            x = (x - a[i][j]);
            x = (x % 3 + 3) % 3;
            a[i][j] = x;
        }
    }
    // for(int i = 1; i <= n; i ++){
    //     for(int j = 1; j <= m; j ++){
    //  		cout<<a[i][j]<<" \n"[j==m];       
    //     }
    // }
    for(int i = 1; i <= n; i++){
    	int s = 0;
    	for(int j = 1; j <= m; j ++){
    		s += a[i][j];
    	}
    	if(s % 3 != 0){
    		cout << "NO\n";
    		return ;
    	}
    }
    for(int j = 1; j <= m;j++){
    	int s = 0;
    	for(int i = 1; i<= n; i++){
    		s += a[i][j];
    	}
    	if(s % 3 != 0){
    		cout << "NO\n";
    		return ;
    	}
    }
    cout << "YES\n";
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