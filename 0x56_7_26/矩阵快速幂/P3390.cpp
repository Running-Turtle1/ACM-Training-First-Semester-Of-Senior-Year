#include<bits/stdc++.h>
using namespace std;
#define int long long

typedef vector<vector<long long> > matrix;
int const mod = 1e9 + 7;
// 矩阵乘法
matrix multiply(matrix &x, matrix &y){
	int n = x.size();
	int m = y[0].size();
	int c = x[0].size();
	matrix res(n, vector<long long> (m, 0));
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < m; j ++){
			for(int k = 0; k < c; k ++){
				res[i][j] = (res[i][j] + x[i][k] * y[k][j]) % mod;
			}
		}
	}
	return res;
}
// 矩阵快速幂, 要求 x 必须是方阵
matrix matrixPower(matrix &x, int k){
	int n = x.size();
	matrix res(n, vector<long long> (n, 0));
	for(int i = 0; i < n; i ++){
		res[i][i] = 1;
	}
	while(k){
		if(k & 1) res = multiply(res, x);
		k >>= 1;
		x = multiply(x, x);
	}
	return res;
}

void solve(){
	int n, k;
	cin >> n >> k;
	matrix A(n, vector<long long> (n, 0));
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < n; j ++){
			cin >> A[i][j];
		}
	}
	A = matrixPower(A, k);
	for(int i = 0; i < n; i ++){
		for(int j = 0; j < n; j ++){
			cout << A[i][j] << " \n"[j == n - 1];
		}
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
