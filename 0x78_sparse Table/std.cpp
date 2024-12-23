#include <bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n, k, l = 1, r = 0;
    cin >> n >> k;
    vector<int> a(n * 2);
    for(int i = 0; i < n; i ++){
        cin >> a[i];
        r += a[i];
    }
    for(int i = 0; i < n; i ++){
        a[n + i] = a[i];
    }

    const int INF = 2 * n + 1;
    vector<vector<int> > f(n * 2, vector<int> (33, 0));
    auto check = [&] (int x) {
        int sum = 0;
        for(int l = 0, r = 0; l < n * 2; l ++){
            while(r < n * 2 && sum < x){
                sum += a[r];
                r ++;
            }
            if(sum >= x) f[l] = r;
            else f[l] = INF;
        }
    };
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);

        for (int i = 0; i < n; i++) {
            fk[i] = i;
        }
        int t = k;
        while (t) {
            if (t & 1) {
                for (int i = 0; i < n; i++) {
                    if (fk[i] < n * 2) {
                        fk[i] = f[fk[i]];
                    }
                }
            }
            for (int i = 0; i < n * 2; i++) {
                if (f[i] < n * 2) {
                    f[i] = f[f[i]];
                }
            }
            t >>= 1;
        }
        for (int i = 0; i < n; i++) {
            if (fk[i] <= n + i) {
                return true;
            }
        }
        return false;
    };
    while (l <= r) {
        int mid = (l + r) / 2;
        if (ck(mid)) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    ck(r);
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += fk[i] <= n + i;
    }
    cout << r << ' ' << n - cnt << '\n';
}