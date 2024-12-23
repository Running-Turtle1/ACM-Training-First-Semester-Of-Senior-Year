#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	char c1, c2, c3;
	cin >> c1 >> c2 >> c3;
	if(c1 == c3){
		cout << "B";
	}
	else{
		if(c1 == '<'){
			if(c2 == '<') cout << "C";
			else cout << "A";
		}
		else{
			if(c2 != '<') cout << "C";
			else cout << "A";
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
