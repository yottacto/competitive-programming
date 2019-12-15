// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr inf = 1<<30;

struct edge
{
    int v;
    ll cost;
};

std::vector<std::vector<edge>> g;
std::vector<int> size;

int k;
int n;
ll G = 0;
ll B = 0;

int dfs(int u, int parent)
{
    auto count = 0;
    for (auto const& e : g[u]) {
        auto [v, cost_v] = e;
        if (v == parent)
            continue;
        auto tmp = dfs(v, u);
        if (tmp) {
            count++;
            G += cost_v;
        }
    }
    if (count & 1) {
        return 0;
    } else {
        return 1;
    }
}

void dfs2(int u, int parent)
{
    size[u] = 1;
    for (auto const& e : g[u]) {
        auto [v, cost_v] = e;
        if (v == parent)
            continue;
        dfs2(v, u);
        size[u] += size[v];
    }

    for (auto const& e : g[u]) {
        auto [v, cost_v] = e;
        if (v == parent)
            continue;
        B += cost_v * std::min(size[v], n - size[v]);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> k;
        n = 2 * k;
        g.clear();
        g.resize(n + 1);
        size.clear();
        size.resize(n + 1);
        G = B = 0;
        for (auto i = 1; i < n; i++) {
            int u, v;
            ll w;
            std::cin >> u >> v >> w;
            g[u].emplace_back(edge{v, w});
            g[v].emplace_back(edge{u, w});
        }
        dfs(1, 0);

        dfs2(1, 0);

        std::cout << G << " " << B << "\n";
    }
}

