#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 1e9 + 7;
int n, a[200010];

int ksm(int a, int k, int p){  
    int res = 1;
    a %= p;
    while(k){
        if(k & 1) res = res * a % p;
        k >>= 1;
        a = a * a % p;
    }
    return res;
}

// 非空子序列和的和
int sol1(int n, int *a, int mod){
	int res = 0;
	for(int i = 1; i <= n; i ++){
		int t = ksm(2LL, n - 1, mod) * a[i] % mod;
		res = (res + t) % mod;
    }
    return res;
}

// 非空子序列异或和的异或和
int sol2(int n, int *a){
	return n == 1 ? a[1] : 0;
}

// 非空子序列异或和的和
int sol3(int n, int *a, int mod){ 
	// 考虑某一位上 0 和 1 的个数, 推公式
	// 全 0 无贡献, 存在 1 求奇数个 1 有多少种方案
	int const sz = __lg(*max_element(a + 1, a + n + 1)) + 3;
	vector<int> s(sz + 1);

	for(int i = 1; i <= n; i ++){
		for(int j = 0; j < sz; j ++){
			s[j] += (a[i] >> j & 1);
		}
	}

	int res = 0;
	for(int k = 0; k < sz; k ++){
		if(s[k]) res = (res + ksm(2LL, n + k - 1, mod)) % mod;
    }
    return res;
}

// 非空子序列和的异或和
int sol4(int n, int *a){
	// n <= 1000, \sum a[i] < 2^16
	// dp[i][j] 表示考虑到第 i 个数得到结果 j 的方案数
	vector<vector<int> > dp(2, vector<int> (1LL << 16, 0));
	dp[0][0] = 1;
	for(int i = 1; i <= n; i ++){
		int now = i & 1;
		fill(dp[now].begin(), dp[now].end(), 0);
		for(int j = 0; j < 1LL << 16; j ++){
			dp[now][j] = (dp[now][j] + dp[now ^ 1][j]) % 2; // 算奇偶性即可
			if(j >= a[i]){
				dp[now][j] = (dp[now][j] + dp[now ^ 1][j - a[i]]) % 2;
			}
		}
    }
    int res = 0;
    for(int i = 0; i < 1LL << 16; i ++){
    	if(dp[n & 1][i]) res ^= i;
    }
    return res;
}

void solve(){
	int res = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    cout << sol4(n, a) << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
