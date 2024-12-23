#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 3e5 + 10;
int n, a[N], sum[N], sumr[N], sum1[N];

int askr1(int l, int r){
    if(l > r) return 0LL;
    return sum1[r] - sum1[l - 1];
}

int askrow(int l, int r){
    if(l > r) return 0LL;
    return sumr[r] - sumr[l - 1];
}

int ask(int row, int l, int r){
    if(row == 1) return askr1(l, r); // 特判
    if(l > r) return 0LL;
    int d = row - 1;
    return askr1(l + d, r + d) - askr1(d, d) * (r - l + 1);
}

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        a[i] += a[i - 1];
        sum1[i] = sum1[i - 1] + a[i];
    }

    sumr[1] = askr1(1, n);
    for(int i = 2; i <= n; i ++){
        sumr[i] = sumr[i - 1] - ask(i - 1, 1, 1) * (n - (i - 1) + 1);
    }

    for(int i = 1; i <= n; i ++){
        sumr[i] += sumr[i - 1];
    }
    
    auto f = [&] (int r){
        return r * (2 * n - r + 1) / 2;
    };
    auto findPos = [&] (int x){
        pair<int, int> p;
        int l = 1, r = n;
        while(l < r){
            int mid = l + r >> 1;
            if(f(mid) >= x) r = mid;
            else l = mid + 1;
        }
        p.first = l;
        p.second = x - (f(r - 1) + 1) + 1;
        return p;
    };

    int q;
    cin >> q;
    while(q --){
        int l, r;
        cin >> l >> r;
        auto [r1, c1] = findPos(l);
        auto [r2, c2] = findPos(r);
        // cout << r1 << ' ' << c1 << '\n'; //
        // cout << r2 << ' ' << c2 << '\n';
        int ans = askrow(r1 + 1, r2 - 1);
        if(r1 == r2) ans += ask(r1, c1, c2);
        else ans += ask(r1, c1, n - r1 + 1) + ask(r2, 1, c2);
        cout << ans << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
