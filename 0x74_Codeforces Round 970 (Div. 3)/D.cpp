#include<bits/stdc++.h>
using namespace std;
#define int long long

// 这种给出一个排列的题目, 且如果存在 i -> p_i
// 或者 p_i -> i 的边
// 那么一定会构成若干环
// 知道这个性质, 用任意方法维护一个环里面有多少个黑色的点即可

int const N = 2e5 + 10;

int n, x, p[N], to[N], st[N], f[N], c[N];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		st[i] = 0;
		cin >> x;
		to[i] = x;
	}

	string str;
	cin >> str;
	for(int i = 0; i < str.size(); i ++){
		c[i + 1] = (str[i] == '0' ? 0 : 1);
	}

	for(int i = 1; i <= n; i ++){
		// cout << "i: " << i << '\n';
		if(!st[i]){
			stack<int> stk;

			int sz = 0;
			
			int at = i;
			while(true){
				stk.push(at);
				st[at] = 1;
				if(c[at] == 0) sz ++;
				at = to[at];
				if(at == i) break;
			}

			// int sz = stk.size();
			while(stk.size()){
				x = stk.top();
				stk.pop();
				f[x] = sz;
			}
		}
	}

	for(int i = 1; i <= n; i ++){
		cout << f[i] << " \n"[i == n];
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