#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, k;
int a[510][510];
string type[510];
int s[510][510];

int ask(int x1, int y1, int x2, int y2){
	int res = s[x2][y2] - s[x2][y1 - 1] - s[x1 - 1][y2] + s[x1 - 1][y1 - 1];
	return abs(res);
}

void solve(){
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		cin >> a[i][j];       
        }
    }
    for(int i = 1; i <= n; i ++){
    	cin >> type[i];
    	type[i] = ' ' + type[i];
    }
    int s1 = 0, s2 = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		if(type[i][j] == '1') s1 += a[i][j];
     		else s2 += a[i][j];       
        }
    }

    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		s[i][j] = 0;       
        }
    }
    int absDelta = abs(s1 - s2);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + (type[i][j] == '1' ? 1 : -1);   
        }
    }
    // for(int i = 1; i <= n; i ++){
    //     for(int j = 1; j <= m; j ++){
    //  		cout << s[i][j] << " \n"[j == m];       
    //     }
    // }
    // cout << "?\n";
    int gcd = 0;
    for(int i = 1; i + k - 1 <= n; i ++){
    	for(int j = 1; j  + k - 1 <= m; j ++){
    		int x = i + k - 1;
    		int y = j + k - 1;
    		// cout << i << ' ' << j << ' ' << ask(i, j, x, y) <<'\n';
    		gcd = __gcd(gcd, ask(i, j, x, y));
    	}
    }
    // cout << gcd << ' ' << absDelta << '\n';
    if(gcd == 0){
    	cout << (absDelta == 0 ? "YES\n" : "NO\n");
    }
    else if(absDelta % gcd == 0){
    	cout << "YES\n";
    }
    else{
    	cout << "NO\n";
    }
    // cout << "?\n";
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}