#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N = 1;
int p = 1;



void solve(){

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

int Inv[N], Fact[N];
void initInv(int n){
	Fact[0] = 1;
	for(int i = 1; i <= n; i ++){
		Fact[i] = Fact[i - 1] * i % p;
    }
    Inv[n] = exgcd_cal(Fact[n], p);
    for(int i = n - 1; i >= 0; i --){
    	Inv[i] = Inv[i + 1] * (i + 1) % p;
    }
}