#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

int n, q;
int a[N], s[N];

int ask(int l, int r){
	return s[r] - s[l - 1];
}

int ask(int id, int l, int r){
	l -= (id - 1) * n;
	r -= (id - 1) * n;
	if(id == 1) return ask(l, r);
	int nl = l + (id - 1);
	int nr = r + (id - 1);
	if(nl > n && nl > n) return ask(nl - n, nr - n);
	if(nl <= n && nr > n){
		nr -= n;
		return ask(nl, n) + ask(1, nr);
	}
	return ask(nl, nr);
}

int at(int pos){
	return (pos + n - 1) / n;
}

void solve(){
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
		s[i] = a[i] + s[i - 1];
    }
    // cout << ask(1, 1, 3) << ' ' << ask(3, 7, 9) << '\n';
    while(q --){
    	int l, r;
    	cin >> l >> r;
    	// 第一个 >= l 的 xn
    	// 第一个 <= r 的 x (n + 1)
    	int pl = at(l), pr = at(r);
    	// cout << pl << ' ' << pr << '\n';
    	if(pl == pr){ // 不超过一个区间
    		cout << ask(pl, l, r) << '\n';
    	}	
    	else{
    		int num1 = (l % n == 0 ? l : (l + (n - 1)) / n * n);
    		int num2 = (r + n - 1) / n * n;
    		num2 -= n;
    		// cout << "num: ";
    		// cout << num1 << ' ' << num2 << '\n';
    		cout << (pr - pl - 1) * s[n] + ask(pl, l, num1) + ask(pr, num2 + 1, r) << '\n';
    	}
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