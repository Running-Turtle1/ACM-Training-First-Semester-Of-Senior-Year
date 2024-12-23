#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e6 + 10;

int n, m;
int p[N], sz[N];

int cal(int x, int y){
	return (x - 1) * m + y;
}

int find(int x){
	if(x == p[x]) return x;
	p[x] = find(p[x]);
	return p[x];
}

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n * m; i ++){
    	p[i] = i;
    	sz[i] = 0;
    }
	char g[n + 10][m + 10];
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
    		cin >> g[i][j];        
    		if(g[i][j] == '#'){
    			sz[cal(i, j)] = 1;
    		}
        }
    }
    int res = 0;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
        	if(g[i][j] == '.') continue;
     		for(int d = 0; d < 4; d ++){
     			int a = i + dx[d], b = j + dy[d];
     			if(a >= 1 && a <= n && b >= 1 && b <= m && g[a][b] == '#'){
     				int fa = find(cal(i, j)), fb = find(cal(a, b));
     				if(fa != fb){
     					p[fa] = fb;
     					sz[fb] += sz[fa];
     					res = max(res, sz[fb]);
     				}
     			}
     		}
        }
    }
    // 预处理 row
    for(int i = 1; i <= n; i ++){
    	int s = 0;
    	for(int j = 1; j <= m; j ++){
    		s += g[i][j] == '.';
    	}
    	// 预处理三个连通块
       	set<int> st;
        int tmp = 0;
        for(int k = max(i - 1, 1LL); k <= min(i + 1, n); k ++){
     		for(int kj = 1; kj <= m; kj ++){
     			int fa = find(cal(k, kj));
     			if(st.count(fa) == false){
   					st.insert(fa);
   					tmp += sz[fa];
   				}
   			}
   		} 
     	res = max(res, tmp + s);
     	st.clear();
    }

    // 预处理 col
    for(int j = 1; j <= m; j ++){
    	int s = 0;
    	for(int i = 1; i <= n; i ++){
    		s += g[i][j] == '.';
    	}
    	// 预处理三个连通块
       	set<int> st;
        int tmp = 0;
        for(int k = max(j - 1, 1LL); k <= min(j + 1, m); k ++){
     		for(int kj = 1; kj <= n; kj ++){
     			int fa = find(cal(kj, k));
     			if(st.count(fa) == false){
   					st.insert(fa);
   					tmp += sz[fa];
   				}
   			}
   		} 
     	res = max(res, tmp + s);
     	st.clear();
    }

    cout << res << '\n';
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