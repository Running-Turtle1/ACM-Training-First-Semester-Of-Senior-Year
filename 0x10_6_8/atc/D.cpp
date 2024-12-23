#include<bits/stdc++.h>
using namespace std;
#define int __int128

int const p = 998244353;
inline int read(){
    int x = 0, f = 1; // f 代表正负 
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = x * 10LL + c - '0';
        c = getchar();
    }
    return x * f;
} 


int n, x;

int ksm(int a, int k){
	int res = 1;
	while(k){
		if(k & 1) res = res * a % p;
		k >>= 1;
		a = a * a % p;
	}
	return res;
}
inline void write(__int128 x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}
void solve(){
	n = read();
	int x = 0;
	int cal = n;
	while(cal){
		cal /= 10;
		x ++;
	}
	int res = ksm(10LL, n * x) - 1;
	int t = ((ksm(10LL, x) - 1) % p + p) % p;
	res = res * ksm(t, p - 2) % p * n % p;
	write(res);
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	// cout << 99999 / 9 * 5 << '\n';

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}