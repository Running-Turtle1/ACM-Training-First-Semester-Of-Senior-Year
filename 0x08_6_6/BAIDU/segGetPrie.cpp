#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
#define int long long


int const N = 1e6 + 10;
int cnt = 0; // [a, b] 中的质数数量
bool isPrimeRes[N]; // [a, b] 的表
bool isPrimeBig[N]; // [2, √b] 的表
int prime[N]; // 质数表

// 对 [a, b) 筛质数 
void segmentSieve(int a, int b){
    for(int i = 0; i * i < b; i ++){
        isPrimeBig[i] = true;
    }
    for(int i = 0; i < b - a; i ++){
        isPrimeRes[i] = true;
    }

    // 对 [2, √b] 埃氏筛, 同时用最小质因数筛 [a, b) 区间
    for(int i = 2; i * i < b; i ++){
        if(isPrimeBig[i]){ // 如果 i 是质数
            // [2, √b] 的表
            for(int j = 2 * i; j * j < b; j += i){ 
                isPrimeBig[j] = false;
            }
            // [a, b] 的表, 首先找到第一个 >= a 的数 j, 且 j % i == 0
            for(int j = max((a + i - 1) / i * i, 2LL); j < b; j += i){
                isPrimeRes[j - a] = false; // 映射区间
            }
        }
    }

    for(int i = 0; i < b - a; i ++){
        if(isPrimeRes[i]){
            prime[cnt ++] = i + a;
        }
    }
}

// 求 [a, b]
void solve(){
    int a, b;
    while(cin >> a >> b){
        if(a == 1) a = 2;
        cnt = 0;
        segmentSieve(a, b + 1);
        // cout << cnt << '\n';
        if(cnt <= 1){
            cout << "There are no adjacent primes.\n";
        }
        else{
            int mn = 2e9, x1, y1;
            for(int i = 0; i + 1 < cnt; i ++){
                if(prime[i + 1] - prime[i] < mn){
                    mn = prime[i + 1] - prime[i];
                    x1 = prime[i];
                    y1= prime[i + 1];
                }
            }
            int mx = -2e9, x2, y2_;
            for(int i = 0; i + 1 < cnt; i ++){
                if(prime[i + 1] - prime[i] > mx){
                    mx = prime[i + 1] - prime[i];
                    x2 = prime[i];
                    y2_= prime[i + 1];
                }
            }
            printf("%lld,%lld are closest, %lld,%lld are most distant.",x1,y1,x2,y2_);
        }
        
    }
}

signed main(){
    solve();
    return 0;
} 