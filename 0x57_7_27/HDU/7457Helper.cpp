#include<bits/stdc++.h>
using namespace std;
#define int long long

vector<vector<int> > preprocessFactors(int n){
	vector<vector<int> > factors(n + 1);
	for(int i = 1; i <= n; i ++){
		for(int j = 1; j <= n; j += i){
			factors[j].push_back(i);
		}
	}
	return factors;
}

void solve(){

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
