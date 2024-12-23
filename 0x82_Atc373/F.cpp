#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3100;

int n, m;
int f[N], g[N], q[N << 1];

void solve(){
	cin >> n >> m; 
	for(int i = 1; i <= n; i ++){
		int wt, val, s;
		cin >> wt >> val;
		s = m / wt;
		if(s >= val / 2) s = val / 2;
		// cout << wt << ' ' << val << ' ' << s << '\n';
		memcpy(g, f, sizeof f);
		// 根据当前物品体积划分为 wt 个类
		for(int j = 0; j < wt; j ++){
			int hh = 0, tt = -1;
			// 对于每个类用单调队列优化 DP
			//  窗口 [k - s * wt, k - wt]
			for(int k = j; k <= m; k += wt){
				while(hh <= tt && q[hh] < k - s * wt) hh ++;
				if(hh <= tt){
					int t = (k - q[hh]) / wt;
					if(t > val / 2) t = val / 2;
					f[k] = max(g[k], g[q[hh]] + t * val - t * t);
				}
				int t = (k - q[tt]) / wt;
				if(t > val / 2) t = val / 2;
				while(hh <= tt && g[k] >= g[q[tt]] + t * val - t * t) tt --;
				q[++ tt] = k;
			}
		}
	}
	cout << f[m];
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
