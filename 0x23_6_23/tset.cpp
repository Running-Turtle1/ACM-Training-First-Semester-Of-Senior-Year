#include<bits/stdc++.h>
using namespace std;
#define int long long

int k = 4;
void test(int mask){
	for(int i = k - 1; i >= 0; i --){
		cout << (mask >> i & 1);
	}
	cout << '\n';
}

void solve(){
	int mask = 7;
	test(mask);
	test(~mask);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
