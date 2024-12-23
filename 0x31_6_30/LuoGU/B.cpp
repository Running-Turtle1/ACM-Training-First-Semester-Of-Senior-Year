#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
char g[1100][1100];

// bool isLetter(char x){
// 	return (islower(x) || isupper(x));
// }

int dx[4] = {1, -1, 0, 0};
int dy[8] = {0, 0, 1, -1};

void solve(){
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
     		cin >> g[i][j];       
        }
    }
    char mx = ' ';
    pair<int, int> pos;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
        	if(g[i][j] == '#') continue;
     		if(isupper(g[i][j])){
     			if(mx == ' ' || g[i][j] > mx){
     				mx = g[i][j];
     				pos = {i, j};
     			}
     		}       
        }
    }
    vector<pair<int, int> > Candidate;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
        	if(g[i][j] == '#') continue;
            if(g[i][j] == mx){
            	Candidate.push_back({i, j});
            }
        }
    }
    // for(auto &[x, y] : Candidate) cout << x << ' ' << y << '\n';
    char SecondMax = ' ';
    for(int i = 0; i < Candidate.size(); i ++){
    	auto [x, y] = Candidate[i];
    	for(int d = 0; d < 4; d ++){
    		int a = x + dx[d], b = y + dy[d];
    		// cout << "a b : " << a << ' ' << b << '\n';
    		if(a >= 1 && a <= n && b >= 1 && b <= m && g[a][b] != '#'){
    			// cout << "a b : " << a << ' ' << b << '\n';
    			if(SecondMax == ' ' || g[a][b] > SecondMax){
    				SecondMax = g[a][b];
    			}
    		}
    	}
    }
    if(SecondMax == ' ' || SecondMax == mx){
    	cout << mx << '\n';
    }
    else{
    	cout << mx << SecondMax;
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
