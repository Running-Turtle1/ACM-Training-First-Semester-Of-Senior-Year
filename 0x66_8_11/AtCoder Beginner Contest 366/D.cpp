#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 110;

int n, q;
int s[N][N][N];

void sol(int id){
	auto &a = s[id];
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++){
			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		}
	}
}

int ask(int id, int x1, int y1, int x2, int y2){
	auto &a = s[id];
	return (a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1]);
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j ++){
			for(int k = 1; k <= n; k ++){
				cin >> s[i][j][k];
			}
		}
	}
	for(int i = 1; i <= n; i ++){
		sol(i); // 处理第 i 个矩阵的前缀和
	}
	// for(int i = 1; i <= n; i ++){
	// 	for(int j = 1; j <= n; j ++){
	// 		for(int k = 1; k <= n; k ++){
	// 			cout << s[i][j][k] << " \n"[k == n];
	// 		}
	// 	}
	// }
	// cout << ask(1, )
	cin >> q;
	while(q --){
		int x1, x2, y1, y2, z1, z2;
		cin >> x1 >> x2 >> y1 >> y2 >> z1 >> z2;
		int res = 0;
		for(int i = x1; i <= x2; i ++){
			// cout << "ask: " << i << ' ' << ask(i, y1, z1, y2, z2) << '\n';
			res += ask(i, y1, z1, y2, z2);
		}
		cout << res << '\n';
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
