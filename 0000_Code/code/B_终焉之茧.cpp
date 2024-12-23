#include "bits/stdc++.h"
using namespace std;
using i64 = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    i64 f;
    cin >> f;
    if (!f) {
        return 0;
    }

    int sx = 0, sy = 0;
    auto get = [&](int x, int y) {
        cout << x - sx << ' ' << y - sy << endl;
        sx = x, sy = y;
        i64 f;
        cin >> f;
        if (!f) {
            exit(0);
        }
        return f;
    };

    int l0 = -1000, r0 = 1000, l1 = -1000, r1 = 1000;
    i64 f0 = get(l0, l1), f1 = get(r0, l1);
    while (l0 < r0) {
        int m = (l0 + r0) >> 1;

        if (f0 > f1) {
            l0 = m + 1;
            f0 = get(l0, l1);
        } else {
            r0 = m;
            f1 = get(r0, l1);
        }
    } 

    f0 = get(l0, l1), f1 = get(r0, r1);
    while (l1 < r1) {
        int m = (l1 + r1) >> 1;
        
        if (f0 > f1) {
            l1 = m + 1;
            f0 = get(l0, l1);
        } else {
            r1 = m;
            f1 = get(r0, r1);
        }
    }

    return 0;
}