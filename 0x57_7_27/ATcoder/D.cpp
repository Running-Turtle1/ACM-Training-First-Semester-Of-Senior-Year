#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e5 + 10;

int n, q, x, k;
int a[N];

bool check(int d){
	int s = 0;
	// 统计 dis < d 的数量
	if(x < a[1]){
		int p = lower_bound(a + 1, a + n + 1, x + d) - a;
		s += (p - 1);
	}
	else if(x > a[n]){
		int l = 1, r = n;
		while(l < r){
			int mid = l + r >> 1;
			if(x - a[mid] < d) r = mid;
			else l = mid + 1;
		}
		if(x - a[n] < d) s += n - l + 1;
	}
	else{
		int pos = lower_bound(a + 1, a + n + 1, x) - a;
		int p = lower_bound(a + pos, a + n + 1, x + d) - a;
		s += (p - 1) - pos + 1;
		// cout << "s: " << s << '\n';
		// cout << "p: " << p << '\n';
		// cout << "pos: " << pos << '\n';
		int l = 1, r = pos - 1;
		while(l < r){
			int mid = l + r >> 1;
			if(x - a[mid] < d) r = mid;
			else l = mid + 1;
		}
		if(x - a[pos - 1] < d) s += (pos - 1) - l + 1;
		// cout << "l: " << l << '\n';
		// cout << s << '\n';
	}
	// cout << "s: " << s << '\n';
	return s <= k - 1;
}

bool check_(int d){
	// x - d + 1, x + d - 1
	int s = 0;
	if(d == 0) s = 0;
	else{
		int l = lower_bound(a + 1, a + n + 1, x - d + 1) - a;
		int r = upper_bound(a + 1, a + n + 1, x + d - 1) - a - 1;
		s = r - l + 1;
	} 
	return s <= k - 1;

}

void solve(){	
	cin >> n >> q;
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }
    sort(a + 1, a + n + 1);
    while(q --){
    	cin >> x >> k;

    	// int t=check(1);
    	// cout << "check: "<<t<<'\n';
    	// return ;

    	int l = 0, r = 2e18;
    	while(l < r){
    		int mid = l + r + 1 >> 1;
    		if(check_(mid)){
    			l = mid;
    		}
    		else{
    			r = mid - 1;
    		}
    	}
    	cout << l << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
