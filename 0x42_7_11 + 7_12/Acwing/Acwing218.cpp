#include<bits/stdc++.h>
using namespace std;
#define int long long

double E[16][16][16][16][5][5];
int st[16][16][16][16][5][5];

int A, B, C, D;

bool equals(double a, double b){
	return fabs(a - b) < 1e-6;
}

double dfs(int a, int b, int c, int d, int x, int y){
	double &e = E[a][b][c][d][x][y];
	if(equals(e, -1.0) == false) return e;

	// 现在相当于手里面有什么牌
	int sa = a + (x == 0) + (y == 0);
	int sb = b + (x == 1) + (y == 1);
	int sc = c + (x == 2) + (y == 2);
	int sd = d + (x == 3) + (y == 3);

	// sum : 表示牌库里面有多少牌
	int sum = 54 - (a + b + c + d + (x != 4) + (y != 4));

	// 终点状态
	if(sa >= A && sb >= B && sc >= C && sd >= D){
		return e = 0;
	}

	// 初始化
	e = 1.0;
	if(a != 13){
		e += (13.0 - a) / sum * (dfs(a + 1, b, c, d, x, y));
	}
	if(b != 13){
		e += (13.0 - b) / sum * (dfs(a, b + 1, c, d, x, y));
	}
	if(c != 13){ 
		e += (13.0 - c) / sum * (dfs(a, b  , c + 1, d, x, y));
	}
	if(d != 13){
		e += (13.0 - d) / sum * (dfs(a, b, c, d + 1, x, y));
	}
	if(x == 4){
		double minState = 1e9;
		for(int i = 0; i < 4; i ++){
			minState = min(minState, dfs(a, b, c, d, i, y));
		}
		e += 1.0 / sum * minState;
	}
	if(y == 4){
		double minState = 1e9;
		for(int i = 0; i < 4; i ++){
			minState = min(minState, dfs(a, b, c, d, x, i));
		}
		e += 1.0 / sum * minState;
	}
	return e;
}

void solve(){
	cin >> A >> B >> C >> D;
	for(int i1 = 0; i1 < 16; i1 ++){
		for(int i2 = 0; i2 < 16; i2 ++){
			for(int i3 = 0; i3 < 16; i3 ++){
				for(int i4 = 0; i4 < 16; i4 ++){
					for(int j1 = 0; j1 < 5; j1 ++){
						for(int j2 = 0; j2 < 5; j2 ++){
							E[i1][i2][i3][i4][j1][j2] = -1.0;
						}
					}
				}
			}
		}
	}
	int s = (A > 13 ? A - 13 : 0) + (B > 13 ? B - 13 : 0) + (C > 13 ? C - 13 : 0) + (D > 13 ? D - 13 : 0);
	if(s > 2){
		cout << "-1.000\n";
	}
	else{
		cout << fixed << setprecision(3) << dfs(0, 0, 0, 0, 4, 4) << '\n';
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
