#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 2e5 + 10;

struct Q{
	int l, r, k;
}q[N];

int res = 0;
string a, b;
int pos[N], ans[N];

map<char, int> sta;
map<char, int> stb;
map<char, int> stc;

void Add(int x){
	char fs = a[x - 1], sc = b[x - 1];
	if(fs == sc) return ;
	if(stb.count(fs)){
		if(stb[fs] == 1){
			stb.erase(fs);
			// stc.insert()
		}
		else{
			stb[fs] --;
		}
	}
	else{
		sta[fs] ++;
	}
	if(sta.count(sc)){
		if(sta[sc] == 1){
			sta.erase(sc);
		}
		else{
			sta[sc] --;	
		}
	}
	else{
		stb[sc] ++;
	}
	res = sta.size();
	// cout<<"Add: \n";
	// cout << x << '\n';
	// for(auto [x, y] : sta) cout << x << ' ';
    // cout << '\n';
	// for(auto [x, y] : stb) cout << x << ' ';
    // cout << '\n';
	// cout << '\n';
}

void Sub(int x){
	char fs = a[x - 1], sc = b[x - 1];
	if(fs == sc) return ;
	if(sta.count(fs)){
		if(sta[fs] == 1){
			sta.erase(fs);
		}
		else{
			sta[fs] --; 
		}
	}
	else{
		stb[fs] ++;
	}
	if(stb.count(sc)){
		if(stb[sc] == 1){
			stb.erase(sc);
		}
		else{
			stb[sc] --; 
		}
	}
	else{
		sta[sc] ++;
	}
	res = sta.size();
	// cout<<"Sub: \n";
	// cout << x << '\n';
	// for(auto [x, y] : sta) cout << x << ' ';
    // cout << '\n';
	// for(auto [x, y] : stb) cout << x << ' ';
    // cout << '\n';
	// cout << '\n';
}

int n, m;

void solve(){	
	res = 0;
	sta.clear();
	stb.clear();
	stc.clear();
	cin >> n >> m >> a >> b;
	int siz = sqrt(n);
	for(int i = 1; i <= n; i ++){
		pos[i] = i / siz;
	}
	for(int i = 1; i <= m; i ++){
		cin >> q[i].l >> q[i].r;
		q[i].k = i;
	}
	sort(q + 1, q + m + 1, [] (Q &x, Q &y){
		return pos[x.l] == pos[y.l] ? x.r < y.r : pos[x.l] < pos[y.l];
	});

	int l = 1, r = 0; // [l, r]
    for(int i = 1; i <= m; i ++){
        while(q[i].l < l) Add(-- l);
        while(q[i].r > r) Add(++ r);
        while(q[i].l > l) Sub(l ++);
        while(q[i].r < r) Sub(r --);
        // cout<<l<<' '<<r<<'\n';
        // for(auto [x, y] : sta) cout << x << ' ';
        // cout << '\n';
    	// for(auto [x, y] : stb) cout << x << ' ';
        // cout << '\n';
        ans[q[i].k] = res;
    }

    for(int i = 1; i <= m; i ++)
        cout << ans[i] << '\n';
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