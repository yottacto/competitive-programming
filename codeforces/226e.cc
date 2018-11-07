// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <algorithm>
#include <vector>

auto constexpr maxn = 100007;
auto constexpr maxj = 20;
int root[maxn];
int depth[maxn];
int parent[maxj][maxn];
int attacked[maxn];
int n, m, king;

int in[maxn];
int out[maxn];
int tick;
std::vector<std::vector<int>> tree;

struct node
{
    int l;
    int r;
    int sum;
};

node pst[maxn * 40];
int alloc;

void add_edge(int u, int v)
{
    tree[u].emplace_back(v);
}

void dfs(int u, int p = 0, int d = 1)
{
    in[u] = ++tick;
    depth[u] = d;
    parent[0][u] = p;
    for (auto v : tree[u])
        dfs(v, u, d + 1);
    out[u] = ++tick;
}

void lca_binary_lifting()
{
    for (auto j = 1; j < maxj; j++)
        for (auto i = 1; i <= n; i++)
            if (parent[j-1][i])
                parent[j][i] = parent[j-1][parent[j-1][i]];
}

auto walk(int u, int step)
{
    for (auto j = 0; j < maxj; j++)
        if (step & (1<<j))
            u = parent[j][u];
    return u;
}

auto lca(int u, int v)
{
    if (depth[u] < depth[v])
        std::swap(u, v);
    u = walk(u, depth[u] - depth[v]);
    if (u == v)
        return u;

    for (auto j = maxj - 1; j >= 0; j--)
        if (parent[j][u] != parent[j][v]) {
            u = parent[j][u];
            v = parent[j][v];
        }
    return parent[0][u];
}

void update(int& now, int pre, int pos, int delta, int l = 1, int r = tick)
{
    pst[now = ++alloc] = pst[pre];
    pst[now].sum += delta;

    if (l == r) return;
    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(pst[now].l, pst[pre].l, pos, delta, l, mid);
    else
        update(pst[now].r, pst[pre].r, pos, delta, mid + 1, r);
}

auto query(int now, int pre, int tl, int tr, int l = 1, int r = tick)
{
    if (tl > tr) return 0;
    if (tl <= l && r <= tr)
        return pst[now].sum - pst[pre].sum;
    auto mid = (l + r) / 2;
    auto sum = 0;
    if (tl <= mid)
        sum += query(pst[now].l, pst[pre].l, tl, tr, l, mid);
    if (mid < tr)
        sum += query(pst[now].r, pst[pre].r, tl, tr, mid + 1, r);
    return sum;
}

// not include u itself
auto calc_remain(int u, int v, int ancestor, int pre, int now)
{
    if (u == ancestor) return 0;
    auto desecrated = query(root[now], root[pre], in[ancestor], in[u] - 1);
    auto remain = depth[u] - depth[ancestor] - desecrated;
    if (v == ancestor) remain -= (attacked[v] <= pre);
    return remain;
}

auto judge(int u, int v, int mid, int k, int pre, int now)
{
    auto ancestor = walk(u, mid);
    auto remain = calc_remain(u, v, ancestor, pre, now);
    return remain >= k;
}

auto find_kth(int u, int v, int ancestor, int k, int pre, int now) -> int
{
    auto l = 1;
    auto r = depth[u] - depth[ancestor];
    while (l + 1 < r) {
        auto mid = (l + r) / 2;
        if (judge(u, v, mid, k, pre, now))
            r = mid;
        else
            l = mid;
    }
    if (judge(u, v, l, k, pre, now)) r = l;
    return walk(u, r);
}

auto kth_castle(int u, int v, int k, int pre, int now)
{
    auto common = lca(u, v);
    auto remain_u = calc_remain(u, v, common, pre, now);

    if (remain_u >= k)
        return find_kth(u, v, common, k, pre, now);

    auto remain_v = calc_remain(v, u, common, pre, now);
    auto all = remain_u + remain_v
        - (u != common && v != common && attacked[common] <= pre);
    if (all < k) return -1;
    return find_kth(v, u, common, all - k + 1, pre, now);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    tree.resize(n + 1);
    for (auto v = 1; v <= n; v++) {
        int u; std::cin >> u;
        if (u) add_edge(u, v);
        else king = v;
    }
    dfs(king);
    lca_binary_lifting();

    std::cin >> m;
    for (int opt, i = 1; i <= m; i++) {
        std::cin >> opt;
        if (opt == 1) {
            int c; std::cin >> c;
            update(root[i], root[i-1], in[c], 1);
            update(root[i], root[i], out[c], -1);
            attacked[c] = i;
        } else {
            int a, b, k, y; std::cin >> a >> b >> k >> y;
            root[i] = root[i - 1];
            std::cout << kth_castle(a, b, k, y, i) << "\n";
        }
    }
}

