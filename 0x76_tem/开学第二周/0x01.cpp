#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 510;

int n, m, k; 

char g[N][N];

int sx, sy;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

bool st[N][N];

void dfs(int x, int y){
	g[x][y] = '.';
	st[x][y] = true;
	-- k;
	if(k == 0) return ;

	for(int d = 0; d < 4; d ++){
		int nx = x + dx[d], ny = y + dy[d];
		if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && g[nx][ny] == 'X' && st[nx][ny] == false){
			if(k) dfs(nx, ny);
		}
	}
}

void solve(){
	int s = 0;
	cin >> n >> m >> k;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		cin >> g[i][j];
     		if(g[i][j] == '.'){
     			sx = i;
     			sy = j;
     			s ++;
     			g[i][j] = 'X';
     		}       
        }
    }
    // cout << s << '\n';
    k = s - k;
    // cout << k << '\n';
    if(k) dfs(sx, sy);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            cout << g[i][j];
        }
        cout << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
