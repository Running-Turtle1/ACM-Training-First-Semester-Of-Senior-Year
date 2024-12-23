#include<bits/stdc++.h>
using namespace std;
#define int long long
int f(int x){
    int res = 0;
    while(x){
        res += x % 10;
        x /= 10;
    }
    return res;
}
void solve(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i ++){
        if(n % i == f(i)){
            cout << n << ' ' << i << '\n';
        }
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
