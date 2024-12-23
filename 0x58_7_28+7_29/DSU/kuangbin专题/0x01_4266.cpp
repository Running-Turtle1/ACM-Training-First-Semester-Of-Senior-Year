#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1002;

int n, d;
pair<int, int> coordinate[N];
bool st[N];
int p[N];
bool isAdjacent[N][N];
int find(int x){
	return (x == p[x] ? x : p[x] = find(p[x]));
}
void merge(int x, int y){
	x = find(x);
	y = find(y);
	if(x != y){
		p[x] = y;
	}
}
void solve(){
	cin >> n >> d;
	for(int i = 1; i <= n; i ++){
		p[i] = i;
		cin >> coordinate[i].first >> coordinate[i].second;
    }
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= n; j ++){
     		auto& [x1, y1] = coordinate[i];
     		auto& [x2, y2] = coordinate[j];
     		if(pow(x1 - x2, 2LL) + pow(y1 - y2, 2LL) <= d * d){
     			isAdjacent[i][j] = true;
     		}
     		else{
     			isAdjacent[i][j] = false;
     		}
        }
    }
    char op;
    int x, y;
    while(cin >> op){
    	if(op == 'O'){
    		cin >> x;
    		st[x] = true;
    		for(int i = 1; i <= n; i ++){
    			if(isAdjacent[x][i] && st[i]){
    				merge(x, i);
    			}
    		}
    	}
    	else{
    		cin >> x >> y;
    		if(st[x] && st[y] && find(x) == find(y)){
    			cout << "SUCCESS\n";
    		}
    		else{
    			cout << "FAIL\n";
    		}
    	}

    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	solve();

	return 0;
}