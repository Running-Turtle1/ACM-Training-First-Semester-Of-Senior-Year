#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	string s;
	cin >> s;
	int n = s.size(), s1 = 0, s2 = 0;
	for(int i = 1; i <= n; i ++){
		if(isupper(s[i - 1])) s1 ++;
		else s2 ++;
    }
    if(s1 > s2){
    	for(auto &x : s){
    		if(islower(x)) x = x - 'a' + 'A';
    		cout << x;
    	}
    }
    else{
    	for(auto &x : s){
    		if(isupper(x)) x = x - 'A' + 'a';
    		cout << x;
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
