#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 5e5 + 10;

int n, L, R;
int h[N];
int tr[N]; // 维护差分数组
int lowbit(int x){return x & -x; }
void add(int p, int v){
    for(int i = p; i <= n; i += lowbit(i)){
    	tr[i] += v;
    }
}
// 区间加 v
void segAdd(int l, int r, int v){
	add(l, v);
	add(r + 1, -v);
}
// 查询 h[p]
int query(int p){
	int res = 0;
    for(int i = p; i; i -= lowbit(i)){
        res += tr[i];
    }
    return res;
}

void solve(){
	cin >> n >> L >> R;
	for(int i = 1; i <= n; i ++){
		cin >> h[i];
    }
    sort(h + 1, h + n + 1);
	for(int i = 1; i <= n; i ++){
		h[i] = (h[i] + 1) / 2;
		segAdd(i, i, h[i]);
    }
    // for(int i = 1; i <= n; i ++){
    // 	cout << query(i) << " \n"[i == n];
    // }
    // int cnt = 0;
    int Leftidx = 1;
    priority_queue<int> q;
    int sum = 0; // 右侧可以凑数的次数
    while(true){
    	// ++ cnt;
    	// cout << cnt << '\n';
    	// for(int i = 1; i <= n; i ++){
    	// 	if(i < Leftidx) cout << "0 ";
    	// 	else cout << query(i) << ' ';
    	// }
    	// cout << '\n';
    	int Rightidx = Leftidx + (R - L) - 1;
    	int sumPeople = n - Leftidx + 1; // 总人数
    	// cout<<Leftidx<<' '<<Rightidx<<' '<<sumPeople<<'\n';
    	if(sumPeople < L){
    		cout << sum << '\n';
    		if(sumPeople + sum >= L){
    			cout << "YES\n";
    		}
    		else{
    			cout << "NO\n";
    		}
    		return ;
    	}
    	if(sumPeople <= R){ // 全部送走
    		cout << "YES\n";
    		return ;
    	}
    	// 此时必须选 L 个人回程,
    	if(n - L + 1 >= Rightidx + 1 && query(n - L + 1) >= 2){ // 此时有解
    		int l = Rightidx + 1, r = n;
    		while(l < r){
    			int mid = l + r >> 1;
    			if(query(mid) >= 2) r = mid;
    			else l = mid + 1;
    		}
    		// cout<<"l : " << l << '\n';
    		segAdd(l, l + L - 1, -1); // 区间减 1
    		for(int k = Leftidx; k <= Rightidx; k ++){
    			if(query(k) > 1){
    				q.push(query(k));//sum += query(k) - 1;
    			}
    		}
    		Leftidx = Rightidx + 1;
    	}
    	else{
    		cout << "NO\n";
    		return ;
    	}
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
