#include <bits/stdc++.h>
using namespace std;

int solution(int m, std::string s) {
  int n = s.size();
  s = ' ' + s;
  vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));
  int ans = 0;
  auto chmax = [&](int &x, int y) {
    if (x < y)
      x = y;
  };
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      if (s[i] == 'C') {
        if (i >= 3 && s.substr(i - 2, 3) == "UCC") // UCC
        {
          chmax(f[i][j], f[i - 3][j] + 1);
        } else if (i >= 3 && s.substr(i - 2, 3) == "CCC" && j) { // CCC 替换
          chmax(f[i][j], f[i - 3][j - 1] + 1);
        } else if (i >= 2 && s[i - 1] == 'C' && j) { // CC 插入 U
          chmax(f[i][j], f[i - 2][j - 1] + 1);
        } else if (i >= 2 && s[i - 1] == 'U' && j) { // UC
          chmax(f[i][j], f[i - 2][j - 1] + 1);
        }
      } else {
        if (j >= 2)
          chmax(f[i][j], f[i - 1][j - 2] + 1);
      }
      chmax(f[i][j], f[i-1][j]);
      if(j>=2)chmax(f[i][j], f[i-1][j-2]+1);
      ans = max(ans, f[i][j] + (m - j) / 3);
    }
  }  
  return ans; // Placeholder
}

int main() { 
//   std::cout << (solution(3, "CUUUCUCUUUUCU")) << std::endl;
std::cout << (solution(9, "CUUUUC")) << std::endl;
  return 0;
}
