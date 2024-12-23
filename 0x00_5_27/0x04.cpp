#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, a[2100];
int res = 0;

int lcm(int a, int b){
	return a * b / __gcd(a, b);
}

void dfs(int u, int s, int v, int x){
	if(v > x){
		return ;
	}
	if(v == x){
		res = max(res ,s);
		return ;
	}
	if(u == n){
		return ;
	}
	if(a[u] == 1){
		if(v) dfs(u + 1, s + 1, lcm(v,a[u]), x);
		else dfs(u + 1, s + 1, a[u], x);
		return ;
	}
	if(v) dfs(u + 1, s + 1, lcm(v,a[u]), x);
	else dfs(u + 1, s + 1, a[u], x);
	dfs(u+1, s, v, x);
}
// 1
// 6
// 1 2 3 10 20 60 
void solve(){
	res=0;
	cin >> n;
	multiset<int> st;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		st.insert(a[i]);
    }
    sort(a + 1, a + n + 1);
    // 
    bool fg = true;
    for(int i = 1; i <= n; i ++){
    	if(a[n] % a[i] != 0){
    		fg = false;
    	}
    }
    // cout << (fg) << '\n';
    if(fg == false){
    	cout << n << '\n';
    	return ;
    }
    // 最大值一定不选, 答案一定是最大值的约数
    // 所以枚举答案
    vector<int> v;
    for(int i = 1; i <= a[n] / i; i ++){
    	if(a[n] % i == 0){
    		v.push_back(i);
    		if(i != a[n] / i) v.push_back(a[n] / i);
    	}
    }
    sort(v.begin(), v.end());


    dfs(1, 0, 0, 21);
    cout << res << '\n';
    return ;

    for(auto &x : v){
    	if(st.count(x)) continue;
    	// 现在在考虑第 i 个数, 已经选了 s 个, 目前构成 v, 目标是 x
    	// cout << x << ' ' << res << '\n';
    	dfs(1, 0, 0, x); 
    }
    cout << res << '\n';
}
// 1
// 7
// 2 3 4 6 12 100003 1200036
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
// 现将序列排序, 因为选择子序列求 lcm, 所以显然是可以排序的
// 观察最大值, 是所有数的倍数, 一定不选他 ; 否则答案是 n ;
// 去掉最大值之后 //并不能递归求解
// 但是明确了一件事, 最大值一定不选了
// 1
// 7
// 2 3 4 6 12 100003 1200036
// 1
// 9
// 1 2 3 6 6 7 7 7 42
// 1 3 7 7 7 
// 1 2 3 6 6 7 7 7 42
// 21