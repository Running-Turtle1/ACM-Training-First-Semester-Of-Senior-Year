#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, m;
int const N = 1e5 + 10;
int l[N], r[N], a[N], ans[N];
 
void MonotoneStack(int n, int a[]){
    stack<int> q;
    // 输出 a[i] 左边第一个比 a[i] 小的元素的下标
    for(int i = 1; i <= n; i ++){
        while(q.size() && a[i] <= a[q.top()]){
            q.pop();
        }
        if(q.size()) cout << q.top() << ' ';
        else cout << "-1 ";
        q.push(i);
    }
    cout << '\n';
    while(q.size()) q.pop();
    // 输出 a[i] 右边第一个比 a[i] 小的元素的下标
    for(int i = n; i >= 1; i --){
        while(q.size() && a[i] <= a[q.top()]){
            q.pop();
        }
        if(q.size()) cout << q.top() << ' ';
        else cout << "-1 ";
        q.push(i);
    }
}

void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
    }
    MonotoneStack(n, a);
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}