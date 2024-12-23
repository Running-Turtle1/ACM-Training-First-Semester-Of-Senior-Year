#include<bits/stdc++.h>
using namespace std;
#define int long long

int cnt, prim[N];
bool st[N];
void getprim(int n){
	for(int i = 2; i <= n; i ++){
		if(!st[i]) prim[cnt ++] = i;
		for(int j = 0; prim[j] * i <= n; j ++){
			st[i * prim[j]] = 1;
			if(i % prim[j] == 0) break;
		}
	}
	st[1] = true;
}


int const N = 5e6 + 10;

int n, m, a[N];

int cnt, prim[N];
bool st[N];
void getPrim(int n){
	for(int i = 2; i <= n; i ++){
        if(!st[i]) prim[cnt ++] = i;
        for(int j = 0; prim[j] <= n / i; j ++){
            st[prim[j] * i] = true;
            if(i % prim[j] == 0) break;
        }
    }
    st[1] = true;
}
bool isjishu[N];
void solve(){
	getPrim(N - 1);
	for(int i = 1; i < N; i ++){
		if(!st[i]){ // 找到一个质数
			for(int j = i; j < N; j = j * i){
				isjishu[j] = 1;
			}
		}
    }
    int res = 0;
    cin >> n;
    for(int i = 2; i <= n; i ++){
    	if(isjishu[i] == false) res ++;
    }
    cout << res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}