// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <vector>

auto constexpr maxn = 100007;
auto constexpr inf = 1<<30;
int f[maxn];
int c[maxn];
int n;
std::vector<std::vector<int>> g;
std::vector<char> leaf;

int dp(int u)
{
    if (leaf[u])
        return inf;
    for (auto v : g[u])
        f[u] += std::min(dp(v), c[v]);
    return f[u];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    g.resize(n + 1);
    leaf.resize(n + 1, 1);
    for (auto i = 2; i <= n; i++) {
        int parent;
        std::cin >> parent >> c[i];
        leaf[parent] = 0;
        g[parent].emplace_back(i);
    }
    std::cout << std::fixed << std::setprecision(2)
        << (double)dp(1) << "\n";
}

