#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k;
vector<int> a;
int sz;
bool fg = false;

// 现在在考虑第 u 个数, 现在选了 s 个数, 现在的乘积之和是 mul 
// 搜出来 >= k 个就合法
void dfs(int u, int s, int mul){
	if(s == k){
		if(mul == n) fg = true;
		return ;
	}
	if(fg || u == sz || mul > n){
		return ;
	}
	if(n % (a[u] * mul) == 0){
		if(a[u] <= pow((n / s), 1.0 / (k - s)))
		dfs(u + 1, s + 1, mul * a[u]);	
	}
	
	dfs(u + 1, s, mul);
}

void solve(){
	fg = false;
	a.clear();
	cin >> n >> k;
	if(k >= 13){
		cout<<"NIE\n";
		return ;
	}
	for(int i = 2; i <= n / i; i ++){
		if(n % i == 0){
			a.push_back(i);
			if(i != n / i) a.push_back(n / i);
		}
	}
	a.push_back(n);
	sort(a.begin(), a.end());
	sz = a.size();
	dfs(0, 1, 1); // 1 一定选
	cout << (fg ? "TAK" : "NIE") << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	int t; cin >> t;
	while(t--) solve();
	return 0;
}	
// 因子超过 20 个一定合法
// 直接选出来二十个因子, 最后把多出来的因子全放到最大的因子上
// 如果因子 < 20 个, 假设 s1 个，首先单独拿出每个因子，出来了 s1 个,
// 还需要 k-s1 个，现在有 s2 个


/*
	枚举因子, 
*/

// hint1 : 13! > 1e9, 所以当 k >= 13 时, 输出 TAK
// 最多 2√n 个因子, 每个因子选或者不选