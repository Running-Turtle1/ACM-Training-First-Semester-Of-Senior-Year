#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
string s;
int dp[1100];

int res = 0;
string t1;
// void dfs(int u, int l, int r);
void dfs(int u);
int ask(int l, int r){
	t1 = s.substr(l, r - l + 1);
	// cout << t1 << '\n';
	res = 0;
	// dfs(0, l, r);
	dfs(0);
	return res;
}
bool judge(string &s){
	for(int i = 0; i < s.size(); i ++){
		if(s[i] == '?') return false;
	}
	string t = s;
	reverse(t.begin(), t.end());
	return s == t;
}
int const mod = 998244353;
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
int num[1100];
void solve(){
	cin >> n >> k >> s;
	s = ' ' + s;
	int quesMark = 0;
	for(int i = 1; i + k - 1 <= n; i ++){
		string tmp = s.substr(i, k);
		if(judge(tmp)){
			cout << "0";
			return ;
		}
	}
	for(int i = 1; i <= n; i ++){
		quesMark += (s[i] == '?');
		num[i] = quesMark;
    }
	int sum = ksm(2, quesMark, mod); // 总方案
	
	dp[k] = ask(1, k);
	for(int i = k + 1; i <= n; i ++){
		if(s[i] != '?'){
			dp[i] = dp[i - 1];	
		}
		else{
			// if(dp[i])
			int t = ask(i - k + 1, i);
			if(t == 0){
				cout << "0";
				return ;
			}
			dp[i] = ksm(2LL, num[i - k], mod) * ask(i - k + 1, i) % mod;
		}
	}
	// for(int i = 1; i <= n; i ++){
	// 	cout << dp[i] << " \n"[i == n];
    // }
	// cout << dp[n] << '\n';
	for(int i = 1; i <= n; i ++){
		cout << dp[i] << " \n"[i == n];
    }
	cout << sum << ' ' << dp[n] << '\n';
	cout << ((sum - dp[n]) % mod + mod) % mod << '\n';
}	

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

void dfs(int u){
	if(u == k){
		// 现在是修改完了 [i - k + 1, i]
		// string tmp = s.substr(i - k + 1 - k + 1, i - k + 1);
		// t1 = tmp + t1;
		string t2 = t1;
		// cout << t1 << '\n';
		reverse(t2.begin(), t2.end());
		res += (t1 == t2);
		return ;
	}
	if(t1[u] == 'A' || t1[u] == 'B'){
		dfs(u + 1);
	}
	else{
		t1[u] = 'A';
		dfs(u + 1);
		t1[u] = '?';

		t1[u] = 'B';
		dfs(u + 1);
		t1[u] = '?';
	}
}
// n * 2^k * k
// ai 建议我修改一下 dfs, 牛魔的

// ? 如果构造 a b 都错, 还是问号
// ? 只能构造成 a | b, 直接构造
// ? 都不能构造, 直接返回 0


// ????
// 2