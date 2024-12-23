#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3e5 + 10;

int n;
vector<int> e[N];
int w[N], dp[N][2];

void dfs1(int u, int fa) {
    dp[u][1] = w[u];
    for (auto v : e[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

void dfs2(int u, int fa) {
    for (auto v : e[u]) {
        if (v == fa) continue;

        // 保存原始值
        int original_dp_v_0 = dp[v][0];
        int original_dp_v_1 = dp[v][1];

        // 重新计算 dp[v][0] 和 dp[v][1]，将 v 视为根
        dp[u][0] -= max(dp[v][0], dp[v][1]);
        dp[u][1] -= dp[v][0];
        dp[v][0] += max(dp[u][0], dp[u][1]);
        dp[v][1] += dp[u][0];

        // 递归
        dfs2(v, u);

        // 恢复原始值
        dp[v][0] = original_dp_v_0;
        dp[v][1] = original_dp_v_1;
    }
}

void solve() {
    int sumValue = 0;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        sumValue += w[i];
        dp[i][0] = dp[i][1] = 0;
        e[i].clear();
    }
    for (int i = 1; i < n; ++i) {
        int u, v;
        cin >> u >> v;
        e[u].push_back(v);
        e[v].push_back(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);

    int result = 0;
    for (int i = 1; i <= n; ++i) {
        result = max(result, max(dp[i][0], dp[i][1]));
    }
    cout << (sumValue << 1) - result << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int T = 1;
    cin >> T;
    while (T--) {
        solve();
    }

    return 0;
}
