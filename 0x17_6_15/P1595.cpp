#include<bits/stdc++.h>
using namespace std;

class Arbitrary_Precision_Arithmetic{ 
    /* 所有数据均不含前导 0 */
    public :
    // 高精度加正常数
    static vector<int> add(vector<int> a, int b){
        vector<int> res;
        int t = 0;
        for(int i = 0; i < a.size() || t; i ++){
            if(i < a.size()) t += a[i] * b;
            res.push_back(t % 10);
            t /= 10;
        }
        return res;
    }
    // 高精度加高精度
    static vector<int> add(vector<int> a, vector<int> b){
        vector<int> res;
        int t = 0;
        for(int i = 0; i < a.size() || i < b.size(); i ++){
            if(i < a.size()) t += a[i];
            if(i < b.size()) t += b[i];
            res.push_back(t % 10);
            t /= 10;
        }
        if(t) res.push_back(t);
        return res;
    }
    // 高精度减法 : 做减法令大数减小数, 根据 cmp 情况加负号
    static bool minus_cmp(vector<int> &a, vector<int> &b){
        if(a.size() != b.size()) return a.size() > b.size();
        for(int i = a.size() - 1; i >= 0; i --){
            if(a[i] != b[i]){
                return a[i] > b[i];
            }
        }
        return true;
    }
    static vector<int> minus(vector<int> &a, vector<int> &b){
        vector<int> res;
        int t = 0; // 保留减数
        for(int i = 0; i < a.size(); i ++){
            t = a[i] - t;
            if(i < b.size()) t -= b[i];
            res.push_back((t + 10) % 10);
            (t < 0) ? (t = 1) : (t = 0);
        }
        while(res.size() > 1 && res.back() == 0) res.pop_back();
        return res;
    }
    // 大数乘以小数
    static vector<int> mul(vector<int> &a, int b){
        vector<int> res;
        int t = 0;
        for(int i = 0; i < a.size() || t; i ++){
            if(i < a.size()) t += a[i] * b;
            res.push_back(t % 10);
            t /= 10;
        }
        while(res.size() > 1 && res.back() == 0){
            res.pop_back();
        }
        return res;
    }
    // 大数乘以大数
    static vector<int> mul(vector<int> &a, vector<int> &b){
        vector<int> c(a.size() + b.size());
        for(int i = 0; i < a.size(); i ++){
            for(int j = 0; j < b.size(); j ++){
                c[i + j] += a[i] * b[j]; // 位权相同的数放在一起
            }
        }
        int t = 0;
        for(int i = 0; i < c.size(); i ++){
            t += c[i];
            c[i] = t % 10;
            t /= 10;
        }
        if(t) c.push_back(t);
        while(c.size() > 1 && c.back() == 0) c.pop_back();
        return c;
    }
    // 高精度除以正常数, 返回 {商, 余数}
    // 保证被除数不为 0
    static pair<vector<int>, int> div(vector<int> &a, int b){
        vector<int> res;
        int r = 0;
        for(int i = a.size() - 1; i >= 0; i --){ // 模拟除法过程
            r = r * 10 + a[i];
            res.push_back(r / b);
            r %= b;
        }
        reverse(res.begin(), res.end());
        while(res.size() > 1 && res.back() == 0) res.pop_back();
        return {res, r};
    }
};

vector<int> res[3];
void solve(){
	int n;
	cin >> n;
	if(n == 1){
		cout << "0\n";
		return ;
	}
	res[0].push_back(1);
	res[1].push_back(0);
	for(int i = 2; i <= n; i ++){
		int c = i % 3;
		int b = ((c - 1) % 3 + 3) % 3;
		int a = ((c - 2) % 3 + 3) % 3;
		res[c].clear();
		res[c] = Arbitrary_Precision_Arithmetic::add(res[a], res[b]);
		res[c] = Arbitrary_Precision_Arithmetic::mul(res[c], i - 1);
	}
	for(int i = res[n % 3].size() - 1; i >= 0; i --){
		cout << res[n % 3][i];
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
