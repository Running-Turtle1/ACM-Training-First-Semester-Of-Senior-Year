#include<bits/stdc++.h>
using namespace std;
#define int long long

int n;
string s;

bool check(int a, int b){
	vector<vector<int> > matrix(a + 1, vector<int> (b + 1, 0));
	for(int i = 1; i <= a; i ++){
		for(int j = 1; j <= b; j ++){
			matrix[i][j] = s[(i - 1) * a + j] - '0';
		}
	}
	for(int i = 1; i <= b; i ++){
		if(matrix[1][i] != 1 || matrix[a][i] != 1) return false;
	}
	for(int i = 1; i <= a; i ++){
		if(matrix[i][1] != 1 || matrix[i][b] != 1) return false;
	}
	for(int i = 2; i < a; i ++){
		for(int j = 2; j < b; j ++){
			if(matrix[i][j] != 0) return false;
		}
	}
	return true;
}

void solve(){
	cin >> n >> s;
	s = ' ' + s;
	
	int x = sqrt(n);
	if(n % x != 0){
		cout << "No\n";
		return ;
	}
	if(x != n / x){
		cout << "No\n";
		return ;
	}
	int y = n / x;
		if(check(x, y)){
			cout << "Yes\n";
			return ;
		}
	// }
	cout << "No\n";
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}