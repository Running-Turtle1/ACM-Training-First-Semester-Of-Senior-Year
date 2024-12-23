#include<bits/stdc++.h>
using namespace std;

int const N = 1e5 + 10;
int const P = 13331;
typedef unsigned long long ull;
ull h[N], p[N];

int n, q;
int len;
string s;

void init(){
    p[0] = 1;
    for(int i = 1; i <= n; i ++){
        p[i] = p[i - 1] * P;
        h[i] = h[i - 1] * P + s[i];
    }
}
ull ask(int l, int r){
    return h[r] - h[l - 1] * p[r - l + 1];
}

ull cal(string &t){
    ull res = 0;
    for(int i = 0; i < t.size(); i ++){
        res = res * P + t[i];
    }
    return res;
}

struct query{
    ull t;
    int k;
    int id;
    size_t len;
}Q[N];
int ans[N];

map<int, vector<int> > mp;
void updateMap(int len){
    mp.clear();
    for(int i = 1; i + len - 1 <= n; i ++){
        int r = i + len - 1;
        mp[ask(i, r)].push_back(r);
    }
}

void solve(){
    cin >> n >> q >> s;
    s = ' ' + s;
    init(); // 初始化哈希
    // cout << ask(1, 2) << ' ' << ask(9, 10) << '\n';
    // string y = "ab";
    // cout << cal(y) << '\n';
    for(int i = 1; i <= q; i ++) {
        string t;
        int k;
        cin >> t >> k;
        // cout << i << ' ' << cal(t) << '\n';
        Q[i] = {cal(t), k, i, t.size()};
    }
    sort(Q + 1, Q + q + 1, [] (query &a, query & b){
        return a.len < b.len;
    });
    for(int i = 1; i <= q; i ++){
        auto &[t, k, id, len] = Q[i];
        // cout << t << ' ' << k << ' ' << id << ' ' << len << '\n';
    }
    size_t nowLen = 0;
    for(int i = 1; i <= q; i ++){
        auto &[t, k, id, len] = Q[i];
        if(nowLen != len){
            nowLen = len;
            updateMap(len);
        }
        if(mp[t].size() < k){
            ans[id] = -1;
        }
        else{
            ans[id] = mp[t][k - 1];
        }
    }
    for(int i = 1; i <= q; i ++){
        cout << ans[i] << '\n';
    }
}   

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
