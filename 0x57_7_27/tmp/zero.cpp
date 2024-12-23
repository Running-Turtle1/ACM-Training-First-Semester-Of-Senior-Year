#include<bits/stdc++.h>
using namespace std;
#define int long long

int const mod = 998244353;
int const N = 1e5 + 10;

int n, k;
string s;
int f[N], l[N];

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
int inv(int x){
	return ksm(x, mod - 2, mod);
}
int v[N];
void solve(){
    cin >> n >> k >> s;
    s = ' ' + s;
    for(int i = 1; i <= n; i ++){
    	if(s[i] == '0') l[i] = -1;
    	else{
    		int j = i;
    		while(j <= n && s[j] != '0') j ++;
    		for(int k = i; k < j; k ++){
    			l[k] = i;
    		}
    		i = j - 1;
    	}
    }
    for(int i = 1; i <= n; i ++){
    	v[i] = ksm(i, k, mod);
    }
    // for(int i = 1; i <= n; i ++){
    // 	cout << l[i] << " \n"[i == n];
    // }
    for(int i = 1; i <= n; i ++){
    	if(s[i] == '0'){
    		f[i] = f[i - 1];
    	}
    	else if(f[i] == '1'){

    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
