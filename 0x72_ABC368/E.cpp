#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int N, M, X0;
    cin >> N >> M >> X0;
    
    vector<int> A(M), B(M), S(M), T(M);
    for (int i = 0; i < M; i++) {
        cin >> A[i] >> B[i] >> S[i] >> T[i];
        A[i]--;
        B[i]--;
    }
    
    vector<array<int, 3>> e(2 * M);
    for (int i = 0; i < M; i++) {
        e[2 * i] = {S[i], 1, i}; // 查询用 1
        e[2 * i + 1] = {T[i], 0, i}; // 更新用 0
    }
    
    sort(e.begin(), e.end());
 
    vector<int> X(M);
    vector<int> tm(N); // 表示 b[i] 的最大的 T[i] + X[i]
    X[0] = X0;
    for (auto [t, o, i] : e) {
        if (o == 1) { // 查询 X[i]
            X[i] = max(X[i], tm[A[i]] - S[i]);
        } else { // 
            tm[B[i]] = max(tm[B[i]], T[i] + X[i]);
        }
    }
    
    for (int i = 1; i < M; i++) {
        cout << X[i] << " \n"[i == M - 1];
    }
    
    return 0;
}