#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
int const N = 1e5 + 10;
int p[N], ra[N];

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	ra[x] = (ra[x] + ra[p[x]]) % 3; // 更新 x 到新根 t 的距离
	return p[x] = t; // 更新 p[x], 路径压缩
}

void solve(){
	int n, k, res = 0;
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		p[i] = i;
		ra[i] = 0;
    }
	for(int i = 1; i <= k; i ++){
		int k, x, y;
		cin >> k >> x >> y;
		if(x > n || y > n){
			res ++;
			continue;
		}
		int px = find(x), py = find(y);
		if(k == 1){
			// 在同一棵树内但是不是同类
			if(px == py && (ra[x] - ra[y] + 3) % 3 != 0){
				res ++;
			}
			else if(px != py){
				p[px] = py;
				ra[px] = (ra[y] - ra[x] + 3) % 3;
			}
		}
		else{
			int px = find(x), py = find(y);
			if(px == py && (ra[x] - ra[y] + 3) % 3 != 1){
				res ++;
			}
			else if(px != py){
				p[px] = py;
				ra[px] = (ra[y] - ra[x] + 1 + 3) % 3;
			}
		}
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}