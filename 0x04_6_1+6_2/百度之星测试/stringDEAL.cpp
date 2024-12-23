#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	string s = "123,456";
	size_t p = s.find(",");
	if(p == string::npos){
		cout << "Illegal inputting\n";
		return ; 
	}
	int leftPart = stoi(s.substr(0, p));
	int rightPart = stoi(s.substr(p + 1));
	cout << leftPart << ' ' << rightPart << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	while (T --){
		solve();
	}

	return 0;
}