// ml:run = $bin < input
#include <bits/stdc++.h>

std::vector<std::unordered_set<int>> tree;
std::vector<std::vector<int>> g;
std::vector<int> h;
std::vector<int> seq;
std::vector<int> op;
int n;

struct data
{
    int h;
    int id;
};

void dfs(int u)
{
    auto maxh = 0;
    std::vector<data> tmp;
    for (auto v : tree[u]) {
        dfs(v);
        tmp.emplace_back(data{h[v], v});
        maxh = std::max(maxh, h[v]);
    }
    std::sort(tmp.begin(), tmp.end(), [](auto const& a, auto const& b) {
        return a.h < b.h;
    });
    g[u].reserve(tmp.size());
    for (auto const& i : tmp)
        g[u].emplace_back(i.id);
    h[u] = maxh + 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n;
    tree.resize(n);
    g.resize(n);
    h.resize(n);
    for (auto i = 1; i <= n - 1; i++) {
        int p;
        std::cin >> p;
        tree[p].emplace(i);
    }

    dfs(0);

    auto u = 0;
    seq.emplace_back(u);
    while (!g[u].empty()) {
        int tn = g[u].size();
        for (auto i = tn - 1; i >= 1; i--)
            op.emplace_back(g[u][i]);
        seq.emplace_back(g[u][0]);
        for (auto i = tn - 2; i >= 0; i--) {
            auto v = g[u][i];
            auto w = g[u][i + 1];
            g[v].emplace_back(w);
            h[w]++;
        }
        u = g[u][0];
    }

    for (auto i : seq)
        std::cout << i << " ";
    std::cout << "\n";

    int num_op = op.size();
    std::cout << num_op << "\n";
    for (auto i = num_op - 1; i >= 0; i--)
        std::cout << op[i] << " ";
    std::cout << "\n";
}

