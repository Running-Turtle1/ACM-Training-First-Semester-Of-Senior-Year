#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, a[N];
bool st[N];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		st[i] = false;
    }
    st[a[1]] = true;
    for(int i = 2; i <= n; i ++){
    	if((a[i] - 1 >= 1 && st[a[i] - 1]) || (a[i] + 1 <= n && st[a[i] + 1])){
    		st[a[i]] = true;
    	}
    	else{
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