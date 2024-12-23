#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, a[2100];
int lcm(int a, int b){
	return a * b / __gcd(a, b);
}

int check(int x){
	int s = 0, now = 0;
	for(int i = 1; i <= n; i ++){
		if(x % a[i] == 0){
			if(!now) now = a[i];
			else now = lcm(now, a[i]);
			s ++;
		}
	}
	if(now == x) return s;
	return 0;
}

void solve(){
	set<int> has;
	int Lcm = 0;
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    int mx = *max_element(a + 1, a + n + 1);
    has.insert(a + 1, a + n + 1);
	for(int i = 1; i <= n; i ++){
		if(!Lcm) Lcm = a[i];
		else Lcm = lcm(Lcm, a[i]);
		if(Lcm > mx){
			cout << n << '\n';
    		return ;
		}
    }
    
    int res = 0;
    for(int i = 1; i <= mx / i; i ++){
    	if(mx % i == 0){
    		if(has.count(i) == false){
    			res = max(res, check(i));
    		}
    		if(i != mx / i && has.count(mx / i) == false){
    			res = max(res, check(mx / i));
    		}
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
/*
hint1 : 
把所有元素的 lcm 算一下, > mx 元素, 答案 = n
进一步分析 : lcm >= x, 如果 lcm=x, 所有元素都是 mx 约数

hint2 :
不满足条件 1, lcm(a1, a2, ..., an) = mx,
此时答案也一定是 mx 的约数, 枚举答案

hint3 : 
从 n : a[] 取最多数构成 x 怎么取 ?
- 只要 x % a[i] == 0, 就取他
*/