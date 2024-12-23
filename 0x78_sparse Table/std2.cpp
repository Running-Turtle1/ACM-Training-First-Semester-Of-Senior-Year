#include <bits/stdc++.h>
#define fi first
#define se second
#define int long long

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

const int N = 4e5 + 10;

int n, m;
int a[N], b[N];

bool check(int x) {
    std::vector<vector<int>> go(2 * n + 2, vector<int>(20, 2 * n + 1));
    for (int i = 1, j = 1; i <= 2 * n; i ++) {
        while (j <= 2 * n && b[j] - b[i - 1] < x) j ++;
        if (j > 2 * n) go[i][0] = j;
        else go[i][0] = j + 1;
    }
    for (int j = 1; j < 20; j ++)
        for (int i = 1; i <= 2 * n; i ++){
            go[i][j] = go[go[i][j - 1]][j - 1];
            cout << i << ' ' << j << ' ' << go[i][j - 1] << '\n';
        }
            
    for (int i = 1; i <= n; i ++) {
        int po = i;
        for (int j = 19; j >= 0; j --)
            if (m >> j & 1) po = go[po][j];
        if (po - 1 <= i + n - 1) return 1;
    }
    return 0;
}

signed main() {
    cin.tie(0);
    cout.tie(0);
    ios::sync_with_stdio(0);

    cin >> n >> m;
    for (int i = 1; i <= n; i ++)
        cin >> a[i], a[i + n] = a[i];
    for (int i = 1; i <= 2 * n; i ++) b[i] = b[i - 1] + a[i];


    cout << check(54) << '\n';
    return 0;

    int lo = 1, ro = 4e9, res;
    while (lo <= ro) {
        int mid = lo + ro >> 1;
        if (check(mid)) lo = mid + 1, res = mid;
        else ro = mid - 1;
    }

    cout << res << " ";
    int cnt = 0;
    std::vector<vector<int>> go(2 * n + 2, vector<int>(20, 2 * n + 1));
    for (int i = 1, j = 1; i <= 2 * n; i ++) {
        while (j <= 2 * n && b[j] - b[i - 1] < res) j ++;
        if (j > 2 * n) go[i][0] = j;
        else go[i][0] = j + 1;
    }
    for (int j = 1; j < 20; j ++)
        for (int i = 1; i <= 2 * n; i ++)
            go[i][j] = go[go[i][j - 1]][j - 1];
    for (int i = 1; i <= n; i ++) {
        int po = i;
        for (int j = 19; j >= 0; j --)
            if (m >> j & 1) po = go[po][j];
        if (po - 1 <= i + n - 1) cnt ++;
    }
    cout << n - cnt << endl;

    return 0;
}
