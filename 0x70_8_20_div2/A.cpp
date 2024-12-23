#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, a[110];

// x 可以剔除所有夹着的数
// 对于 a <= b 也全部删除
// 就是一个严格下降区间
// 此时用结尾剃掉开头, 然后逐个剔除结尾
void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    int res = n - 1;
    for(int i = 1; i <= n; i ++){
    	int s = 0;
    	for(int j = 1; j <= n; j ++){
    		s += a[i] == a[j];
    	}
    	res = min(res, n - s);
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