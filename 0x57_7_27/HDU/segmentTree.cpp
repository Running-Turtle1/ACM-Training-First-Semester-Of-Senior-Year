#include<bits/stdc++.h>
using namespace std;
#define int long long

#define lc u << 1
#define rc u << 1 | 1

int const N = 1e5 + 10;

struct treeNode{
	int l, r;
	int lval, rval;
	int tp;
	int add; // 区间加懒标记
}tr[N * 4];

void pushup(int u){
	tr[u].lval = tr[lc].lval;
	tr[u].rval = tr[rc].rval;
	if(tr[lc].tp == 5 || tr[rc].tp == 5){
		tr[u].tp = 5;
	}
	if(tr[lc].tp == 4){
		if(tr[rc].tp == 3 && tr[lc].rval >= tr[rc].lval){
			tr[u].tp = 4;
		}
		else{
			tr[u].tp = 5;
		}
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
