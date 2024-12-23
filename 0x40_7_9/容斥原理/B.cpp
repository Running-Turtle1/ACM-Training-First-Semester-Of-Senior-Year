#include<bits/stdc++.h>
using namespace std;
#define int long long

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
	__int128 x = 1e18+1;
	write((__int128)(x*x));
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
