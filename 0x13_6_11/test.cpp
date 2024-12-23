#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N = 2000 + 5;
int bell[N][N];

void initBell(int n) { // 构造贝尔三角形
  bell[1][1] = 1;
  for (int i = 2; i <= n; i++) {
    bell[i][1] = bell[i - 1][i - 1];
    for (int j = 2; j <= i; j++)
      bell[i][j] = bell[i - 1][j - 1] + bell[i][j - 1];
  }
}

int B(int n){ // 返回贝尔数
  return bell[n + 1][1];
}

void solve(){
  initBell(10);
  for(int i = 0; i <= 6; i ++){
      cout << "B" << i << ": ";
      cout << B(i) << '\n';
  }
}

signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0); 
  solve();
  return 0;
}