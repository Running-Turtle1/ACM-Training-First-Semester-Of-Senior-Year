#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 998244353;

int n, k;
int f[1100][1 << (11)];
string s;

bool check(int s){ // 不是回文返回 true
	for(int i = 0, j = k - 1; i <= j; i ++, j --){
		if((s >> i & 1) != (s >> j & 1)) return true;
	}
	return false;
}
void test(int mask){
	for(int i = k - 1; i >= 0; i --){
		cout << (mask >> i & 1);
	}
	cout << '\n';
}
void dfs(int u, int mask){ // 正在处理第 u 个字母, 当前状态为 mask
	if(u == k + 1){
		if(check(mask)){
			// test(mask);
			f[k][mask] = 1;
		}
		return ;
	}
	if(s[u] == 'A'){
		dfs(u + 1, mask << 1);
	}
	else if(s[u] == 'B'){
		dfs(u + 1, mask << 1 | 1);
	}
	else{
		dfs(u + 1, mask << 1);
		dfs(u + 1, mask << 1 | 1);
	}
}

void solve(){
	cin >> n >> k >> s;
	s = ' ' + s;
	dfs(1, 0); // 预处理 dp[k][?] 状态
	for(int i = k; i < n; i ++){
		for(int j = 0; j < (1 << k); j ++){
			if(f[i][j] == 0) continue;
			if(s[i + 1] == 'A'){
				// int nj = ((j) & ~(1 << (k - 1))) << 1;
				int nj = j;
				if(j >> (k - 1) & 1) nj -= (1 << (k - 1));
				nj <<= 1;
				if(check(nj)){
					f[i + 1][nj] = (f[i + 1][nj] + f[i][j]) % mod;
				}
			}
			else if(s[i + 1] == 'B'){
				int nj = j;
				if(j >> (k - 1) & 1) nj -= (1 << (k - 1));
				nj <<= 1;
				nj |= 1;
				if(check(nj)){
					f[i + 1][nj] = (f[i + 1][nj] + f[i][j]) % mod;
				}
			}
			else{
				int nj = j;
				if(j >> (k - 1) & 1) nj -= (1 << (k - 1));
				nj <<= 1;
				if(check(nj)){
					f[i + 1][nj] = (f[i + 1][nj] + f[i][j]) % mod;
				}
				nj = j;
				if(j >> (k - 1) & 1) nj -= (1 << (k - 1));
				nj <<= 1;
				nj |= 1;
				if(check(nj)){
					f[i + 1][nj] = (f[i + 1][nj] + f[i][j]) % mod;
				}
			}
		}
	}
	int res = 0;
	for(int i = 0; i < (1 << k); i ++){
		(res += f[n][i]) %= mod;
    }
    cout << res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
