#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m, p;
int A[12][12];
int d[12][12][10010];

struct node{
	int x, y, v;
};

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void solve(){
	cin >> n >> m >> p;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		cin >> A[i][j];
     		A[i][j] %= (p - 1);       
        }
    }
    memset(d, -1, sizeof d);
    queue<node> q;
    q.push({1, 1, A[1][1]});
    // d[1][1][0] = 0;
    d[1][1][A[1][1]] = 0;
    while(q.size()){
    	// auto &[x, y, v] = q.front(); q.pop();
    	auto [x, y, v] = q.front(); q.pop();
    	// cout << x << ' ' << y << ' ' << v << ' ' << d[x][y][v] << '\n';
    	for(int i = 0; i < 4; i ++){
    		int a = x + dx[i];
    		int b = y + dy[i];
    		if(a >= 1 && a <= n && b >= 1 && b <= m){
    			int tmpV = (v + A[a][b]) % (p - 1);
    			if(d[a][b][tmpV] == -1){
    				d[a][b][tmpV] = d[x][y][v] + 1;
    				q.push({a, b, tmpV});
    			}
    		}
    	}
    }
    // cout << d[1][1][1] << '\n';
    // cout << d[1][2][3] << '\n';
    // cout << d[1][3][6] << '\n';
    cout << d[n][m][0];
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
