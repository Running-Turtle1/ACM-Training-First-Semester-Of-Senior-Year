#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
	char sab, sac, sbc;
	cin >> sab >> sac >> sbc;
	std::vector<int> in(3);
	if(sab == '<') in[1] ++;
	else in[0] ++;
	if(sbc == '<') in[2] ++;
	else in[1] ++;
	if(sac == '<') in[2] ++;
	else in[0] ++;
	for(int i = 0; i < 3; i ++){
		if(in[i] == 1){
			cout << (char)('A' + i);
			break;
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
