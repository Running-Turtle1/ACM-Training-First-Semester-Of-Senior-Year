#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a;i <= b;i ++)
typedef long long ll;

int n, m;
int const N = 510, INF = 2e9;
int g[N][N], d[N];
bool st[N];

int prim(){
	for(int i = 1; i <= n; i ++){
 		d[i] = 2e9;       
    }
    int res = 0;
    d[1] = 0;
    for(int i = 1; i <= n; i ++){
    	int t = -1;
    	for(int j = 1; j <= n; j ++){
    		if(!st[j] && (t == -1 || d[j] < d[t])){
    			t = j;
    		}
    	}

    	if(d[t] == 2e9) return 2e9; // 不存在最小生成树
    	res += d[t];
    	st[t] = true;

    	for(int j = 1; j <= n; j ++){
    		d[j] = min(d[j], g[j][t]);
    	}
    }

    return res;
}

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
     		g[i][j] = 2e9;       
        }
    }
	for(int i = 1; i <= m; i ++){
		int a, b, c;
		cin >> a >> b >> c;
		g[a][b] = g[b][a] = min(g[a][b], c); // 建双向边
    }
    int res = prim();
    cout << (res == 2e9 ? "impossible" : to_string(res)) << '\n';
}

int main(){ 
    solve();
    return 0;
} 