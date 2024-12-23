#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, p;

int exgcd(int a, int b, int &x, int &y){
	if(!b){
		x = 1;
		y = 0;
		return a;
	}
	int d = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return d;
}

int ksm(int a, int k, int p){
	a %= p;
	int res = 1;
	while(k){
		if(k & 1) res = res * a % p;
		k >>= 1;
		a = a * a % p;
	}
	return res;
}

// 求 a 在 mod p 意义下的乘法逆元
// int x, y;
// int cal(int a, int p){
// 	exgcd(a, p, x, y);
// 	return (x % p + p) % p;
// }

int cal(int a, int p){
	return ksm(a, p - 2, p);
}

void solve(){
	cin >> n >> p;
	for(int i = 1; i <= n; i ++){
		cout << cal(i, p) << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}