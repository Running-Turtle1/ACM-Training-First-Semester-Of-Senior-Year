#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, k, a[100010];
int b[100010];
int cnt[100010];
int s[100010];

void solve(){
    cin >> n >> k;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + n + 1);
    int szb = unique(b + 1, b + n + 1) - b - 1;
    for(int i = 1; i <= n; i ++){
        a[i] = lower_bound(b + 1, b + szb + 1, a[i]) - b;
        cnt[a[i]] ++;
    }
    // for(int i = 1; i <= n; i ++){
    //     cout<<a[i]<<" \n"[i==n];
    // }
    sort(cnt + 1, cnt + n + 1);

    // int st = 1;
    // while(st <= n && cnt[st] == 0) st ++; // 找到 st 位置
    
    for(int i = 1; i <= n; i ++){
        s[i] = s[i - 1] + cnt[i];
    }
    s[n+1]=s[n];


    // 对于 cnt 数组, [st, n] 逐渐增大
    // for(int i=1; i<=n; i++){
    //     cout<<cnt[i]<<" \n"[i==n];
    // }
    int res=n;
    for(int l = 0; l + k <= n; l ++){
        int r = l + k ;
        int tmp = 0;
        //prev
        int p1 = prev(lower_bound(cnt + 1, cnt + n + 1, l)) - cnt;
        tmp += s[p1];
        int p2 = lower_bound(cnt + 1, cnt + n + 1, r) - cnt;
        tmp += (s[n] - s[p2-1]) - (n - p2 + 1) * r;
        // if(l==5){
        //     cout<<p1<<' '<<p2<<'\n';
        // }
        // if(tmp==0||l==4){
        //     cout<<"WA: "<<l<<' '<<r<<'\n';
        //     cout<<p1<<' '<<p2<<'\n';
        // }
        res = min(res, tmp);
    }    
    cout << res << '\n';
    // for(auto &x : s) cnt[get(x)] ++;
    // // for(int i = 0; i <= 61; i ++){
    // // 	cout << cnt[i] << " \n"[i == 61];
    // // }
    // int res = n;
    // for(int l = 0; l <= n - k; l ++){
    // 	int r = l + k;
    // 	// [l, r]
    // 	int tmp = 0;
    // 	for(int j = 0; j < 62; j ++){
    // 		if(cnt[j] == 0) continue;
    // 		if(cnt[j] >= l && cnt[j] <= r) continue;
    // 		if(cnt[j] < l) tmp += cnt[j];
    // 		if(cnt[j] > r) tmp += -r + cnt[j];
    // 	}
    // 	res = min(res, tmp);
    // }
    // cout << res << '\n';
}
// 枚举字符串出现次数范围, [i, i+k], 因为数据太少直接算
// 把所有非 0 出现次数排序, 二分之后, 所有 < l 的全部删除, > r 的前缀和处理
// 1 2 3 5
signed main(){
    freopen("array.in", "r", stdin);
    freopen("array.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}