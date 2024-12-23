#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, m, q, a, b, c, d, e, f;

int in[N];

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> in[i];
    }
    int s = 0;
    while(true){
    	sort(in + 1, in + n + 1, [](int a, int b){
    		return a > b;
    	});
    	if(in[1] == 0 || in[2] == 0) break;
    	in[1] --;
    	in[2] --;
    	s ++;
    }
    cout << s << '\n';
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