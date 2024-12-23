#include<bits/stdc++.h>
using namespace std;
#define int long long

typedef vector<vector<long long> > matrix;
int const mod = 1e9 + 7;
matrix multiply(matrix &x, matrix &y){
    int n = x.size();
    int m = y[0].size();
    int c = x[0].size();
    matrix res(n, vector<long long> (m, 0));
    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            for(int k = 0; k < c; k ++){
                res[i][j] = (res[i][j] + x[i][k] * y[k][j] % mod) % mod;
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

void fib(int n){
    if(n == 1 || n == 2){
        cout << "1\n";
        return ;
    }
    matrix A(2, vector<long long>(2, 0));
    A[0][0] = A[0][1] = A[1][0] = 1;
    A = matrixPower(A, n - 2); 
    matrix Fib(1, vector<long long> (2, 1));
    Fib = multiply(Fib, A);
    cout << Fib[0][0] << '\n';
}

int n, k;

int f[1000010];

int res[1000010];



void solve(int cnt){
	int p = -1;
	// cin >> n >> k;
	// n = 100;
	// k = cnt;
	cin >> n >> k;
	if(res[k] == -1){
		f[1] = f[2] = 1;
		for(int i = 3;  ; i ++){
			f[i] = (f[i - 1] + f[i - 2]) % k;
			// cout << i << ' ' << f[i] << '\n';
			if(f[i] == 0){
				res[k] = i;
				break;
			}
	    }
	}
    
    // for(int i = 1; i <= n; i ++){
    // 	cout << i << ' ' << f[i] << '\n';
    // }
    // cout << p << '\n';
    cout << res[k] * (n % mod) % mod << '\n';
    // p : 第一次出现 0 的位置
    // 第 n 次出现 : f[np]
    // fib(p * k);
}
// k = 1, 1
// k = 2, 3 次一个 0
// k = 3, 4 次一个 0
// k = 4, 6 次一个 0
// k = 5, 5 次一个 0
// k = 6, 10
// k = 7, 8
// k = 8, 6

// 1,1,2,3,5,8,13,21,34

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	memset(res, -1, sizeof res);
	res[1] = 1;
	// res[1] = 1;
	// // for(int k = 2; k <= 1000000; k ++){
	// // 	if(k % 10000==0)cout<<k<<'\n';
	// // 	if(res[k] != -1) continue; 
		
	// // 	f[1] = f[2] = 1;
	// // 	for(int i = 3; ; i ++){
	// // 		f[i] = (f[i-1] + f[i-2]) % k;
	// // 		if(f[i]==0){
	// // 			res[k] = i;
	// // 			for(int j = k; j <= 1000000; j += k){
	// // 				res[j] = i;
	// // 			}
	// // 			break;
	// // 		}
	// // 	}
	// // }
	// for(int i = 1; i <)

	int T = 1;
	cin >> T;
	for(int i = 1; i <= T; i ++){
		solve(i);
    }

	return 0;
}