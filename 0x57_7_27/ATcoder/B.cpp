#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m,  x,  y;
char g[52][52];
string s;

void solve(){
	cin >> n >> m >>  x >>  y;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		cin >> g[i][j];       
        }
    }
	cin >> s;
	for(int i = 0; i < s.size(); i ++){
		int nx = x, ny = y;
		if(s[i] == 'U'){
			nx --;
		}
		else if(s[i] == 'D'){
			nx ++;
		}
		else if(s[i] == 'L'){
			ny --;
		}
		else{
			ny ++;
		}
		if(g[nx][ny] != '#' && nx >= 1 && nx <= n && ny >= 1 && ny <= m){
			x = nx;
			y = ny;
		}
		// cout << i + 1 << ' ' << x << ' ' << y << '\n';
	}
	cout << x << ' ' << y << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
// 模拟走路