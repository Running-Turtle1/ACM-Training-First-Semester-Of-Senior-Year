#include<bits/stdc++.h>
using namespace std;
#define int long long

vector<int> divisorA;
vector<int> divisorC;

int a, b, c;

void init(int x, vector<int> &v, int fg){
    for(int i = 1; i <= x / i; i ++){
        if(x % i == 0){
            v.push_back(i);
            if(fg) v.push_back(-i);
            if(i != x / i){
                v.push_back(x / i);
                if(fg) v.push_back(-(x / i));
            }
        }
    }
}

void solve(){
    divisorA.clear();
    divisorC.clear();
    cin >> a >> b >> c;
    if(c == 0){
        int a1 = __gcd(a,b), b1 = 0;
        int a2 = a / a1, b2 = b / a1;
//         int b1 = 0;
//             int b2 = 0;
//         for(int i = 0; i < divisorA.size(); i ++){
//             int a1 = divisorA[i];
//             int a2 = a / a1;
//             if(b == a1 * b2 + b1 * a2){
                cout << a1 << ' ' << b1 << ' ' << a2 << ' ' << b2 << '\n';
// //                 cout << "YES\n";
//                 return ;
//             }
//             cout << "NO\n";
//         }
        return ;
    }
    init(abs(a), divisorA, 1);
    init(abs(c), divisorC, 1);
    // for(auto x : a){
    //     cout <<
    // }
    for(int i = 0; i < divisorA.size(); i ++){
        int a1 = divisorA[i];
        int a2 = a / a1;
        for(int j = 0; j < divisorC.size(); j ++){
            int b1 = divisorC[j];
            int b2 = c / b1;
            // if(a1 == 2 && a2 == 2){
            //     cout << b1 << ' ' << b2 << '\n';
            // }
            if(b == a1 * b2 + b1 * a2){
                cout << a1 << ' ' << b1 << ' ' << a2 << ' ' << b2 << '\n';
//                 cout << "YES\n";
                return ;
            }
        }
    }
    cout << "NO\n";
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