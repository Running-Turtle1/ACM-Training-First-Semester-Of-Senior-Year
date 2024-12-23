#include<bits/stdc++.h>
using namespace std;
#define int long long

double E[16][16][16][16][4];
int st[16][16][16][16][4]; // 是否已经被记忆搜索过了

double dfs(int a, int b, int c, int d, int e){
	if(st[a][b][c][d][e]) return E[a][b][c][d][e];
	if(!a && !b && !c && !d && !e){
		st[a][b][c][d][e] = 1;
		return E[a][b][c][d][e] = 0;
	}

	// 上一个状态牌堆里面有多少牌
	int s = a + b + c + d + (e & 1) + (e >> 1 & 1); // 当前手里
	s = 54 - (s - 1);

	// 抽一张 a 来到当前状态的的概率
	if(a){
		double p = (13.0 - (a - 1)) / (1.0 * s);
		E[a][b][c][d][e] += p * dfs(a - 1, b, c, d, e);
	}
	// 抽一张 b 来到当前状态的概率
	if(b){	
		double p = (13.0 - (b - 1)) / (1.0 * s);
		E[a][b][c][d][e] += p * dfs(a, b - 1, c, d, e);
	}
	// 抽一张 c 来到当前状态的概率
	if(c){
		double p = (13.0 - (c - 1)) / (1.0 * s);
		E[a][b][c][d][e] += p * dfs(a, b, c - 1, d, e);
	}
	// 抽一张 d 来到当前状态的概率
	if(d){
		double p = (13.0 - (d - 1)) / (1.0 * s);
		E[a][b][c][d][e] += p * dfs(a, b, c, d - 1, e);
	}
	// 抽到小王
	if(e >> 1 & 1){
		double p = 1.0 / s;
		int ne = e ^ (2);
		E[a][b][c][d][e] += p * dfs(a, b, c, d, ne);
	}
	// 抽到大王
	if(e >> 1 & 1){
		double p = 1.0 / s;
		int ne = e ^ 1;
		E[a][b][c][d][e] += p * dfs(a, b, c, d, ne);
	}
	st[a][b][c][d][e] = 1; 
	return E[a][b][c][d][e];
}

void solve(){
	int a, b, c, d, e;
	cin >> a >> b >> c >> d >> e;
	dfs(a, b, c, d, e);
	double resMin = 2e9;
	resMin = min(resMin, dfs(a, b, c, d, 0));
	resMin = min({resMin, dfs(a - 1, b, c, d, 1), dfs(a, b, c, d, 2)});
	resMin = min({resMin, dfs(a, b, c, d, 1), dfs(a, b, c, d, 2)});
	resMin = min({resMin, dfs(a, b, c, d, 1), dfs(a, b, c, d, 2)});
	resMin = min({resMin, dfs(a, b, c, d, 1), dfs(a, b, c, d, 2)});
	if(st[a][b][c][d][e]){
		cout << fixed << setprecision(3) << E[a][b][c][d][e] << '\n';	
	}
	else{
		cout << "-1.000";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
