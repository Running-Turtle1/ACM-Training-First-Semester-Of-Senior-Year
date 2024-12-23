#include<bits/stdc++.h>
using namespace std;
#define int long long

// 问题等价于将 a 个 1 和 b 个 2 分成两个和相等的数组
// 要求总和是偶数

void solve(){
	int a, b;
	cin >> a >> b;
	if((a + 2 * b) & 1){
		cout << "NO\n";
		return ;
	}
	if(a % 2 == 0 && b % 2 == 0){
		cout << "YES\n";
	}
	else if(b % 2 == 1){ // 奇数个 2
		if(a == 0){ // 一定不合法
			cout << "NO\n";
		}
		else{ // 一边分两个 1, 另一边分 1 个 2
			cout << "YES\n";
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