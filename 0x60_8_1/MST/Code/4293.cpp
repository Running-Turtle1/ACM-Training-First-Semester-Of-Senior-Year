#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;

struct Sphere{
	double x, y, z, r;
}sphere[110];

double eg[110][110];
double pow(double x){
	return x * x;
}
void cal(int x, int y){
	auto &[x1, y1, z1, r1] = sphere[x];
	auto &[x2, y2, z2, r2] = sphere[y];
	double dis = sqrt(pow(x1 - x2) + pow(y1 - y2) + pow(z1 - z2));
	if(dis <= r1 + r2){
		eg[x][y] = eg[y][x] = 0;
	}
	else{
		eg[x][y] = eg[y][x] = dis - r1 - r2;
	}
}

double d[110];
int st[110];
double prim(){
	double res = 0;
	for(int i = 1; i <= n; i ++){
		d[i] = 2e9;
		st[i] = 0;
	}
	d[1] = 0;
	for(int i = 1; i <= n; i ++){
		int t = -1;
		for(int j = 1; j <= n; j ++){
			if(!st[j] && (t == -1 || d[j] < d[t])){
				t = j;
			}
		}
		res += d[t];
		st[t] = 1;
		for(int j = 1; j <= n; j ++){
			d[j] = min(d[j], eg[t][j]);
		}
	}
	return res;
}

void solve(){
	for(int i = 1; i <= n; i ++){
		double a, b, c, r;
		cin >> a >> b >> c >> r;
		sphere[i] = {a, b, c, r};
    }
    for(int i = 1; i <= n; i ++){
    	for(int j = 1; j < i; j ++){
    		cal(i, j);
    	}
    	eg[i][i] = 0;
    }
    cout << fixed << setprecision(3) << prim() << '\n';
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	while(cin >> n, n){
		solve();
	}

	return 0;
}