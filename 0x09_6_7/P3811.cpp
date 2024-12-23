#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, p;
int const N = 6e6 + 10;
int Inv[N];

int ksm(int a, int k, int p){
	int res = 1;
	while(k){
		if(k & 1) res = res * a % p;
		k >>= 1; 
		a = a * a % p;
	}
	return res;
}

int pre[N], suf[N], a[N], Invs;

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

inline void write(int x){
    if(x < 0){
        putchar('-');
        x = -x;
    }
    if(x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void solve(){
	int n, p, k, x;
	n = read();
	p = read();
	k = read();
	pre[0] = 1;
	suf[n + 1] = 1;
	for(int i = 1; i <= n; i ++){
		a[i] = read();
		pre[i] = pre[i - 1] * a[i] % p;
    }
    for(int i = n; i >= 1; i --){
    	suf[i] = suf[i + 1] * a[i] % p;
    }
    Invs = ksm(pre[n], p - 2, p);
	int res = 0, sk = 1;
	for(int i = 1; i <= n; i ++){
		sk = sk * k % p;
		int tmp = sk * pre[i - 1] % p * suf[i + 1] % p * Invs % p;
		(res += tmp) %= p;
    }
    write(res % p);
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}