// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using ll = long long;
using range_type = std::pair<ll, ll>;

std::vector<ll> a;
std::vector<std::vector<int>> tree;
int n, g;
int au, av;
ll ans;
ll max;
ll k;


auto calc(range_type range, ll size)
{
    if (size <= 1)
        return range;
    range.first  = std::min(max + 1, range.first * size);
    range.second = std::min(max + 1, (range.second + 1) * size - 1);
    return range;
}

void dfs(int u, int parent, range_type range)
{
    auto next_range = calc(range, tree[u].size() - 1);
    auto leaf = true;
    for (auto v : tree[u]) {
        if (v == parent)
            continue;
        dfs(v, u, next_range);
        leaf = false;
    }
    if (leaf) {
        auto lower = std::lower_bound(a.begin(), a.end(), range.first);
        auto upper = std::upper_bound(a.begin(), a.end(), range.second);
        ans += (upper - lower) * k;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> g >> k;
    a.reserve(n);
    for (auto i = 0; i < g; i++) {
        ll t;
        std::cin >> t;
        a.emplace_back(t);
        max = std::max(max, t);
    }

    std::sort(a.begin(), a.end());

    tree.resize(n + 1);
    for (auto i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        if (i == 1) {
            au = u;
            av = v;
        }
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    dfs(au, av, {k, k});
    dfs(av, au, {k, k});

    std::cout << ans << "\n";
}

