// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <bits/stdc++.h>

int n, m;
std::vector<std::vector<int>> g;
std::vector<char> vis;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> m;
    g.resize(n + 1);
    vis.resize(n + 1);
    for (auto i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    auto res = 0;
    std::unordered_set<int> zeros;
    std::unordered_set<int> ones;
    for (auto i = 2; i <= n; i++)
        ones.emplace(i);
    zeros.emplace(1);
    for (auto i = 1; i <= n; i++) {
        int u;
        if (zeros.empty()) {
            u = *ones.begin();
            ones.erase(u);
            res++;
        } else {
            u = *zeros.begin();
            zeros.erase(u);
        }

        // std::cerr << i << " " << u << "\n";

        vis[u] = true;
        std::unordered_set<int> keeps;
        for (auto v : g[u]) {
            if (!vis[v] && ones.count(v)) {
                keeps.emplace(v);
                ones.erase(v);
            }
        }
        for (auto v : ones)
            zeros.emplace(v);
        ones = std::move(keeps);

        // std::cerr << "zero: ";
        // for (auto v : zeros)
        //     std::cerr << v << " ";
        // std::cerr << "\n";

        // std::cerr << "one: ";
        // for (auto v : ones)
        //     std::cerr << v << " ";
        // std::cerr << "\n";

    }
    std::cout << res << "\n";
}

