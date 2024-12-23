#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cout << i << " \n"[i == n];
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