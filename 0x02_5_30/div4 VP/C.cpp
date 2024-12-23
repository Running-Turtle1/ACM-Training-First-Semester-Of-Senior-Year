#include<bits/stdc++.h>
using namespace std;
#define int long long

int a, b, c, d;

void solve(){
	cin >> a >> b >> c >> d;
	if(c == a || c == b || d == a || d == b){
		cout << "YES\n";
		return ;
	}
	set<int> st;
	for(int i = (a + 1 == 13 ? 1 : a + 1); i != b; ){
		st.insert(i);
		i = i + 1;
		if(i == 13) i -= 12;
	}
	// for(auto &x : st) cout << x << ' '; cout << '\n';
	if(st.count(c) && st.count(d)){
		cout << "NO\n";
		return ;
	}
	if(!st.count(c) && !st.count(d)){
		cout << "NO\n";
		return ;
	}
	cout << "YES\n";
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}