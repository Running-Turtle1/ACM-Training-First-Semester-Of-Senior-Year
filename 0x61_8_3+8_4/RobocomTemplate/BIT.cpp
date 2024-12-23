#include<bits/stdc++.h>
using namespace std;
#define int long long

void add(int p, int v){
	for(int i = p; i < N i += lowbit(i)){
		tr[i] += v;
	}
}

void solve(){

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}

class BIT{
	public :
		int n, a[N], tr[N];
		void memset_(int n){
			this->n = n;
			for(int i = 1; i <= n; i ++){
				a[i] = 0;
				tr[i] = 0;
			}
		}
		void update(int x, int value){
			a[x] = value;
			while(x <= n){
				tr[x] = a[x];
				for(int i = 1; i < i & -i; i <<= 1){
					tr[x] = max(tr[x], tr[x - i]);
				}
				x += x & -x;
			}
		}
		int query(int L, int R){
			
		}
};
