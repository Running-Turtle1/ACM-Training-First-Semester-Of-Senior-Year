#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

void solve(){
	cin >> n;
	// if(n == 1){
	// 	cout << "1\n1\n";
	// 	return ;
	// }
	int s1 = 0;
	for(int i = 0; i < 60; i ++){
		if(n >> i & 1) s1 ++;
	} 
	vector<int> res;
	res.push_back(1);
	res.push_back(0);
	for(int i = 1; i < s1; i ++){
		for(auto &x : res){
			x += (1LL << i);
		}
		int tmp = 0;
		for(int j = 0; j < i; j ++){
			if((res.back() >> j & 1) == 0){
				tmp += (1LL << j);
			}
		}
		res.push_back(tmp);
	}
	// for(auto &x : res){
	// 	cout << x << ' ';
	// }
	// cout << '\n';
	for(auto &x : res){
		int s = 0;
		// cout << x << ' ';
		int tmp = 0;
		for(int i = 0; i < 60; i ++){
			// cout << i << ' ' << (n >> i & 1) << ' ' << (x >> s & 1) << '\n';
			if(n >> i & 1){
				if(x >> s & 1)  tmp += (1LL << i);
				s ++;
			} 
		}
		x = tmp;
		// cout << x <<' ' << tmp << '\n';
	}
	int s = 0;
	for(auto &x : res) s += (x != 0);
	cout << s << '\n';
	sort(res.begin(),res.end());
	// cout << res.size() << '\n';
	for(auto &x : res){
		if(x)
		cout << x << ' ';
	}
	cout << '\n';
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