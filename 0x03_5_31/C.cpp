#include<bits/stdc++.h>
using namespace std;
#define int long long

int n, a[500010];
int s0 = 0, s1 = 0;
void solve(){
    cin >> n;
    for(int i = 1; i <= n; i ++){
        cin >> a[i];
        if(a[i]) s1 ++;
        else s0 ++;
    }

    if(n == 1){
        cout << "-1";
        return ;
    }
    
    // 头尾相等
    if(a[1] == a[n]){
        cout << 1;
        return ;
    }
    
    // 落单 0 1
    // if((s0 == 1) || (s1 == 1)){
    //     cout << "-1\n";
    //     return ;
    // }
    
    
    // 换成 0 开头
    if(a[1] == 1){
        for(int i = 1; i <= n; i ++){
            a[i] = 1 - a[i];
        }
    }
    
    // 看看都找到一个 1 满足 a[i]=1 i!=n a[i-1]=0
    for(int i = 2; i <= n - 2; i ++){
        if(!a[i] && a[i+1]){
            cout<<"2";
            return ;
        }
    }
    cout<<"-1";

}
// 0101
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    solve();
    return 0;
}