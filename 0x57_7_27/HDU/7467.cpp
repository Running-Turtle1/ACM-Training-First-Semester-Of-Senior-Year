#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

struct people{
	int x, y;
	pair<int, int> d; 
}p[200010];

int f(int t){
	int xmax, ymax, xmin, ymin;
	xmax = ymax = -2e9;
	xmin = ymin = 2e9;
	for(int i = 1; i <= n; i ++){
		int nx = p[i].x + p[i].d.first * t;
		int ny = p[i].y + p[i].d.second * t;
		xmax = max(xmax, nx);
		xmin = min(xmin, nx);
		ymax = max(ymax, ny);
		ymin = min(ymin, ny);
	}
	if(!t){
		cout << xmin << ' ' << xmax << '\n';
		cout << ymin << ' ' << ymax << '\n';
	}
	return (xmax - xmin) * 2LL + (ymax - ymin) * 2LL;
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> p[i].x >> p[i].y;
		char x;
		cin >> x;
		if(x == 'E'){
			p[i].d = {1, 0};
		}
		else if(x == 'W'){
			p[i].d = {-1, 0};
		}
		else if(x == 'N'){
			p[i].d = {0, 1};
		}
		else{
			p[i].d = {0, -1};
		}
    }
    int l = 0, r = 1e9;
    while(r - l >= 3){
    	int midl = l + (r - l) / 3;
    	int midr = r - (r - l) / 3;
    	int fl = f(midl), fr = f(midr);
    	if(fl < fr){
    		r = midr;
    	}
    	else{
    		l = midl;
    	}
    }
    int mn = LLONG_MAX;
    for(int i = l; i <= r; i ++){
    	mn = min(mn, f(i));
    }
    cout << mn << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
