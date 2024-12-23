#include<bits/stdc++.h>
using namespace std;
#define int long long
class Solution {
public:
    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        int n = colors.size();

        int tr[n + 1][2];
        memset(tr, 0, sizeof tr);
        auto add = [&] (int id, int pos, int val){
            for(int i = pos; i <= n; i += i & -i) tr[i][id] += val;
        };
        auto ask = [&] (int id, int l, int r) {
            int res = 0;
            for(int i = r; i; i -= i & -i) res += tr[i][id];
            for(int i = l - 1; i; i -= i & -i) res -= tr[i][id];
            return res;
        };

        // k = 1 表示往结束点 set 里加入新结束点 pos
        // k = -1 表示从结束点 set 里删除结束点 pos
        // L 和 R 是 pos 左边和右边最近的其它结束点
        auto update = [&] (int l, int r, int pos, int k){
            int old = (r - l + n) % n;
            if(!old) old = n;
            add(0, old, -k * n);
            add(1, old, -k);

            int len = (pos - l + n) % n;
            if(!len) len = n;
            add(0, len, k * len);
            add(1, len, -k);

            len = (r - pos + n) % n;
            if(!len) len = n;
            add(0, len, k * len);
            add(1, len, -k);
        };

        set<int> st;
        auto ins = [&] (int pos) {
            if(st.empty()){
                st.insert(pos);
                add(0, n, n), add(1, n, 1);
            }
            else{
                auto it = st.insert(pos).first;
                int l = (it == st.begin() ? *st.rbegin() : *prev(it));
                int r = (next(it) == st.end() ? *st.begin() : *next(it));
                update(l, r, pos, 1);
            }
        };

        auto del = [&] (int pos) {
            if(st.size() == 1){
                st.erase(st.find(pos));
                add(0, n, -n), add(1, n, -1);
            }
            else{
                auto it = st.erase(st.find(pos));
                // 找到左右两个最近的其它结束点
                int L = (it == st.begin() ? *prev(st.end()) : *prev(it));
                int R = (it == st.end() ? *(st.begin()) : *it);
                update(L, R, pos, -1); 
            }
        };

        for (int i = 0; i < n; i++) if (colors[i] == colors[(i + 1) % n]) ins(i);
        
        vector<int> ans;
        for (auto &qry : queries) {
            if (qry[0] == 1) {
                if (st.empty()) ans.push_back(n);
                else {
                    // 因为树状数组维护的是小于等于 s 的总和
                    // 要求大于等于 s 的总和，可以转为“所有元素之和，减去小于等于 s - 1 的总和”
                    int sm = ask(0, qry[1], n);
                    int cnt = ask(1, qry[1], n);
                    ans.push_back(sm - cnt * qry[1] + cnt);
                }
            } else {
                // 修改 idx 的颜色，只影响 idx - 1 和 idx 是否成为结束点
                int idx = qry[1], col = qry[2];
                int prv = (idx - 1 + n) % n, nxt = (idx + 1) % n;
                // 回撤旧情况
                if (colors[prv] == colors[idx]) del(prv);
                if (colors[idx] == colors[nxt]) del(idx);
                // 计算新情况
                colors[idx] = col;
                if (colors[prv] == colors[idx]) ins(prv);
                if (colors[idx] == colors[nxt]) ins(idx);
            }
        }
        return ans;
 
    }
};
void solve(){

}

signed main(){
	solve();
	return 0;
}
