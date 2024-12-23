#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
string s;
int dp[1100];

int res = 0;
string t1, t2;
void dfs(int u, int l, int r);
int ask(int l, int r){
	t1 = t2 = "";
	res = 0;
	dfs(l, l, r);
	return res;
}

void solve(){
	cin >> n >> k >> s;
	s = ' ' + s;
	dp[k] = ask(1, k);
	for(int i = k + 1; i <= n; i ++){
		dp[i] = dp[i - k] * ask(i - k + 1, i);
	}
	cout << dp[n] << '\n';
}	

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

void dfs(int u, int l, int r){
	if(u == r + 1){
		t2 = t1;
		cout << t1 << '\n';
		reverse(t1.begin(), t1.end());
		res += (t1 != t2);
		return ;
	}
	if(s[u] == 'A' || s[u] == 'B'){
		t1 += s[u];
		dfs(u + 1, l, r);
		t1.pop_back();
	}
	else{
		t1 += 'A';
		dfs(u + 1, l, r);
		t1.pop_back();

		t1 += 'B';
		dfs(u + 1, l, r);
		t1.pop_back();
	}
}
// n * 2^k * k
// ai 建议我修改一下 dfs, 牛魔的