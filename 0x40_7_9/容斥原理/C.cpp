#include<bits/stdc++.h>
using namespace std;
#define int long long

bool isPrime(int x){
	for(int i = 2; i <= x / i; i ++){
		if(x % i == 0) return false;
	}
	return true;
}

void solve(){
	set<pair<int, int> > st;
	int cnt = 0;
	for(int i = 2; i < 60; i ++){
		if(isPrime(i)){
			st.insert({++ cnt, i});
		}
    }
    for(auto& [id, num] : st){
    	cout << id << ' ' << num << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
