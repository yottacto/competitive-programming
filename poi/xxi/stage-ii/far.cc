// ml:run = $bin < input
#include <cstdio>
#include <algorithm>
#include <vector>

auto constexpr maxn = 500007;
int cost[maxn];
std::vector<std::vector<int>> tree;
int n;

struct data
{
    int min;
    int travel;
};

auto dfs(int u, int parent = 0) -> data
{
    std::vector<data> da;
    auto res = data{cost[u], 0};
    for (auto v : tree[u]) {
        if (v == parent)
            continue;
        auto c = dfs(v, u);
        da.emplace_back(c);
    }
    std::sort(da.begin(), da.end(), [](auto const& lhs, auto const& rhs) {
        return rhs.min + lhs.travel < lhs.min + rhs.travel;
    });
    for (auto const& i : da) {
        res.min = std::max(res.min, i.min + res.travel + 1);
        res.travel += i.travel + 2;
    }
    return res;
}

int main()
{
    std::scanf("%d", &n);
    tree.resize(n + 1);
    for (auto i = 1; i <= n; i++)
        std::scanf("%d", &cost[i]);
    for (auto i = 1; i < n; i++) {
        int u, v;
        std::scanf("%d%d", &u, &v);
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
    auto res = dfs(1);
    std::printf("%d\n", std::max(res.min, res.travel + cost[1]));
}

