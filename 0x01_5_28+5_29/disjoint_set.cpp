#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1e4 + 10;
int q;

struct DisjointSet{
	int n, fa[N], sz[N];	

	DisjointSet(int n){
		for(int i = 1; i <= n; i ++){
			fa[i] = i;
			sz[i] = 1;
	    }
	}

	int find(int x){
		if(x == fa[x]) return x;
		return fa[x] = find(fa[x]); // 路径压缩
	}

	// 把 x 所在的集合合并到 y
	void unionset(int x, int y){
		// 按秩合并 (启发式合并)
		x = find(x), y = find(y);
		if(x == y) return ;
		if(sz[x] > sz[y]) swap(x, y);
		fa[x] = y;
		sz[y] += sz[x];
	}
};

void solve(){
	int n;
	cin >> n >> q;
	DisjointSet disjointSet(n);
	for(int i = 1; i <= q; i ++){
		int z, x, y;
		cin >> z >> x >> y;
		switch(z) {
			case 1 :
				disjointSet.unionset(x, y);
				break;
			case 2 :
				if(disjointSet.find(x) == disjointSet.find(y)){
					cout << "Y\n";
				}
				else{
					cout << "N\n";
				}
				break;
		}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}