#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
int const N = 1100;
char g[N][N];

int cnt = 0;
vector<pair<int, int> > v[N * N];

bool st[N][N];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
void dfs(int x, int y){
	st[x][y] = true;
	v[cnt].push_back({x, y});
	for(int i = 0; i < 4; i ++){
		int a = x + dx[i], b = y + dy[i];
		if(a >= 1 && a <= n && b >= 1 && b <= n && st[a][b] == false && g[a][b] == '#'){
			dfs(a, b);
		}
	}
}

bool check(int x, int y){
	for(int i = 0; i < 4; i ++){
		int a = x + dx[i], b = y + dy[i];
		if(a >= 1 && a <= n && b >= 1 && b <= n){
			if(g[a][b] == '.') return true;
		}
	}
	return false;
}
bool check(int k){
	for(int i = 0; i < v[k].size(); i ++){
		auto [x, y] = v[k][i];
		if(check(x, y) == false) return false;
	}
	return true;
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
     		cin >> g[i][j];       
        }
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
     		if(st[i][j] == false && g[i][j] == '#'){
     			++ cnt;
     			dfs(i, j);
     		}       
        }
    }
    int res = 0;
    for(int i = 1; i <= cnt; i ++){
    	res += check(i);
    }
    cout << res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
