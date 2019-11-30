// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr mo = 998244353ll;
auto constexpr maxn = 150007;
int dfn[maxn];
ll size[maxn];
ll val[maxn];
// for heavy-light decomposition
int top[maxn];
int heavy_son[maxn];
int parent[maxn];
int tot;

// for bit
ll a[maxn];

ll n, q;
ll inv_n;
std::vector<std::vector<int>> tree;

template <class T>
T add(T x, T y)
{
    return (x + y) % mo;
}

template <class T>
T mul(T x, T y)
{
    return (x * y) % mo;
}

ll quick_pow(ll a, ll b)
{
    if (!b)
        return 1;
    auto tmp = quick_pow(a, b / 2);
    tmp = mul(tmp, tmp);
    if (b & 1)
        tmp = mul(tmp, a);
    return tmp;
}

template <class T>
T lowbit(T x)
{
    return x & -x;
}

void tree_update(int p, ll d)
{
    for (; p <= n; p += lowbit(p))
        a[p] = add(a[p], d);
}

void tree_update(int l, int r, ll d)
{
    if (l > r)
        return;
    tree_update(l, d);
    tree_update(r + 1, mo - d);
}

auto tree_query(int p)
{
    ll sum{};
    for (; p; p -= lowbit(p))
        sum = add(sum, a[p]);
    return sum;
}

void add_edge(int u, int v)
{
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
}

void dfs(int u, int parent)
{
    ::parent[u] = parent;
    dfn[u] = ++tot;
    size[u] = 1;
    for (auto v : tree[u]) {
        if (v == parent)
            continue;
        dfs(v, u);
        size[u] += size[v];
        if (size[v] > size[heavy_son[u]])
            heavy_son[u] = v;
    }
}

void dfs(int u, int parent, int top_parent)
{
    top[u] = top_parent;
    if (auto v = heavy_son[u]; v)
        dfs(v, u, top_parent);
    for (auto v : tree[u]) {
        if (v == parent || v == heavy_son[u])
            continue;
        dfs(v, u, v);
    }
}

void update(int u, ll d)
{
    val[u] = add(val[u], d);
    auto tmp = mul(size[u], d);
    tree_update(1, dfn[u] - 1, tmp);
    tree_update(dfn[u] + size[u], n, tmp);
    if (heavy_son[u]) {
        auto v = heavy_son[u];
        tree_update(dfn[v], dfn[v] + size[v] - 1, mul(n - size[v], d));
    }
}

ll query(int u)
{
    auto ans = tree_query(dfn[u]);
    auto tu = u;
    for (int topu; u; u = parent[topu]) {
        topu = top[u];
        ans = add(ans, mul(val[parent[topu]], n - size[topu]));
    }
    return add(val[tu], mul(ans, inv_n));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> q;
    inv_n = quick_pow(n, mo - 2);
    tree.resize(n + 1);
    for (auto i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        add_edge(u, v);
    }

    dfs(1, 0);
    dfs(1, 0, 1);

    while (q--) {
        int op, v, d;
        std::cin >> op >> v;
        if (op == 1) {
            std::cin >> d;
            update(v, d);
        } else {
            std::cout << query(v) << "\n";
        }
    }

}

