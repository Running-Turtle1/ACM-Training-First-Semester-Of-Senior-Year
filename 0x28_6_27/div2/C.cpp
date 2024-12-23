#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, l, r;
int a[100010];
vector<int> e[100010];
int cnt = 0;
// 这牌 > r 直接扔
// 这牌在 [l, r] 之间, 直接用
// 这牌 < l, 发挥一下, 跟后面 < l 的组合, 尽量少组合


// l = 100, r = 100

// 99 2 98

// < l 的连续块如何使用 ???????


// dp[i][0/1] 表示考虑到 i 且 是否用  i 结尾的最大组合数

// 划分, 往前取几个 ???

// dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);

// p 表示 s[p, i] >= l && s[p][i] <= r 最靠右的位置

// dp[i][1] = max dp[p - 1][0], dp[p - 1][1] + 1

int sol(int id){
	int sz = e[id].size();
	vector<array<int, 2> > dp(sz + 1, {0, 0});
	vector<int> s(sz + 1, 0);
	for(int i = 1; i <= sz; i ++){
		s[i] = s[i - 1] + e[id][i - 1];
	}
	for(int i = 1; i <= sz; i ++){
		dp[i][0] = max(dp[i - 1][0], dp[i - 1][1]);
		if(s[i] < l) continue;
		int lf = 1, rt = i;
		while(lf < rt){
			int mid = lf + rt + 1 >> 1;
			if(s[i] - s[mid - 1] >= l) lf = mid;
			else rt = mid - 1; 
		}
		if(s[i] - s[lf - 1] > r) continue;
		dp[i][1] = max(dp[lf - 1][0], dp[lf - 1][1]) + 1;
	}
	return max(dp[sz][0], dp[sz][1]);
}

void solve(){
	cin >> n >> l >> r;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    for(int i = 1; i <= cnt; i ++){
    	e[i].clear();
    }
    cnt = 0;
    int res = 0;
    for(int i = 1; i <= n; i ++){
    	if(a[i] > r) continue;
    	if(a[i] >= l && a[i] <= r) res ++;
    	if(a[i] < l){
    		++ cnt;
    		int j = i;
    		while(j <= n && a[j] < l){
    			e[cnt].push_back(a[j]);
    			j ++;
    		}
    		// cout << i << ' ' << j << '\n';
    		i = j - 1;
    	}
    }
    // cout << res << '\n';
    // cout << cnt << '\n';
    for(int i = 1; i <= cnt; i ++){
    	// cout << i << ' ' << sol(i) << '\n';
    	res += sol(i);
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

