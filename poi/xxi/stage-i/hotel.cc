// ml:run = $bin < input
#include <iostream>
#include <vector>

using ll = long long;

std::vector<std::vector<int>> g;
int n;
ll ans;

std::vector<ll> pair_sum;
std::vector<ll> sum;
std::vector<ll> depth;

void add_edge(int u, int v)
{
    g[u].emplace_back(v);
    g[v].emplace_back(u);
}

void calc_depth(int u, int parent, int d)
{
    depth[d]++;
    for (auto v : g[u]) {
        if (v == parent) continue;
        calc_depth(v, u, d + 1);
    }
}

void dfs(int u, int parent = 0)
{
    pair_sum.clear();
    pair_sum.resize(n);
    sum.clear();
    sum.resize(n);
    for (auto v : g[u]) {
        depth.clear();
        depth.resize(n);
        calc_depth(v, u, 1);
        for (auto d = 1; d < n; d++) {
            if (!depth[d]) break;
            ans += depth[d] * pair_sum[d];
            pair_sum[d] += sum[d] * depth[d];
            sum[d] += depth[d];
        }
    }
    for (auto v : g[u])
        if (v != parent)
            dfs(v, u);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    g.resize(n + 1);
    for (auto i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        add_edge(u, v);
    }

    dfs(1);

    std::cout << ans << "\n";
}

