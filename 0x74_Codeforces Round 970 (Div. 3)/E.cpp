#include<bits/stdc++.h>
using namespace std;
#define int long long

这里采用了 DP 的解法
dp[i][0 / 1] 表示考虑到第 i 个字符，
是否使用第二种操作, 使得[1,i] 是交替字符的方案数

int const inf = 2e18;

int n;
string s;
vector<array<int, 2> > f(200010);

void deal(int i, int j){
	for(int i = 1; i <= n; i ++){
		f[i][0] = f[i][1] = 2e18;
	}	
	char fs = ('a' + i), sc = ('a' + j); // fs sc
	f[1][0] = (s[1] == fs ? 0 : 1);
	f[1][1] = 1;
	for(int i = 2; i <= n; i ++){
		char t = (i & 1) ? fs : sc;
		char ano = (i & 1) == 0 ? fs : sc;
		f[i][0] = min(f[i][0], f[i - 1][0] + (s[i] != t));
		f[i][1] = min({f[i][1], f[i - 1][0] + 1, f[i - 1][1] + (s[i] != ano)});
	}
}

void solve(){
	cin >> n >> s;
	s = ' ' + s;

	int res = 2e18;
	for(int i = 0; i < 26; i ++){
		for(int j = 0; j < 26; j ++){
			deal(i, j);
			if(n & 1) res = min(res, f[n][1]);
			else res = min(res, f[n][0]);
		}
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