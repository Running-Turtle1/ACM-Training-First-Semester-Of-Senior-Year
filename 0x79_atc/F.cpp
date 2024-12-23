#include <bits/stdc++.h>
#define fi first
#define se second
#define int long long

using namespace std;

typedef pair<int, int> PII;
typedef long long LL;

const int N = 2e5 + 10, inf = 9e18;

int n, q;
int a[N];
struct Node {
	int l, r;
	int S1, S2, L1, L2;
}tr[N << 2];

void work(int u, int d1, int d2) {
	if (d1 != inf) tr[u].S1 = (tr[u].r - tr[u].l + 1) * d1, tr[u].L1 = d1;
	if (d2 != inf) tr[u].S2 = (tr[u].l + tr[u].r) * (tr[u].r - tr[u].l + 1) / 2 * d2, tr[u].L2 = d2;
}
void pushup(int u) {
	tr[u].S1 = tr[u << 1].S1 + tr[u << 1 | 1].S1;
	tr[u].S2 = tr[u << 1].S2 + tr[u << 1 | 1].S2;
}
void pushdown(int u) {
	work(u << 1, tr[u].L1, tr[u].L2), work(u << 1 | 1, tr[u].L1, tr[u].L2);
	tr[u].L1 = inf, tr[u].L2 = inf;
}
void build(int u, int l, int r) {
	tr[u] = {l, r}, tr[u].L1 = tr[u].L2 = inf;
	if (l == r) return;
	int mid = l + r >> 1;
	build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
}
void modify(int u, int l, int r, int d1, int d2) {
	if (tr[u].l >= l && tr[u].r <= r) {
		work(u, d1, d2);
		return;
	}
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1;
	if (mid >= l) modify(u << 1, l, r, d1, d2);
	if (mid < r) modify(u << 1 | 1, l, r, d1, d2);
	pushup(u);
}
int query(int u, int l, int r) {
	if (tr[u].l >= l && tr[u].r <= r) return tr[u].S1 + tr[u].S2;
	pushdown(u);
	int mid = tr[u].l + tr[u].r >> 1, tot = 0;
	if (mid >= l) tot += query(u << 1, l, r);
	if (mid < r) tot += query(u << 1 | 1, l, r);
	return tot;
}



signed main() {
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(0);

	cin >> n;
	build(1, 1, n);
	for (int i = 1; i <= n; i ++)
		cin >> a[i], modify(1, i, i, a[i], 0);

	cin >> q;
	int res = 0;
	while (q -- ) {
		int u, v;
		cin >> u >> v;

		if (query(1, u, u) >= v) {
			int lo = 1, ro = u, po = u;
			while (lo <= ro) {
				int mid = lo + ro >> 1;
				if (v - (u - mid) <= query(1, mid, mid)) ro = mid - 1, po = mid;
				else lo = mid + 1;
			}
			// cout << query(1, po, u) - (2 * v - u + po) * (u - po + 1) / 2 << endl;
			res += query(1, po, u) - (2 * v - u + po) * (u - po + 1) / 2;
			modify(1, po, u, v - u, 1);
		} else {
			int lo = u, ro = n, po = u;
			while (lo <= ro) {
				int mid = lo + ro >> 1;
				if (v + (mid - u) >= query(1, mid, mid)) lo = mid + 1, po = mid;
				else ro = mid - 1;
			}
			// cout << (2 * v + po - u) * (po - u + 1) / 2 - query(1, u, po) << endl;
			res += (2 * v + po - u) * (po - u + 1) / 2 - query(1, u, po);
			modify(1, u, po, v - u, 1);
		}
	}

	cout << res << endl;

	return 0;
}