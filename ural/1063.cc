// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <utility>
#include <numeric>

auto constexpr n = 6;
bool vis[7];
int father[7];
int d[7];
auto first_node = n;

auto get_father(int u) -> int
{
    return u == father[u] ? u : father[u] = get_father(father[u]);
}

void set_union(int u, int v)
{
    d[u]++;
    d[v]++;
    auto tu = get_father(u);
    auto tv = get_father(v);
    if (tu != tv)
        father[tu] = tv;
}

auto connected()
{
    for (auto i = first_node + 1; i <= n; i++)
        if (vis[i] && get_father(i) != get_father(first_node))
            return false;
    return true;
}

auto has_odd(int u)
{
    for (auto i = 1; i <= n; i++)
        if (vis[i] && get_father(i) == u && (d[i] & 1))
            return true;
    return false;
}

auto get_odd_min(int u)
{
    for (auto i = 1; i <= n; i++)
        if (vis[i] && get_father(i) == u && (d[i] & 1))
            return i;
    return n;
}

auto get_min(int u)
{
    for (auto i = 1; i <= n; i++)
        if (vis[i] && get_father(i) == u)
            return i;
    return n;
}

auto count_odd_pair(int u)
{
    auto count = 0;
    for (auto i = 1; i <= n; i++)
        if (vis[i] && get_father(i) == u && (d[i] & 1))
            count++;
    return count / 2;
}

int main()
{
    std::iota(father, father + n + 1, 0);
    int tot;
    std::cin >> tot;
    while (tot--) {
        int u, v;
        std::cin >> u >> v;
        vis[u] = vis[v] = true;
        set_union(u, v);
        first_node = std::min(first_node, std::min(u, v));
    }

    auto count = 0;
    std::vector<std::pair<int, int>> ans;
    while (!connected()) {
        auto first = get_father(first_node);
        auto second = 0;
        for (auto i = first_node + 1; i <= n; i++)
            if (get_father(i) != first) {
                second = get_father(i);
                break;
            }

        auto odd0 = has_odd(first);
        auto odd1 = has_odd(second);
        if (odd0 && odd1) {
            auto u = get_odd_min(first);
            auto v = get_odd_min(second);
            set_union(u, v);
            ans.emplace_back(u, v);
            count += u + v;
        } else {
            auto u = get_min(first);
            auto v = get_min(second);
            set_union(u, v);
            ans.emplace_back(u, v);
            count += u + v;
        }
    }

    int first;
    while (count_odd_pair(first = get_father(first_node)) > 1) {
        auto u = first_node;
        for (; u <= n; u++)
            if (vis[u] && (d[u] & 1))
                break;
        auto v = u + 1;
        for (; v <= n; v++)
            if (vis[v] && (d[v] & 1))
                break;

        set_union(u, v);
        ans.emplace_back(u, v);
        count += u + v;
    }

    std::cout << count << "\n";
    std::cout << ans.size() << "\n";
    for (auto const& p : ans)
        std::cout << p.first << " " << p.second << "\n";
}

