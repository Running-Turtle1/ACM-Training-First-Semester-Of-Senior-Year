#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;

struct Info{
	int a, b, dis;
}infos[2100];

int p[510], d[510];

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	d[x] = (d[x] + d[p[x]]) % 3;
	return p[x] = t;
}

void merge(int a, int b, int dis){
	int pa = find(a), pb = find(b);
	p[pb] = pa;
	d[pb] = ((dis + d[a] - d[b]) % 3 + 3) % 3;
}

int cal(int id){
	if(n == 1) return 0;
	for(int i = 1; i <= n; i ++){
		p[i] = i;
		d[i] = 0;
	}
	int cnt = 0;
	for(int i = 1; i <= m; i ++){
		auto& [a, b, dis] = infos[i];
		int pa = find(a), pb = find(b);
		if(pa != pb){
			merge(a, b, dis);
		}
		else{
			if(((d[b] - d[a]) % 3 + 3) % 3 != dis){
				cnt ++;
				if(cnt == 2) return i;
			}	
		}
	}
	return n;
}

void solve(){
	for(int i = 1; i <= m; i ++){
		string s;
		int pos;
		cin >> s;
		for(int j = 0; j < s.size(); j ++){
			if(isdigit(s[j]) == false){
				pos = j;
				break;
			}
		}
		int a = stoi(s.substr(0, pos));
		int b = stoi(s.substr(pos + 1));
		int dis = (s[pos] == '=' ? dis : (s[pos] == '<' ? 2 : 1));
		++ a, ++ b;
		infos[i] = {a, b, dis};
	}
	vector<int> v;
	for(int judge = 1; judge <= n; judge ++){
		for(int i = 1; i <= n; i ++){
			p[i] = i;
			d[i] = 0;
		}
		bool fg = true;
		for(int i = 1; i <= m; i ++){
			auto& [a, b, dis] = infos[i];
			if(a == judge || b == judge) continue ;
			int pa = find(a), pb = find(b);
			if(pa != pb){
				merge(a, b, dis);
			}
			else{
				if(((d[b] - d[a]) % 3 + 3) % 3 != dis){
					fg = false;
					break;
				}	
			}
		}
		if(fg){
			v.push_back(judge);
		}
	}
	// cout << v.size() << '\n';
	// for(auto &x : v){
	// 	cout << x << ' ';
	// }
	// cout << '\n';
	if(v.size() == 0){
		puts("Impossible");
	}
	else if(v.size() == 1){
		printf("Player %lld can be determined to be the judge after %lld lines\n", v[0] - 1, cal(v[0]));
	}
	else{
		puts("Can not determine");		
	}
}

signed main(){
	// ios::sync_with_stdio(false);
	// cin.tie(0), cout.tie(0); 
	while(cin >> n >> m){
		solve();		
	}
	return 0;
}
