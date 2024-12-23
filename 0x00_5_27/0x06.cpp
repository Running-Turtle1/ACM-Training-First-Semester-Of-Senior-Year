#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){

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
1010
0110
0100

010 操作 row :
1010
1001
0100

暴力 :
2^n 枚举操作类型, n*m 实现操作 + n*m 统计
2^n (n + m)