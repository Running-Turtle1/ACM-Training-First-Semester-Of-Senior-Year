
#include <bits/stdc++.h>
using namespace std;

// Edit your code here
int solution(int n, int w, const std::vector<int> &array) {
    vector<int> a(array);
    for(auto &nx : a){
        nx = w - nx;
        if(nx < 0) return 0;
    }
    a.push_back(0);
    for(int i = n; i >= 1; i --){
        a[i] -= a[i - 1];
        if(abs(a[i]) > 1) return 0;
    }
    if(abs(a[0]) > 1) return 0;
    
    vector<vector<int> > f(n + 1, vector<int> (n + 1, 0));
    if(a[0] == 1) f[0][1] = 1;
    else if(a[0] == 0) f[0][0] = 1;

    for(int i = 1; i <= n; i ++){
        for(int j = 0; j <= n + 1; j ++){
            if(a[i] == 0) {
                f[i][j] = f[i - 1][j] + j * f[i - 1][j];
            }
            if(j && a[i] > 0){
                f[i][j] = f[i - 1][j - 1];
            }
            if(j + 1 <= n + 1 && a[i] < 0){
                f[i][j] += f[i - 1][j + 1];
            }
        }   
    }
    return max(f[n][0], f[n][1]);
}

int main() {
    cout << solution(2, 2, {1, 1}) << '\n';
    cout << solution(1, 1, {1}) << '\n';
    cout << solution(3, 5, {5, 4, 5}) << '\n';
    return 0;
}
