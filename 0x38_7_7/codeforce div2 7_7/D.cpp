#include<bits/stdc++.h>
using namespace std;
#define int long long

int cal(int x){
	unordered_set<int> st;
	for(int i = 1; i <= x / i; i ++){
		if(x % i == 0){
			st.insert(i);
			st.insert(x / i);
		}
	}
	return st.size();
}

void solve(){
	int num = -1, mx = -1;
	for(int i = 1; i <= 1e6; i ++){
		if(cal(i) > mx){
			mx = cal(i);
			num = i;
		}
	}
	cout << num << ' ' << mx << '\n';
}
// 83160 128
// 720720 240
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
