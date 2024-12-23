#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;
int const mod = 998244353;

int fact[N];

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

int inv(int x){
	return ksm(x, mod - 2, mod);
}

int C(int n, int m){
	// cout << fact[n] << ' ' << fact[m] << ' ' << fact[n - m] << '\n';
	return fact[n] * inv(fact[m]) % mod * inv(fact[n - m]) % mod;
}

int n, k, p;

vector<int> e[N];

int dp[N][3]; // 考虑以 i 为根子树, 多 0/1 , 不多方案数
int sz[N];

void dfs(int u, int fa){
	sz[u] = 1;
	int s = 0;
	int fac = 1;
	int facofeven = 1;
	for(auto &v : e[u]){
		if(v == fa) continue ;
		dfs(v, u);
		sz[u] += sz[v];
		if(sz[v] & 1){
			s ++;
			fac = fac * dp[v][0] % mod;
		}
		else{
			facofeven = facofeven * dp[v][2] % mod; 
		}
	}
	if(e[u].size() == 0){ // 叶子结点
		// cout << "leaf: " << u << '\n';
		dp[u][0] = 1;
		dp[u][1] = 1;
	}
	else if(sz[u] & 1){ // sz 是奇数, 偶数个奇数儿子, 儿子选一半即可, 父亲分配 0/1 或者 某个儿子多选两个,父亲补一个,少一个
		dp[u][0] = (facofeven * (C(s, s / 2) % mod * fac % mod + C(s, s / 2 + 1) % mod * fac % mod) % mod) % mod;
		dp[u][1] = dp[u][0];
		// dp[u][1] = facofeven * C(s, s / 2) % mod * fac % mod;
	}
	else{ // sz 是偶数, 偶数个奇数儿子
		dp[u][2] = facofeven * 2LL * C(s, s / 2) % mod * fac % mod; // 多选 0 或者 多选 1, 根节点补 0/1
	}
}

void solve(){
	cin >> n >> k;
	for(int i = 1; i <= n; i ++){
		e[i].clear();
		sz[i] = 0;
		fill(dp[i], dp[i] + 3, 0);
    }
    for(int i = 2; i <= n; i ++){
    	cin >> p;
    	e[p].push_back(i);
    }
    // for(auto &v : e[1]){
    // 	cout << "son: " << v << '\n';
    // }
    dfs(1, 0);
    // for(int i = 1; i <= n; i ++){
    // 	for(int j = 0; j < 3; j ++){
    // 		printf("dp[%lld][%lld]=%lld\n", i, j, dp[i][j]);
    // 	}
    // }
    if(sz[1] & 1){
    	cout << ksm(dp[1][0] + dp[1][1], k, mod) << '\n';	
    }
    else{
    	cout << ksm(dp[1][2], k, mod) << '\n';
    }
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	fact[0] = 1;
	for(int i = 1; i < N; i ++){
		fact[i] = fact[i - 1] * i % mod;
    }

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}