#include<bits/stdc++.h>
using namespace std;
#define int long long

constexpr int N = 3E5 + 10;

int f[N][2][2];

void solve(){
    int n;
    cin >> n;

    vector<int> a (n + 1, 0);
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }

    for(int i = 0; i <= n; i ++){
        for(int j = 0; j < 2; j ++) {
            for(int k = 0; k < 2; k ++) {
                f[i][j][k] = -1e9;
            }
        }
    }

    auto chmax = [] (int &x, int y) {
        if(x < y) x = y;
    };

    f[0][0][0] = 0;
    for(int i = 1; i <= n; i ++) {
        
        int t = 0;
        if(f[i - 1][0][0] < a[i]) t = 1;
        if(f[i - 1][0][0] > a[i]) t = -1;
        chmax(f[i][0][0], f[i - 1][0][0] + t);

        t = 0;
        if(f[i - 1][0][1] < a[i]) t = 1;
        if(f[i - 1][0][1] > a[i]) t = -1;
        chmax(f[i][0][1], f[i - 1][0][1] + t);

        t = 0;
        if(f[i - 1][1][1] < a[i]) t = 1;
        if(f[i - 1][1][1] > a[i]) t = -1;
        chmax(f[i][0][1], f[i - 1][1][1] + t);

        chmax(f[i][1][1], f[i - 1][1][1]);
        chmax(f[i][1][1], f[i - 1][0][0]);
    } 
    cout << max({f[n][0][1], f[n][1][1]}) << '\n';
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