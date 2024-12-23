#include<bits/stdc++.h>
using namespace std;
#define int long long
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
	int mod = 3;
	cout << ksm(2, mod - 2, mod) << ',';
	mod = 5;
	cout << ksm(2, mod - 2, mod) << ',';
	mod = 7;
	cout << ksm(2, mod - 2, mod) << ',';
	mod = 11;
	cout << ksm(2, mod - 2, mod) << ',';
	mod = 13;
	cout << ksm(2, mod - 2, mod) << ',';
	mod = 17;
	cout << ksm(2, mod - 2, mod) << ',';
	mod = 19;
	cout << ksm(2, mod - 2, mod) << ',';
	mod = 23;
	cout << ksm(2, mod - 2, mod) << ',';
}	

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
