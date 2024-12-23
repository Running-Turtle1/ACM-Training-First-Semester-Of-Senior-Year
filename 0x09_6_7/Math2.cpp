#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;

int prime_cnt = 0;
int const N = 1e6 + 10;
bool is_prime[N];
bool is_prime_small[N];
ll prime[N];

void segment_sieve(ll a, ll b){
	for(ll i = 0; i * i < b; i ++)
		is_prime_small[i] = true;
	for(ll i = 0; i < b - a; i ++)
		is_prime[i] = true;
	
	is_prime_small[1] = false;
	for(ll i = 2; i * i < b; i ++){
		if(is_prime_small[i]){
			for(ll j = 2 * i; j * j < b; j += i)
				is_prime_small[j] = false;
			for(ll j = max(2LL, (a + i - 1) / i) * i; j < b; j += i)
				is_prime[j - a] = false;
		}
	}
	
	for(ll i = 0; i < b - a; i ++)
		if(is_prime[i]) prime[prime_cnt ++] = i + a;
}

int main(){
	ll a, b;
	while(cin>>a>>b){
	    if(a == 1) a = 2;
		prime_cnt = 0;
		segment_sieve(a, b + 1);
		if(prime_cnt <= 1) puts("There are no adjacent primes.");
		else{
		    ll res1, res2, res_1 = 2e9;
		    ll res3, res4, res_2 = -2e9;
		    for(int i = 1; i <= prime_cnt - 1; i ++){
		        if(prime[i] - prime[i - 1] < res_1){
		            res_1 = prime[i] - prime[i - 1];
		            res1 = prime[i - 1], res2 = prime[i];
		        }
		        if(prime[i] - prime[i - 1] > res_2){
		            res_2 = prime[i] - prime[i - 1];
		            res3 = prime[i - 1], res4 = prime[i];
		        }
		    }
		    printf("%lld,%lld are closest, %lld,%lld are most distant.\n", res1, res2, res3, res4);
		}
	}
	
	return 0;
} 