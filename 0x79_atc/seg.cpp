#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

struct Node{
	int l, r;
	int s1, s2, d1, d2;
};

void pushup(int u){
	tr[u].sum = tr[lc].s1 + tr[rc].s1;
	tr[u].s2 = tr[lc].s2 + tr[rc].s2;
}

void solve(){

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
