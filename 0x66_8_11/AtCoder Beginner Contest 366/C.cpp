#include<bits/stdc++.h>
using namespace std;
#define int long long

map<int, int> st;
int q;
void solve(){
	cin >> q;
	while(q --){
		int op, x;
		cin >> op;
		if(op!=3) cin>>x;
		switch (op) {
			case 1 :
				{
					st[x] ++;
				break;
				}
			case 2 :
				if(st[x] == 1) st.erase(x);
				else st[x] --;
				break;
			case 3 :
			// cout << "ask\n";
				cout << st.size() << '\n';
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
