#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
string s;

int check(int l, int r){
	if(s[l] == s[r]) return 1;
	for(int k = l; k < r; k ++){
		bool fg = true;
		if(s[k] == s[k + 1]) fg = false; //return 0;
		if(s[k] == s[l] && s[k + 1] == s[r]) fg = false; //return 0;
		if(fg) return 1;
	}
	return 0;
}
int p[100];
void sol(){
	int n;
	string s;
	cin >> s;
	n = s.size(); 
	int cnt[30];
	for(int i = 0; i < 26; i ++){
		cnt[i] = 0;
    }
    
    int mn = 2e9;
    for(int i = 0; i < n; i ++){
    	cnt[s[i] - 'a'] ++;
    }
    while(true){
    	bool fg = false;
	    for(int i = 0; i < 26; i ++){
	    	if(cnt[i]){
	    		cnt[i] --;
	    		cout << (char)('a' + i);
	    		fg = true;
	    	}
	    	// char x = 'a' + i - 1;
	    	// for(int j = 1; j <= cnt[i - 1]; j ++){
	    	// 	cout << x;
	    	// }
	    	// mn = min(mn, cnt[i - 1]);
	    }
	    if(fg == false) break;
    }

    cout << '\n';
}
void solve(){
	cin >> s;
	string finddd;
	cin >> finddd;
	n = s.size();
	s = ' ' + s;
	int mx = 0;
	map<int, vector<string> > mp;
	for(int i = 1; i <= n; i ++){
		p[i] = i;
    }
    do{
    	string t = s;
    	for(int i = 1; i <= n; i ++){
    		s[i] = t[p[i]];
    	}
    	int res = 0;
    	for(int i = 1; i <= n; i ++){
    		for(int j = i + 1; j <= n; j ++){
    			res += check(i, j);
    			// cout << i << ' ' << j << ' ' << res << '\n';
    		}
    	}
    	// cout << res << ' ' << s << '\n';
    	// break;
    	mx = max(mx, res);
    	mp[res].push_back(s.substr(1));
    	// break;
    }
    while(next_permutation(p + 1, p + n + 1));
    cout << "mx: " << mx << '\n';
    cout << "sz: " << mp[mx].size() << '\n';
    // for(auto &str : mp[mx]) cout << str << '\n';
    cout << "find: ";
	s = ' ' + finddd;
	int res = 0;
	for(int i = 1; i <= n; i ++){
		for(int j = i + 1; j <= n; j ++){
			res += check(i, j);
			// cout << i << ' ' << j << ' ' << res << '\n';
		}
	}
	cout << res << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	sol();
	return 0;
}
