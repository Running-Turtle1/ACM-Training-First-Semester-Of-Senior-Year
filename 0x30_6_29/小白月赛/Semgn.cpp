#define lc u << 1
#define rc u << 1 | 1

struct TreeNode{
    int l, r;
    int mn, mx;
}tr[N * 4];

void pushup(int u){
    tr[u].mx = max(tr[lc].mx, tr[rc].mx);
    tr[u].mn = min(tr[lc].mn, tr[rc].mn);
}

void buildTree(int u, int l, int r){
    tr[u] = {l, r, a[l], a[l]};
    if(l == r) return ;
    int mid = l + r >> 1;
    buildTree(lc, l, mid);
    buildTree(rc, mid + 1, r);
    pushup(u);
}

int askSegmentMax(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].mx;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    int tmpMax = LLONG_MIN;
    if(l <= mid) tmpMax = max(tmpMax, askSegmentMax(lc, l, r));
    if(r > mid) tmpMax = max(tmpMax, askSegmentMax(rc, l, r));
    return tmpMax;
}

int askSegmentMin(int u, int l, int r){
    if(l <= tr[u].l && r >= tr[u].r){
        return tr[u].mn;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    int tmpMin = LLONG_MAX;
    if(l <= mid) tmpMin = min(tmpMin, askSegmentMin(lc, l, r));
    if(r > mid) tmpMin = min(tmpMin, askSegmentMin(rc, l, r));
    return tmpMin;
}

void Modify(int u, int p, int v){
    if(tr[u].l == tr[u].r){
        tr[u] = {p, p, v, v};
        return ;
    }
    int mid = tr[u].l + tr[u].r >> 1;
    if(p <= mid) Modify(lc, p, v);
    else Modify(rc, p, v);
    pushup(u);
}