#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m1, m2;
int g1[10][10], g2[10][10];
int t[10][10], a[10][10], p[10];

void solve(){ 
	cin >> n;
	cin >> m1;
	for(int i = 1; i <= m1; i ++){
		int a, b; 
		cin >> a >> b;
		g1[a][b] = g1[b][a] = 1;
	}
	cin >> m2;
	for(int i = 1; i <= m2; i ++){
		int a, b;
		cin >> a >> b;
		g2[a][b] = g2[b][a] = 1;
	}
	for(int i = 1; i <= n; i ++){
		for(int j = i + 1; j <= n; j ++){
			cin >> a[i][j];
		}
	}
	iota(p + 1, p + n + 1, 1);
	int ans = 1e9;
	do{
		for(int i = 1; i <= n; i ++){
			for(int j = 1; j <= n; j ++){
				t[i][j] = 0;
			}
		}
		for(int i = 1; i <= n; i ++){
			for(int j = 1; j <= n; j ++){
				if(g1[i][j]){
					t[p[i]][p[j]] = 1;
				}
			}
		}
		int res = 0;
		for(int i = 1; i <= n; i ++){
			for(int j = i + 1; j <= n; j ++){
				if(g2[i][j] && !t[i][j]){ // 多余边
					res += a[i][j];
				}
				if(!g2[i][j] && t[i][j]){ // 缺失边
					res += a[i][j];
				}
			}
		}
		ans = min(ans, res);
	}
	while(next_permutation(p + 1, p + n + 1));
	cout << ans << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
