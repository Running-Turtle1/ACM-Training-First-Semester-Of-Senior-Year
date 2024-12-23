#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 510;

int n;
int a[N][N];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            cin >> a[i][j];
        }
    }
    vector<int> mx(2 * n + 3, 0);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
            if(a[i][j] < 0){
            	mx[j - i + n] = max(mx[j - i + n], abs(a[i][j]));
            }
        }
    }
    int res = 0;
    for(int i = 1; i <= 2 * n - 1; i ++){
    	res += mx[i];
    }
    cout << res << '\n';
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