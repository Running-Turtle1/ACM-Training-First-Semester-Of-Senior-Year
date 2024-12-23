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
1≤T≤20,1≤n,m≤10,0≤k≤5
dfs 枚举 k 个新棋子的落点, 枚举结束后 ;
判断有多少种不同的连通块

如何判定本质相同 :
首先块数一样多, 其次所有点距离中心点的距离之和相同