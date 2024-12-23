#include<bits/stdc++.h>
using namespace std;
#define int long long

int cal(){
    int res = 0;
    for(int i = 1; i < (1 << m); i ++){
        int t = 1, sign = 0;
        for(int j = 0; j < m; j ++){
            if(i >> j & 1){
                t *= prim[j];
                sign ++;
            }
        }
        if(sign & 1) res += n / t;
        else res -= n / t;
    }
    return res;
}

int cal(){
	int res = 0;
	for(int i = 1; i < (1 << m); i ++){
		int t = 1, sign = -1;
		for(int j = 0; j < m; j ++){
			if(i >> j & 1){
				t *= prim[j];
				sign = -sign;
			}
		}
		if(t) res += n / t * sign;
	}
	return res;
}

void solve(){

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
