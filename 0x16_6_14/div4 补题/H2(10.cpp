#include <bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 100;

int n, m;
int freeR[N], freeC[N], R[N], C[N];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};
int minx, maxx, miny, maxy, sz;

void dfs(int x, int y, vector<vector<bool>>& vis, vector<vector<char>>& g){
    vis[x][y] = true;
    minx = min(x, minx);
    maxx = max(x, maxx);
    miny = min(y, miny);
    maxy = max(y, maxy);
    sz ++;
    for(int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if(nx >= 1 && nx <= n && ny >= 1 && ny <= m && !vis[nx][ny] && g[nx][ny] == '#') {
            dfs(nx, ny, vis, g);
        }
    }
}

void solve(){
    // 预处理输入
    cin >> n >> m;
    vector<vector<char>> g(n + 10, vector<char>(m + 10));
    vector<vector<int>> repetition(n + 10, vector<int>(m + 10, 0));
    vector<vector<bool>> vis(n + 10, vector<bool>(m + 10, false));
    
    for(int i = 1; i <= n; i++){
        freeR[i] = 0;
        R[i] = 0;
    }
    for(int i = 1; i <= m; i++){
        freeC[i] = 0;
        C[i] = 0;
    }
    
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            cin >> g[i][j];  
        }
    }

    // 预处理 .
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		if(g[i][j] == '.'){
     			freeR[i] ++;
     			freeC[j] ++;
     		}       
        }
    }

    // dfs 处理连通块
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(!vis[i][j] && g[i][j] == '#'){
            	minx = miny = INT_MAX;
            	maxx = maxy = INT_MIN;
            	sz = 0;
            	dfs(i, j, vis, g);
            	minx = (minx - 1 < 1 ? 1 : minx - 1);
            	maxx = (maxx + 1 > n ? n : maxx + 1);
            	miny = (miny - 1 < 1 ? 1 : miny - 1);
            	maxy = (maxy + 1 > m ? m : maxy + 1);
            	R[minx] += sz; R[maxx + 1] -= sz;
            	C[miny] += sz; C[maxy + 1] -= sz;
            	repetition[minx][miny] += sz;
            	repetition[maxx + 1][maxy + 1] += sz;
            	repetition[minx][maxy + 1] -= sz;
            	repetition[maxx + 1][miny] -= sz;
            }
        }
    }
    for(int i = 1; i <= n; i ++){
    	R[i] += R[i - 1];
    }
    for(int i = 1; i <= m; i ++){
    	C[i] += C[i - 1];
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            repetition[i][j] += repetition[i - 1][j] + repetition[i][j - 1] - repetition[i - 1][j - 1];
        }
    }

    // for(int i = 1; i <= n; i ++){
    //     for(int j = 1; j <= m; j ++){
    //  		cout << repetition[i][j] << " \n"[j == m];       
    //     }
    // }
    // cout << '\n';

    int res = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		res = max(res, freeR[i] + freeC[j] - (g[i][j] == '.') + R[i] + C[j] - repetition[i][j]); 
     		// if(i == n && j == 2){
     		// 	cout << "res: " << freeR[i] + freeC[j] - (g[i][j] == '.') + R[i] + C[j] - repetition[i][j] << '\n';
     		// 	cout << repetition[i][j] << '\n';
     		// }
        }
    }

    cout << res << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    cin >> T;
    while (T--){
        solve();
    }

    return 0;
}
