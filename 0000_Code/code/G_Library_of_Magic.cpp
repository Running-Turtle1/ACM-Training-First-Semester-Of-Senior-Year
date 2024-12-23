// #include<bits/stdc++.h>
// using namespace std;
// // 以下两种写法是一个意思 : 
// // cout << endl;
// // cout << '\n', fflush(stdout);
// int main(){
//     int l=1, r=1000000;
//     while(l<r){
//         int mid=l+r+1>>1;
//         cout<<mid<<endl;

//         string response;
//         cin>>response;
//         if(response==">=") l=mid;
//         else r=mid-1;
//     }    
//     cout<<"! " << l << endl;

//     return 0;
// } 

#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int n;
    cin >> n;

    int s = 0;
    vector<int> vc;
    function<void(int, int, int)> find = [&] (int l, int r, int x){
        if(l == r || s == 2) {
            vc.push_back(x);
            return ;
        }
        int res1, res2;
        int mid = l + r >> 1;
        cout << "xor " << l << ' ' << mid << endl;
        cin >> res1;
        res2 = x ^ res1;
        if(res1 && res2) {
            ++ s;
            find(l, mid, res1);
            find(mid + 1, r, res2);
        }
        else if(res1){
            find(l, mid, res1);
        }
        else if(res2){
            find(mid + 1, r, res2);
        }
    };
    int t;
    cout << "xor " << 1 << ' ' << n << endl;
    cin >> t;
    if(t) find(1, n, t);
    else{
        int res, t = 1;
        while(t <= n) t <<= 1;
        t >>= 1;
        cout << "xor " << t << ' ' << n << endl;
        cin >> res;
        if(res){
            s = 1;
            find(t, n, res);
            find(1, t - 1, res);
        }
        else{
            while(true){
                t >>= 1;
                cout << "xor " << t << ' ' << t * 2 - 1 << endl;
                cin >> res;
                if(!res) continue ;
                s = 1;
                find(t, t * 2 - 1, res);
                find(1, t - 1, res);
                break;
            }
        }
    }
    cout << "ans ";
    for(auto &nx : vc) cout << nx << ' ';
    cout << endl;
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int T = 1;
	cin >> T;
	while (T --){
		solve();
	}

	return 0;
}