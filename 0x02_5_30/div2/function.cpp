#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	char x;
	cin >> x;
	if(isdigit(x)){
		cout << x << " is numbers\n"; 
	}
	else if(islower(x)){
		cout << x << " is lower letters\n";
	}
	else if(isupper(x)){
		cout << x << " is upper letters\n";
	}
	else{
		cout << "else characters\n";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}