#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	int n;
	cin >> n;

	vector<int> a(n + 1);
	for(int i = 1; i <= n; i ++){
		cin >> a[i];
    }	

    if(a[1] != 1){
    	cout << "-1";
    	return ;
    }
    vector<int> res;
    res.push_back(1);
    for(int i = 2; i <= n; i ++){
    	if(a[i] == a[i - 1]){
    		res.push_back(a[i - 1]);
    	}
    	else if(a[i] == a[i - 1] + 1){
    		res.push_back(a[i - 1] + 1);
    	}
    	else{
    		cout << "-1";
    		return ;
    	}
    }
    for(auto &nx : res) cout << nx << ' ';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
