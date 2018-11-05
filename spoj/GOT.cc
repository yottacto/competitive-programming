// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>

auto constexpr maxn = 100007;
auto constexpr maxj = 20;
int depth[maxn];
int parent[maxj][maxn];
int root[maxn];
int a[maxn];
int n, m;

std::vector<std::vector<int>> tree;

struct node
{
    int l;
    int r;
    int count;
};

node pst[maxn * 40];
int alloc;

void add_edge(int u, int v)
{
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
}

void lca_binary_lifting()
{
    for (auto j = 1; j < maxj; j++)
        for (auto i = 1; i <= n; i++)
            parent[j][i] = 0;

    for (auto j = 1; j < maxj; j++) {
        for (auto i = 1; i <= n; i++) {
            if (parent[j - 1][i])
                parent[j][i] = parent[j - 1][parent[j - 1][i]];
        }
    }
}

void update(int& now, int pre, int pos, int l = 1, int r = n + 1)
{
    pst[now = ++alloc] = pst[pre];
    pst[now].count++;

    if (l == r) return;

    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(pst[now].l, pst[pre].l, pos, l, mid);
    else
        update(pst[now].r, pst[pre].r, pos, mid + 1, r);
}

auto query(int now, int pre, int pos, int l = 1, int r = n + 1) -> bool
{
    if (l == r)
        return pst[now].count - pst[pre].count;

    auto mid = (l + r) / 2;
    if (pos <= mid)
        return query(pst[now].l, pst[pre].l, pos, l, mid);
    else
        return query(pst[now].r, pst[pre].r, pos, mid + 1, r);
}

void dfs(int u, int p = 0, int d = 1)
{
    parent[0][u] = p;
    depth[u] = d;
    update(root[u], root[p], a[u]);
    for (auto v : tree[u]) {
        if (v == p) continue;
        dfs(v, u, d + 1);
    }
}

auto walk(int u, int step)
{
    for (auto i = 0; i < maxj && u; i++)
        if (step & (1<<i)) {
            u = parent[i][u];
        }
    return u;
}

auto lca(int u, int v)
{
    if (depth[u] < depth[v])
        std::swap(u, v);
    u = walk(u, depth[u] - depth[v]);
    if (u == v) return u;

    for (auto i = maxj - 1; i >= 0; i--)
        if (parent[i][u] != parent[i][v]) {
            u = parent[i][u];
            v = parent[i][v];
        }
    return parent[0][u];
}

auto find(int u, int v, int x)
{
    auto ancestor = lca(u, v);
    return query(root[u], root[parent[0][ancestor]], x)
        || query(root[v], root[parent[0][ancestor]], x);
}

int main()
{
    std::ios::sync_with_stdio(false);
    for (auto T = 0; std::cin >> n >> m; T++) {
        if (T) std::cout << "\n";
        alloc = 0;
        for (auto i = 1; i <= n; i++) {
            std::cin >> a[i];
            a[i]++;
        }
        tree.clear();
        tree.resize(n + 1);
        for (auto i = 1; i < n; i++) {
            int u, v; std::cin >> u >> v;
            add_edge(u, v);
        }
        dfs(1);
        lca_binary_lifting();

        for (int u, v, x; m--; ) {
            std::cin >> u >> v >> x;
            std::cout << (find(u, v, ++x) ? "Find" : "NotFind") << "\n";
        }
    }
}

