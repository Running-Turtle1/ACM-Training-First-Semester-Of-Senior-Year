#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int n, k, g, a[N];

void solve(){
	g = 0;
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		g = __gcd(g, a[i]);
    }
    if(n != 1){
    	for(int i = 1; i <= n; i ++){
    		a[i] = g * (i - 1);
    	}
    }

    a[++ n] = 1e18; // 方便处理数组的 trick
    k --; // 允许补 k - 1 次没出现的数
    int now; // [0, now] 都出现了
    if(a[1] == 0) now = 0;
    else{ // a[1] != 0
    	if(k == 0){
    		cout << "0\n";
    		return ;
    	}
    	k --;
    	now = 0;
    }

    for(int i = 1; i <= n; i ++){
    	if(now == a[i] || now == a[i] - 1){
    		now = a[i];
    	}
    	else{
    		// [now + 1, a[i] - 1]
    		int t = (a[i] - 1) - (now + 1) + 1;
    		if(k >= t){
    			k -= t; // 补上
    			now = a[i];
    		}
    		else{
    			cout << now + k + 1 << '\n';
    			return ;
    		}
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