#include<bits/stdc++.h>
using namespace std;
#define int long long

// int const mx = (1LL << 16);

// int d[mx][15][15];
// int n;
// string s;
// string t;

// struct state{
// 	int sta;
// 	int p1;
// 	int p2;
// };

// state trans(string &s){
// 	int res = 0;
// 	int p1 = -1, p2 = -1;
// 	for(int i = 0; i < s.size(); i ++){
// 		if(s[i] == '.'){
// 			if(p1 == -1) p1 = i;
// 			else p2 = i; 
// 			continue;
// 		}
// 		res = res * 2 + s[i] - '0';
// 	}
// 	return state(res, )
// }

map<string, int> mp;
int n;
string s, tar;
void solve(){
	cin >> n >> s >> tar;
	s += "..", tar += "..";
	// cout << s << ' ' << tar << '\n';
	queue<string> q;
	mp[s] = 0;
	q.push(s);
	int cnt = 10;
	while(q.size()){
		string t = q.front(); q.pop();
		if(t==tar)break;
		// cout << t << '\n';
		// cnt ++;
		// if(cnt <= 20) cout << t << '\n';
		// vector<string> tmp;
		int p1 = -1, p2 = -1;
		for(int i = 0; i < t.size(); i ++){
			if(t[i] == '.' && p1 == -1) p1 = i;
			else if(t[i] == '.' && p1 != -1) p2 = i;
		}
		for(int i = 0; i + 1 < t.size(); i ++){
			if(t[i] != '.' && t[i + 1] != '.'){
				// tmp.push_back(s.substr(i, 2));
				string newS = t;
				newS[p1] = t[i], newS[p2] = t[i+1];
				newS[i] = newS[i + 1] = '.';
				// cout << "newS: " << newS << '\n';
				if(mp.count(newS) == false){
					mp[newS] = mp[t] + 1;
					q.push(newS);
				}
			}
		}
		// for(auto s : tmp){
		// 	string newS = s;
		// 	newS[p1] = s[0], newS[p2] = s[1];

		// }
	}
	if(mp.count(tar) == false) cout << "-1";
	else cout << mp[tar];
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
