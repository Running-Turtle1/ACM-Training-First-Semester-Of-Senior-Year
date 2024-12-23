#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 10010;
int const M = 20010;
int const Q = 50010;

struct Edge{
	int a, b; 
}edges[M];
set<pair<int, int> > st;
int n, m, q;
int v[N];
struct Query{
	int tp;
	int a, b;
}querys[Q];

int p[N], d[N];

// 已经位于同一个连通块
int find(int x){
	if(x == p[x]) return x;
	return p[x] = find(p[x]);
	// int t = find(p[x]);
	// d[x] = d[p[x]];
	// return p[x] = t;
}
int cal(int a, int b){
	if(v[a] == v[b]) return min(a, b);
	else if(v[a] > v[b]) return a;
	return b;
}
void merge(int a, int b){
	int pa = find(a), pb = find(b);
	if(pa != pb){
		p[pb] = pa;
		d[pa] = cal(d[pa], d[pb]);
	}
}

void solve(){
	cin >> n;
	for(int i = 1; i <= n; i ++){
		cin >> v[i];
		p[i] = i;
		d[i] = i;
    }
    cin >> m;
    for(int i = 1; i <= m; i ++){
    	int a, b;
    	cin >> a >> b;
    	if(a > b) swap(a, b);
    	edges[i] = {++ a, ++ b};
    }
    cin >> q;
    for(int i = 1; i <= q; i ++){
    	string op;
    	int a, b;
    	cin >> op;
    	if(op == "query"){
    		cin >> a;
    		querys[i] = {0, ++ a};
    	}
    	else{
    		cin >> a >> b;
    		if(a > b) swap(a, b);
    		querys[i] = {1, ++ a, ++ b};
    		st.insert({a, b});
    	}
    }
    for(int i = 1; i <= m; i ++){
    	auto& [a, b] = edges[i];
    	if(st.count({a, b}) == false){
    		// cout << "merge: " << a << ' ' << b << '\n'; 
    		merge(a, b);
    	}
    }
    std::vector<int> ans;
    for(int i = q; i >= 1; i --){
    	int tp = querys[i].tp;
    	if(tp == 0){
    		int a = querys[i].a;
    		if(v[d[find(a)]] > v[a]){
    			ans.push_back(d[find(a)] - 1);
    		}
    		else{
    			ans.push_back(-1);
    		}
    	}
    	else{
    		int a = querys[i].a, b = querys[i].b;
    		// cout << "Merge: " << i << ' ' <<  a << ' ' << b << '\n';
    		// cout << d[find(a)] << '\n';
    		merge(a, b);
    	}
    }
    for(auto i = ans.rbegin(); i != ans.rend(); i ++){
    	cout << (*i) << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
