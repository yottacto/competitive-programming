// ml:run = $bin < input
// ml:std = c++03
#include <iostream>
#include <algorithm>
#include <vector>

typedef long long ll;

int const maxn = 100007;
int const maxj = 20;
int parent[maxj][maxn];
int depth[maxn];

int root[maxn];
ll weight[maxn];
int n, m;

std::vector<std::vector<int> > tree;
std::vector<ll> da;

struct node
{
    int l;
    int r;
    int count;
};

node pst[maxn * 40];
int alloc;

int get_id(ll x)
{
    return std::lower_bound(da.begin(), da.end(), x) - da.begin() + 1;
}

ll get_value(int id)
{
    return da[id - 1];
}

void add_edge(int u, int v)
{
    tree[u].push_back(v);
    tree[v].push_back(u);
}

ll query(int u, int v, int anc, int panc, int k, int l = 1, int r = da.size())
{
    if (l == r) return get_value(l);
    int left = pst[pst[u].l].count + pst[pst[v].l].count - pst[pst[panc].l].count - pst[pst[anc].l].count;
    int mid = (l + r) / 2;
    if (k <= left)
        return query(pst[u].l, pst[v].l, pst[anc].l, pst[panc].l, k, l, mid);
    else
        return query(pst[u].r, pst[v].r, pst[anc].r, pst[panc].r, k - left, mid + 1, r);
}

void update(int& now, int pre, int pos, int l = 1, int r = da.size())
{
    pst[now = ++alloc] = pst[pre];
    pst[now].count++;

    if (l == r) return;
    int mid = (l + r) / 2;
    if (pos <= mid)
        update(pst[now].l, pst[pre].l, pos, l, mid);
    else
        update(pst[now].r, pst[pre].r, pos, mid + 1, r);
}

void dfs(int u, int p = 0, int d = 1)
{
    parent[0][u] = p;
    depth[u] = d;
    update(root[u], root[p], get_id(weight[u]));

    for (int i = 0; i < (int)tree[u].size(); i++) {
        int v = tree[u][i];
        if (v == p) continue;
        dfs(v, u, d + 1);
    }
}

void lca_binary_lifting()
{
    for (int j = 1; j < maxj; j++)
        for (int i = 1; i <= n; i++)
            if (parent[j-1][i])
                parent[j][i] = parent[j-1][parent[j-1][i]];
}

int walk(int u, int step)
{
    for (int i = 0; i < maxj && u; i++)
        if (step & (1<<i))
            u = parent[i][u];
    return u;
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        std::swap(u, v);
    u = walk(u, depth[u] - depth[v]);
    if (u == v) return u;

    for (int j = maxj - 1; j >= 0; j--)
        if (parent[j][u] != parent[j][v]) {
            u = parent[j][u];
            v = parent[j][v];
        }
    return parent[0][u];
}

ll kth(int u, int v, int k)
{
    int anc = lca(u, v);
    return query(root[u], root[v], root[anc], root[parent[0][anc]], k);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    tree.resize(n + 1);
    da.reserve(n);
    for (int i = 1; i <= n; i++) {
        std::cin >> weight[i];
        da.push_back(weight[i]);
    }
    std::sort(da.begin(), da.end());
    da.erase(std::unique(da.begin(), da.end()), da.end());

    for (int i = 1; i < n; i++) {
        int u, v; std::cin >> u >> v;
        add_edge(u, v);
    }

    dfs(1);
    lca_binary_lifting();

    for (int u, v, k; m--; ) {
        std::cin >> u >> v >> k;
        std::cout << kth(u, v, k) << "\n";
    }
}

