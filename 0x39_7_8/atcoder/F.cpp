#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

int pow(int a, int b){
	__int128 res = 1;
	for(int i = 1; i <= b; i ++){
		res = res * a;
		if(res > (__int128)(1e18)) return 2e18;
	}
	return (int)res;
}
vector<int> cal(int x){
	vector<int> v;
	for(int i = 2; i <= x / i; i ++){
		while(x % i == 0){
			x /= i;
			v.push_back(i);
		}
	}
	if(x > 1) v.push_back(x);
	return v;
}
void solve(){
	cin >> n;
	int res = 1;
	for(int b = 2; b < 60; b ++){
		if(pow(2,b)>n)break;
		int l = 2, r = 2e9;
		while(l < r){
			int mid = l + r  >> 1;
			if(pow(mid, b) > n) r = mid;
			else l = mid + 1;
		}
		r--;
	// 	long long l=2,r=2e9;
    // while(l<=r){
    //   long long t=(l+r)/2;
    //   if(pow(t,b)>n){r=t-1;}
    //   else{l=t+1;}
    // }
		// [2, l]
		bool fg=false;
		vector<int> pf = cal(b);
		for(int j = 0; j + 1 < pf.size(); j ++){
			if(pf[j] == pf[j + 1]){
				fg=true;
				break;
			}
		}
		if(fg)continue;
		if(pf.size()&1) res+=l-1;
		else res-=l-1;
	}
	cout<<res;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
