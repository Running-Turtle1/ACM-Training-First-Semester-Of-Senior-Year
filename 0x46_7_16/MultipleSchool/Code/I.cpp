#include<bits/stdc++.h>
using namespace std;
#define int long long

int const N = 1100;

int n, m, q;
char g[N][N];
int f[N][N][4]; // 从 (i, j) 出发发射 k 方向光线最多被折射几次

// 光线 d 摄入 (x, y) 折射之后的方向
// 返回值为 -1 表示未发生折射, 方向不变
// 否则返回折射的方向
int reflect(int x, int y, int d){
    if(g[x][y] == '|'){
        switch(d) {
            case 0 : return -1; 
            case 1 : return 3;
            case 2 : return -1;
            case 3 : return 1;
        }
    }

    if(g[x][y] == '-'){
        switch(d) {
            case 0 : return 2; 
            case 1 : return -1;
            case 2 : return 0;
            case 3 : return -1;
        }
    }
    

    if(g[x][y] == '\\'){
        switch(d) {
            case 0 : return 3;
            case 1 : return 2;
            case 2 : return 1;
            case 3 : return 0;
        }
    }

    if(g[x][y] == '/'){
        switch(d) {
            case 0 : return 1; 
            case 1 : return 0;
            case 2 : return 3;
            case 3 : return 2;
        }
    } 

    return (int)nullptr;
}

// direction
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// 处理从 (x, y) 发射 d 方向光线能到哪
void Initialize(int x, int y, int d){
    set<pair<int, int> > st; // 途径发生折射的镜子
    set<pair<pair<int, int>, int>> vis; // 途径的所有状态
    while(true){
        int nx = x + dx[d], ny = y + dy[d];
        int ndir = reflect(nx, ny, d);

        cout << nx << ' ' << ny << ' ' << ndir << '\n';

        if(ndir != -1 && nx >= 1 && nx <= n && ny >= 1 && ny <= m){ // 如果发生折射, 记录发生折射的镜子
            st.insert({nx, ny});
        }
        else{ // 不发生折射
            ndir = d;
        }

        if(nx < 1 || nx > n || ny < 1 || ny > m || vis.count({{nx, ny}, ndir})){
            for(auto [pr, d] : vis){
                auto [x, y] = pr;
                f[x][y][d] = st.size();
                cout << x << ' ' << y << ' ' << d << '\n';
            }
            cout << st.size() << '\n';
            return ;
        }

        // 正常运作
        vis.insert({{x, y}, d});
        x = nx, y = ny, d = ndir;
    }
}

void solve(){
    cin >> n >> m;
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            cin >> g[i][j];
        }
    }
    
    memset(f, -1, sizeof f); // -1 表示未经过预处理
    // Initialize(1, 2, 1);
    for(int i = 1; i <= n; i ++){
        for(int j = 1; j <= m; j ++){
            for(int k = 0; k < 4; k ++){
                if(f[i][j][k] == -1){
                    cout << "Initialisze from this state: \n";
                    cout << i << ' ' << j << ' ' << k << '\n';
                    cout << "Following is related points: \n";
                    Initialize(i, j, k);
                    cout << '\n';
                }
            }
        }
    }
    
    cin >> q;
    map<string, int> sTodir = {
        {"above", 0},
        {"right", 1},
        {"below", 2},
        {"left", 3}
    };
    for(int i = 1; i <= q; i ++){
        int x, y;
        string s;
        cin >> x >> y >> s;
        // cout << x << ' ' << y << ' ' << sTodir[s] << '\n';
        cout << "res: ";
        cout << f[x][y][sTodir[s]] << '\n';
    }
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0); 
	solve();
	return 0;
}
