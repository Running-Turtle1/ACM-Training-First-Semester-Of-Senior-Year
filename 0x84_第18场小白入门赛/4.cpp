#include<bits/stdc++.h>
using namespace std;
#define int long long

int dis(int a, int b){
	return (b - a) / 2 + (b - a) % 2;
}

void solve(){
	int a, b, c, x = 0;
	cin >> a >> b >> c;
	int d = (a + c - 1) / c * c; // 第一个 >= a 的 c 的倍数
	int e = b / c * c; // 第一个 <= b 的 c 的倍数
	if(d > b){ 
		cout << dis(a, b) << '\n';
	}
	else{
		cout << dis(a, d - 1) + dis(e + 1, b) + 1 + dis(1, c + 1) * ((e - d) / c) << '\n';
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