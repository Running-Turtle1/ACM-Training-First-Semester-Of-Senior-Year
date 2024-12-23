 
class Solution {
public:
    vector<int> numberOfAlternatingGroups(vector<int>& colors, vector<vector<int>>& queries) {
        int sz = colors.size();
        int n = 2 * sz - 1;
        vector<int> ncolors(n + 10);
        for(int i = 0; i < sz; i ++){
            ncolors[i + 1] = colors[i];
            ncolors[sz + i + 1] = colors[i];
        }

        // 处理 [1, sz] 的环形数组即可
        for(int i = 1; i <= n; i ++){
            cout << ncolors[i] << " \n"[i == n];
        }

        vector<array<int, 2> > tr(n + 1, {0, 0});
        auto add = [&] (int p, int v){
            for(int i = p; i <= n; i += i & -i){
                tr[i][0] += v;
                if(v > 0) tr[i][1] ++;
                else tr[i][1] --;
            }
        }; 
        auto ask = [&] (int l, int r, int id) {
            int res = 0;
            for(int i = r; i; i -= i & -i) res += tr[i][id];
            for(int i = l - 1; i; i -= i & -i) res -= tr[i][id];
            return res;
        }; 

        set<int> pos; // 维护所有 ncolors[i] = ncolors[i + 1] 位置

        for(int i = 1; i + 1 <= n; i ++){
            if(ncolors[i] == ncolors[i + 1]){
                pos.insert(i);
            }
        } 
        pos.insert(n);

        for(int i = 1; i <= n; i ++){
            int j = i;
            while(j + 1 <= n && ncolors[j + 1] != ncolors[j]) j ++;
            if(i <= sz){
                add(j - i + 1, j - i + 1); 
            }
            i = j;
        };  
 
        auto ins = [&] (int p) {
            auto r = pos.upper_bound(p);
            int lpos, rpos = *r;
            if(r == pos.begin()) lpos = 0;
            else lpos = *(prev(r)); 
            if(lpos + 1 <= sz) add(p - lpos, p - lpos);
            if(p + 1 <= sz) add(rpos - p, rpos - p);
            if(lpos + 1 <= sz) add(rpos - lpos, -(rpos - lpos));
            pos.insert(p);
        };
        auto del = [&] (int p){
            pos.erase(p);
            auto r = pos.upper_bound(p);
            int lpos, rpos = *r;
            if(r == pos.begin()) lpos = 0;
            else lpos = *(prev(r)); 
            if(lpos + 1 <= sz) add(p - lpos, -(p - lpos));
            if(p + 1 <= sz) add(rpos - p, -(rpos - p));
            if(lpos + 1 <= sz) add(rpos - lpos, rpos - lpos);
        };
        
        for(auto &p : pos) cout << p << ' ';
        cout << '\n';

        vector<int> ans;
        // return ans;
        for(int i = 0; i < queries.size(); i ++){
            if(queries[i][0] == 1){
                int len = queries[i][1];
                int res = ask(len, n, 0) - (len - 1) * ask(len, n, 1);
                cout << ask(len, n, 0) << ' ' << ask(len, n, 1) << '\n';
                ans.push_back(res); 
            }
            else{
                int idx = queries[i][1] + 1, to = queries[i][2];
                if(ncolors[idx] == to) continue ;
                ncolors[idx] = ncolors[idx + sz] = to;
                if(idx != 1) {
                    // cout << idx - 1 << '\n';
                    if(pos.count(idx - 1)) del(idx - 1); 
                    else ins(idx - 1); 
                } 
                if(idx != n){
                    if(pos.count(idx)) del(idx); 
                    else ins(idx); 
                }
                idx += sz;
                if(idx != 1) {
                    if(pos.count(idx - 1)) del(idx - 1); 
                    else ins(idx - 1); 
                } 
                if(idx != n){
                    if(pos.count(idx)) del(idx); 
                    else ins(idx); 
                }
                cout << "Change\n";
                for(int i = 1; i <= n; i ++){
                    cout << ncolors[i] << " \n"[i == n];
                }
                for(int i = 1; i <= n; i ++){
                    cout << "len: " << i << ' ' << ask(i, i, 1) << ' ' << ask(i, i, 0) << '\n';
                }
                for(auto &p : pos) cout << p << ' ';
                cout << '\n';
            }
        }
    
        return ans;
    }
};
