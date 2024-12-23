#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int p[510], d[510];

int find(int x){
	if(x == p[x]) return x;
	int t = find(p[x]);
	(d[x] += d[p[x]]) %= 3;
	return p[x] = t;
}

void solve(){
	while(cin >> n >> m){
		int res = -1;
		bool fg = false;
	    int p1 = -1, p2 = -1;
	    for(int i = 0; i < n; i ++){
	        p[i] = i;
	        d[i] = 0;
	    }
	    for(int i = 0; i < m; i ++){
	        int a, b, dis;
	        {
	            string s;
	            cin >> s;
	            int pos = -1;
	            for(int j = 0; j < s.size(); j ++){
	                if(isdigit(s[j]) == false){
	                    pos = j;
	                    break;
	                }
	            }
	            a = stoi(s.substr(0, pos));
	            b = stoi(s.substr(pos + 1));
	            if(s[pos] == '<') dis = 2;
	            else if(s[pos] == '>') dis = 1;
	            else dis = 0;
	        }
	        int pa = find(a), pb = find(b);
	        cout << i << ' ' << a << ' ' << b << ' ' << dis << '\n';
	        cout << pa << ' ' << pb << '\n';
	        if(pa == pb){ 
	            if(((d[b] - d[a]) % 3 + 3) % 3 != dis){
	            	if(p1 == -1 && p2 == -1){
	            		p1 = a;
	            		p2 = b;
	            	}
	            	else{
	            		set<int> t = {p1, p2, a, b};
	            		multiset<int> t_ = {p1, p2, a, b};
	            		if(t.size() == 4){
	            			fg = true;
	            		}
	            		else if(t.size() == 3){
	            			if(res == -1){
	            				if(t_.count(p1) == 2) res = p1;
	            				if(t_.count(p2) == 2) res = p2;
	            				if(t_.count(a) == 2) res = a;
	            				if(t_.count(b) == 2) res = b;
	            			}
	            			else{
	            				fg = true;
	            			}
	            		}
	            		else{
	            			continue ;
	            		}
	            	}
	                cout << "冲突: " << a << ' ' << b << '\n';
	            }
	        }
	        else{
	            p[pb] = pa;
	            d[pb] = ((d[a] + dis - d[b]) % 3 + 3) % 3;
	        }
	        cout << "第" << i << "次合并之后:\n";
	        for(int i = 0; i < n; i ++){
                cout << i << " -> " << find(i) << '\n';
            }
	    }
	    int sum = 0, pl = 0;
	    for(auto& [x, y] : mp){
	        cout << x << ' ' << y << '\n';
	        if(y >= 2){
	            sum ++;
	            pl = x;
	        }
	    }
		if(sum == 1){
			cout << "player " << pl << " can be determined to be the judge after " << res << " lines";
		}
		else if(sum >= 2){ // fg
			cout << "Impossible\n";
		}
		else if(sum == 0){
			cout << "Can not determine\n";
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
