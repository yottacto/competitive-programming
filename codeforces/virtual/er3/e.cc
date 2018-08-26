// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>

using ll = long long;

auto constexpr maxn = 200007;

struct edge
{
    edge() = default;
    edge(int v, ll w) : v(v), w(w) {}

    int u, v, id;
    ll w;
};

std::vector<edge> edges;

int n, m;
int parent[maxn];
std::vector<edge> tree[maxn];

int p[30][maxn];
ll max[30][maxn];
int depth[maxn];

auto get_parent(int u) -> int
{
    return u == parent[u]
        ? u
        : parent[u] = get_parent(parent[u]);
}

void set_union(int u, int v)
{
    auto tu = get_parent(u);
    auto tv = get_parent(v);
    if (tu != tv)
        parent[tu] = tv;
}

void dfs(int u, int par, int w, int d)
{
    depth[u] = d;
    p[0][u] = par;
    max[0][u] = w;
    for (auto const& e : tree[u]) {
        if (e.v == par)
            continue;
        dfs(e.v, u, e.w, d + 1);
    }
}

void binary_lifting()
{
    for (auto j = 1; j < 30; j++)
        for (auto i = 1; i <= n; i++)
            if (p[j - 1][i]) {
                p[j][i] = p[j - 1][p[j - 1][i]];
                max[j][i] = std::max(max[j - 1][i], max[j - 1][p[j - 1][i]]);
            }
}

auto walk(int& u, int d)
{
    auto res = 0ll;
    for (auto i = 0; i < 30 && u; i++)
        if (d & (1<<i)) {
            res = std::max(res, max[i][u]);
            u = p[i][u];
        }
    return res;
}

auto max_on_path(int u, int v)
{
    if (depth[u] < depth[v])
        std::swap(u, v);
    auto res = walk(u, depth[u] - depth[v]);
    if (u == v)
        return res;
    for (auto i = 29; i >= 0; i--)
        if (p[i][u] != p[i][v]) {
            res = std::max(res, max[i][u]);
            res = std::max(res, max[i][v]);
            u = p[i][u];
            v = p[i][v];
        }
    return std::max(res, std::max(max[0][u], max[0][v]));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    std::iota(parent, parent + n + 1, 0);

    edges.resize(m);
    for (auto i = 0; i < m; i++) {
        auto& e = edges[i];
        std::cin >> e.u >> e.v >> e.w;
        e.id = i;
    }

    std::sort(edges.begin(), edges.end(), [](edge const& lhs, edge const& rhs) {
        return lhs.w < rhs.w;
    });

    auto sum = 0ll;
    for (auto const& e : edges) {
        if (get_parent(e.u) == get_parent(e.v))
            continue;
        tree[e.u].emplace_back(e.v, e.w);
        tree[e.v].emplace_back(e.u, e.w);
        sum += e.w;
        set_union(e.u, e.v);
    }

    dfs(1, 0, 0, 1);
    binary_lifting();

    std::vector<ll> ans(m);
    for (auto const& e : edges) {
        // std::cerr << "(" << e.u << ", " << e.v << ", " << e.w << ") id = " << e.id << "\n";
        if (p[0][e.u] == e.v || p[0][e.v] == e.u) {
            ans[e.id] = sum;
            // std::cerr << "on tree " << ans[e.id] << "\n";
        } else {
            ans[e.id] = sum - max_on_path(e.u, e.v) + e.w;
            // std::cerr << "not on tree " << ans[e.id] << "\n";
        }
    }

    for (auto i : ans)
        std::cout << i << "\n";
}

