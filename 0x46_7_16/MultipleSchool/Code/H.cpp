#include<bits/stdc++.h>
using namespace std;
#define int long long

struct node{
	string name;
	int solvedProblems;
	int penalty;

	bool operator < (const node & T) const{
		if(solvedProblems != T.solvedProblems){
			return solvedProblems > T.solvedProblems;
		}
		else{
			return penalty < T.penalty;
		}
	}
};


int const N = 1e5 + 10;

int n, m;
node fs[N], sc[N];
set<string> stringForfs;
set<string> both;

node tmp[N];
int cnt = 0;

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		string a;
		int b, c;
		cin >> a >> b >> c;
		fs[i] = {a, b, c};
		stringForfs.insert(a);
    }
    cin >> m;
    for(int i = 1; i <= m; i ++){
		string a;
		int b, c;
		cin >> a >> b >> c;
		sc[i] = {a, b, c};
		if(stringForfs.count(a)){
			both.insert(a);
		}
    }
    // for(auto s : both) cout << s << '\n'; 
    for(int i = 1; i <= n; i ++){
    	auto [a, b, c] = fs[i];
    	if(both.count(a) == true && a != "lzr010506") continue ;
    	tmp[++ cnt] = fs[i];
    }
    // cout << cnt << '\n';
    sort(tmp + 1, tmp + cnt + 1);
    int res = 0;
    for(int i = 1; i <= cnt; i ++){
    	auto [a, b, c] = tmp[i];
    	// cout << "\n";
    	// cout << a << ' ' << b << ' ' << c << '\n';
    	// cout << "\n";
    	if(a == "lzr010506"){
    		res = i;
    	}
    }
    cnt = 0;
    for(int i = 1; i <= n; i ++){
    	auto [a, b, c] = sc[i];
    	if(both.count(a) == true && a != "lzr010506") continue ;
    	tmp[++ cnt] = sc[i];
    }
    // cout << res << '\n';
    sort(tmp + 1, tmp + cnt + 1);
    for(int i = 1; i <= cnt; i ++){
    	auto [a, b, c] = tmp[i];
    	if(a == "lzr010506"){
    		res = min(res, i);
    	}
    }
    cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
