#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, x, y;

void solve(){
	cin >> n >> x >> y;
	vector<int> a(n + 2, 0), b(n + 2, 0);
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    for(int i = 1; i <= n; i ++){
    	cin >> b[i];
    }
    sort(a.begin() + 1, a.begin() + n + 1, [] ( int a, int b){
    	return a > b;
    });
    sort(b.begin() + 1, b.begin() + n + 1, [] ( int a, int b){
    	return a > b;
    });
    a[n + 1] = b[n + 1] = 2e18;
    int resx, resy;
    for(int i = 1; i <= n + 1; i ++){
    	if(x < a[i]){
    		resx = i;
    		break;
    	}
    	x -= a[i];
    }
    for(int i = 1; i <= n + 1; i ++){
    	if(y < b[i]){
    		resy = i;
    		break;
    	}
    	y -= b[i];
    }
    cout << min({resx,resy,n});
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
// 按甜度和咸度分别从大到小排序, 看看哪种方案吃的最少