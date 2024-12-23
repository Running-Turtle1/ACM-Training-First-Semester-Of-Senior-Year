#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n;
string str;

int oddcnt[N][26], evencnt[N][26];

void solve(){
	cin >> n >> str;
	str = ' ' + str;
	for(int i = 1; i <= n; i ++){
		for(int j = 0; j < 26; j ++){
			oddcnt[i][j] = oddcnt[i - 1][j];
			evencnt[i][j] = evencnt[i - 1][j];
		}
		if(i & 1) oddcnt[i][str[i] - 'a'] ++;
		else evencnt[i][str[i] - 'a'] ++;
	}
	auto askodd = [&] (int l, int r, int id) -> int {
		if(l > r) return 0;
		return oddcnt[r][id] - oddcnt[l - 1][id];
	};
	auto askeven = [&] (int l, int r, int id) -> int {
		if(l > r) return 0;
		return evencnt[r][id] - evencnt[l - 1][id];
	};
	if(n & 1){ // 使用一次删除操作
		int res = 2e18;
		for(int i = 1; i <= n; i ++){
			int mxodd = -2e18, mxeven = -2e18;
			for(int j = 0; j < 26; j ++){
				mxodd = max(mxodd, askodd(1, i - 1, j) + askeven(i + 1, n, j));
				mxeven = max(mxeven, askeven(1, i - 1, j) + askodd(i + 1, n, j));
			}
			res = min(res, n - mxodd - mxeven);
		}
		cout << res << '\n';
	}
	else{ // 不使用删除操作
		cout << n - *max_element(oddcnt[n], oddcnt[n] + 26) - *max_element(evencnt[n], evencnt[n] + 26) << '\n';
	}
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