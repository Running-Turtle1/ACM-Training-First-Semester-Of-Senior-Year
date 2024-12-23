#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e6 + 10;
struct Node{
	int l, r;
	int val;
	int rnd;
	int size; // 用于排名分裂
	int add; // 懒标记
}tr[N];
int root = 0, idx = 0;

int newNode(int v){
	++ idx;
	tr[idx].val = v;
	tr[idx].rnd = rand();
	tr[idx].size = 1;
	tr[idx].add = 0;
	return idx;
}

void pushup(int p){
	tr[p].size = tr[tr[p].l].size + tr[tr[p].r].size + 1;
}

void pushdown(int p){
	if(!tr[p].add) return ;
	tr[p].val += tr[p].add;
	tr[tr[p].l].add += tr[p].add;
	tr[tr[p].r].add += tr[p].add; 
	tr[p].add = 0;
}

void split(int p, int v, int &x, int &y){
	if(!p) {x = y = 0; return;}
	pushdown(p);
	if(tr[p].val <= v){
		x = p;
		split(tr[x].r, v, tr[x].r, y);
		pushup(x);
	}
	else{
		y = p;
		split(tr[y].l, v, x, tr[y].l);
		pushup(y);
	}
}
int merge(int x, int y){
	if(!x || !y) return x + y;
	if(tr[x].rnd < tr[y].rnd){
		pushdown(x);
		tr[x].r = merge(tr[x].r, y);
		pushup(x);
		return x;
	}
	else{
		pushdown(y);
		tr[y].l = merge(x, tr[y].l);
		pushup(y);
		return y;
	}
}
 
// mid 是否小于等于最大值
// 特征 : 
int check(int mid){
	int x, y;
	split(root, mid - 1, x, y);
	int ans = y != 0;//tr[y].size != 0;
	root = merge(x, y);
	return ans;
}
int bs(){
	int l = -1e6, r = 2e9;
	while(l < r){
		int mid = l + r + 1 >> 1;
		if(check(mid)) l = mid;
		else r = mid - 1;
	}
	return l;
}
void insert(int v){
	int x, y, z;
	split(root, v, x, y);
	z = newNode(v);
	root = merge(merge(x, z), y);
}
void solve(){
	srand(time(NULL));
	// 初始化 treap
	for(int i = 1; i <= idx; i ++){
		tr[i].l = tr[i].r = 0;
		tr[i].val = tr[i].rnd = tr[i].size = tr[i].add = 0;
	}
	root = idx = 0;
	int n, m, l, r, x, y, z;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++){
		int x;
		cin >> x;
		insert(x);
	}

	while(m --){
		char opt;
		cin >> opt >> l >> r;
		split(root, r, x, y); // [1, r] [r + 1, n]
		split(x, l - 1, x, z); // [1, l - 1] [l, r]
		if(opt == '+') tr[z].add ++;
		else tr[z].add --;
		root = merge(merge(x, z), y);  

		cout << bs() << ' ';

	}
	cout << '\n';

}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	int T;
	cin >> T;
	while(T --){
		solve();
	}
	return 0;
}
