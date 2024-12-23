#include <bits/stdc++.h>
#define int long long
using namespace std;
map<int, int> mp;
int R, cnt;
void solve(int n, int k) {
    for (int i = 2; i * i * i <= n; ++i) {
        int t = i * i, m = 2;
        while (t <= n / i) {
            t *= i, m++;
            if (m < k || mp[t]) continue;
            else {
                if ((int)sqrtl(t) * sqrtl(t) == t) R++;
                cnt++, mp[t] = 1;
            }
        }
    }
}
signed main() {
    int n;
    cin >> n;
    solve(n, 2);
    cout << (int)sqrtl(n) - R + cnt << '\n';
}