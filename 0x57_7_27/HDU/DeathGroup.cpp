#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, L, D;
int a[N];

void solve(){
	cin >> n >> L >> D;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    sort(a + 2, a + n + 1);
    if(a[1] >= L){
    	if(a[4] < L && a[1] - a[2] > D){
    		cout << "Yes\n";
    	}
    	else{
    		cout << "No\n";
    	}
    }
    else{
    	if(a[3] < L && a[n] - min(a[1], a[2]) > D){
    		cout << "Yes\n";
    	}
    	else{
    		cout << "No\n";
    	}
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