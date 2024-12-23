#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 1e9 + 7;
int n, x;

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

void solve(){
	int n;
	cin >> n;
	if(n == 1) cin >> n;
	else n = 0;
	cout << n;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
