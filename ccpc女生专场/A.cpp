#include<bits/stdc++.h>
using namespace std;
#define int long long

vector<int> vc[10];

void move(int i, int j){
	auto& a = vc[i], b = vc[j];
	if(b.size() < a.size()) swap(a, b);
	for(auto &nx : a){
		b.push_back(nx);
	}
	a.clear();
}

void solve(){
	for(int i = 1; i <= 9; i ++){
		vc[i].clear();
	}
	vc[2].push_back(1);
	vc[3].push_back(2);
	vc[4].push_back(3);

	for(int i = 1; i <= 12; i ++){
		int a, b;
		cin >> a >> b;
		int p = -1;
		// 找到棋子位置
		for(int j = 1; j <= 9; j ++){
			for(auto &nx : vc[j]){
				if(nx == a){
					p = j;
				}
			}
		}
		vector<int> t, t_;
		bool fg = false;
		for(auto &nx : vc[p]){
			if(nx == a){
				fg = true;
			}
			if(fg) t.push_back(nx);
			else t_.push_back(nx);
		}
		swap(vc[p], t_);

		int ed = p + b;
		for(auto &nx : t) vc[ed].push_back(nx);
	}
	if(vc[9].size() == 3){
		cout << "Y\n";
	}
	else{
		cout << "N\n";
	}
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}