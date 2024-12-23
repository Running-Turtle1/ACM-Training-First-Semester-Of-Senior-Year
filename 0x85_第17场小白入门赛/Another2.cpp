#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k, x;
int a[100010];

void solve(){
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> x;
        a[x] ++;
    }
    vector<int> vc;
    for(int i = 1; i <= 100000; i ++){
        if(a[i]) vc.push_back(a[i]);
    }
    sort(vc.begin(), vc.end());
    vector<int> sum(vc.size());
    sum[0] = vc[0];
    for(int i = 1; i < vc.size(); i ++) sum[i] = vc[i] + sum[i - 1];
    auto ask = [&] (int l, int r){
        if(l > r) return 0LL;
        if(!l) return sum[r] - sum[l - 1];
        return sum[r];
    };
    int res = 0;
    for(int i = 0; i < vc.size() && (i + 1) <= k; i ++){
        if((i + 1) + ask(i + 1, vc.size() - 1) >= k) res = i + 1;
    }
    cout << res << '\n';
}

signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);

  int T = 1;
  // cin >> T;
  while (T --){
    solve();
  }

  return 0;
}