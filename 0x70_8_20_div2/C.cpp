#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

// 发现询问之后会给定 u 与 v 的中间点
// 类似二分进行交互

void solve(){
	cin >> n;
	vector<pair<int, int> > res;
	

	for(int i = 1; i < n; i ++){
		int now = n;
		while(true){
			cout << "? " << i << ' ' << now << endl;
			int response;
			cin >> response;
			if(response == i || response == now){
				res.push_back({i, now});
				break;
			}
			now = response;
		}
	}

	cout << "! ";
	for(auto &[x, y] : res){
		cout << x << ' ' << y << ' ';
	}
	cout << endl;
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