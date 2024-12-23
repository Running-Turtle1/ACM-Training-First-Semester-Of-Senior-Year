#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){ 
	int n = colors.size();
    int res = 0;
    for(int i = 0; i < n; i ++){
        int j = i;
        while((j + 1) % n != i && colors[(j + 1) % n] != colors[j]) j = (j + 1) % n;
        int len = (j >= i ? j - i + 1 : n + j - i + 1);
        if(len >= k) res += len - k + 1;
        // cout << i << ' ' << j << ' ' << len << '\n';
        if(j < i) i = n - 1;
        else i = j;
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
