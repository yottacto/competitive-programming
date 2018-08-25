// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cmath>

using ll = long long;

auto constexpr maxn = 50010;
auto constexpr maxm = 330;
auto constexpr maxj = 30;
std::vector<int> tree[maxn];
ll a[maxn];
int b[maxn];
int k[maxn];
int depth[maxn];
int parent[maxj][maxn];
ll jump_sum[maxm][maxn];
int in[maxn], out[maxn];
int time_stamp;
int n;
int block;
std::vector<int> path_to_root;
std::vector<int> mark[maxn];

struct query
{
    int u, v, k;
    ll sum;
};

query queries[maxn];

void dfs(int u, int p, int d)
{
    in[u] = time_stamp++;
    for (auto i = 1; i <= block; i++) {
        if (i <= (int)path_to_root.size())
            jump_sum[i][u] = jump_sum[i][*std::prev(path_to_root.end(), i)] + a[u];
        else
            jump_sum[i][u] = a[u];
    }

    path_to_root.emplace_back(u);
    depth[u] = d;
    parent[0][u] = p;
    for (auto v : tree[u]) {
        if (v == p)
            continue;
        dfs(v, u, d + 1);
    }
    path_to_root.pop_back();
    out[u] = time_stamp++;
}

bool ancestor(int u, int v)
{
    return in[u] <= in[v] && out[v] <= out[u];
}

int bin(int v, int k)
{
    int len = path_to_root.size() - 1;
    auto l = 0;
    auto r = len / k;
    while (l + 1 < r) {
        auto mid = (l + r) / 2;
        if (!ancestor(path_to_root[len - mid * k], v))
            l = mid;
        else
            r = mid;
    }
    if (ancestor(path_to_root[len - l * k], v))
        r = l;
    if (!ancestor(path_to_root[len - r * k], v))
        return 0;
    return path_to_root[len - r * k];
}

void dfs_ans(int u, int p, int d)
{
    path_to_root.emplace_back(u);
    for (auto i : mark[u]) {
        auto v = queries[i].u == u ? queries[i].v : queries[i].u;
        auto k = queries[i].k;
        auto& sum = queries[i].sum;
        auto const& path = path_to_root;
        if (k > block) {
            auto tu = u;
            auto j = path.size() - 1;
            for (; !ancestor(tu, v);) {
                sum += a[tu];
                j -= k;
                if (j < 0) break;
                tu = path[j];
            }
        } else {
            auto w = bin(v, k);
            sum += jump_sum[k][u] - jump_sum[k][w];
        }
    }
    for (auto v : tree[u]) {
        if (v == p)
            continue;
        dfs_ans(v, u, d + 1);
    }
    path_to_root.pop_back();
}

void lca_binary_lifting()
{
    for (auto j = 1; j < maxj; j++)
        for (auto i = 1; i <= n; i++)
            if (parent[j - 1][i])
                parent[j][i] = parent[j - 1][parent[j - 1][i]];
}

int walk(int u, int k)
{
    for (auto i = 0; i < maxj && u; i++)
        if (k & (1 << i))
            u = parent[i][u];
    return u;
}

int lca(int u, int v)
{
    if (depth[u] < depth[v])
        std::swap(u, v);
    u = walk(u, depth[u] - depth[v]);
    if (u == v)
        return u;
    for (auto i = maxj - 1; i >= 0; i--)
        if (parent[i][u] != parent[i][v]) {
            u = parent[i][u];
            v = parent[i][v];
        }
    return parent[0][u];
}

int dist(int u, int v)
{
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
}

void dividable(int i)
{
    auto& u = queries[i].u;
    auto& v = queries[i].v;
    auto& sum = queries[i].sum;
    auto k = queries[i].k;
    auto len = dist(u, v);
    if (len % k) {
        sum += a[v];
        v = walk(v, len % k);
    }
    auto c = lca(u, v);
    if (!((depth[c] - depth[u]) % k))
        sum += a[c];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    block = std::sqrt(n);
    path_to_root.reserve(n + 1);

    for (auto i = 1; i <= n; i++)
        std::cin >> a[i];

    for (auto i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
    dfs(1, 0, 1);
    lca_binary_lifting();

    for (auto i = 1; i <= n; i++)
        std::cin >> b[i];
    for (auto i = 1; i < n; i++)
        std::cin >> k[i];

    for (auto i = 1; i < n; i++) {
        queries[i].u = b[i];
        queries[i].v = b[i + 1];
        queries[i].k = k[i];
        queries[i].sum = 0;
        dividable(i);

        mark[queries[i].u].emplace_back(i);
        mark[queries[i].v].emplace_back(i);
    }

    dfs_ans(1, 0, 1);

    for (auto i = 1; i < n; i++)
        std::cout << queries[i].sum << "\n";
}

