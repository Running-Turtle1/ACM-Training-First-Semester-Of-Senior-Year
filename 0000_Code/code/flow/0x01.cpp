#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int N = 210, M = (10200 + N) * 2, inf = 1e9;

struct edge
{
    int v, c, nxt;
} edges[M];

int head[N], d[N], cur[N], diff[N]{0}, LOW[M], idx = 0, n, m, s, t;

inline void addedge(int u, int v, int c)
{
    edges[idx] = {v, c, head[u]}, head[u] = idx++;
}
inline void add(int u, int v, int low, int up)
{
    LOW[idx] = low, addedge(u, v, up - low), addedge(v, u, 0);
}

bool bfs() // 多路增广，分层搜索优化
{
    memset(d, 0, sizeof(d));
    queue<int> q;
    q.emplace(s), d[s] = 1;
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i = head[u]; ~i; i = edges[i].nxt)
        {
            int v = edges[i].v;
            if (!d[v] && edges[i].c)
            {
                d[v] = d[u] + 1, q.emplace(v);
                if (v == t)
                    return true;
            }
        }
    }
    return false;
}

int dfs(int u, int limit)
{
    if (u == t)
        return limit;
    int ret = 0;
    for (int i = cur[u]; ~i && limit; i = edges[i].nxt) // limit > 0 余量优化
    {
        cur[u] = i; // 当前弧优化
        int v = edges[i].v;
        if (d[v] == d[u] + 1 && edges[i].c)
        {
            int incf = dfs(v, min(limit, edges[i].c));
            if (!incf)
                d[v] = 0; // 剪枝优化
            edges[i].c -= incf, edges[i ^ 1].c += incf, ret += incf, limit -= incf;
        }
    }
    return ret;
}

int dinic()
{
    int ret = 0;
    while (bfs())
        memcpy(cur, head, sizeof(head)), ret += dfs(s, inf);

    return ret;
}

int main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0), memset(head, -1, sizeof(head));

    int a, b, c, d, tot = 0;
    cin >> n >> m, s = 0, t = n + 1;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c >> d;
        add(a, b, c, d);
        diff[a] -= c, diff[b] += c; // diff = in - out
    }
    for (int i = 1; i <= n; i++)
    {
        if (diff[i] > 0)
            add(s, i, 0, diff[i]), tot += diff[i];
        else if (diff[i] < 0)
            add(i, t, 0, -diff[i]);
    }

    if (dinic() == tot)
    {
        cout << "YES" << '\n';
        for (int i = 0; i < m * 2; i += 2)
            cout << edges[i ^ 1].c + LOW[i] << '\n';
    }
    else
    {
        cout << "NO";
    }
    return 0;
}
