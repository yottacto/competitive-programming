// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <unordered_set>
#include <vector>
#include <utility>
#include <numeric>

auto constexpr n = 6;
auto constexpr size = n + 1;

std::vector<int> degree(size);
std::vector<int> father(size);
bool vis[size];

struct edge { int u; int v; };

// edges connect two component
std::vector<edge> edges;
std::vector<edge> ans;
auto best = 100;

template <class Vec>
auto get_father(int x, Vec& father) -> int
{
    return x == father[x]
        ? x
        : father[x] = get_father(father[x], father);
}

template <class Vec>
void set_union(int u, int v, Vec& father, Vec& degree)
{
    degree[u]++;
    degree[v]++;
    auto tu = get_father(u, father);
    auto tv = get_father(v, father);
    if (tu != tv)
        father[tu] = tv;
}

template <class Vec>
auto odd_pair(Vec const& father, Vec const& degree)
{
    auto count = 0;
    for (auto i = 1; i <= n; i++)
        if (vis[i] && (degree[i] & 1))
            count++;
    return count / 2;
}

template <class Vec>
void add_odd_pair(Vec& father, Vec& degree, int& cost,
    std::vector<edge>& chose)
{
    auto count = 0;
    auto u = 1;
    for (; u <= n; u++)
        if (vis[u] && (degree[u] & 1))
            break;
    auto v = u + 1;
    for (; v <= n; v++)
        if (vis[v] && (degree[v] & 1))
            break;
    set_union(u, v, father, degree);
    cost += u + v;
    chose.emplace_back(edge{u, v});
}

// count for connected components
void dfs(std::size_t id, int count, int cost,
    std::vector<int> father,
    std::vector<int> degree,
    std::vector<edge>& chose)
{
    if (count == 1) {
        auto tsize = chose.size();
        while (odd_pair(father, degree) > 1)
            add_odd_pair(father, degree, cost, chose);
        if (cost < best) {
            best = cost;
            ans = chose;
        }
        chose.resize(tsize);
        return;
    }

    for (auto i = id; i < edges.size(); i++) {
        auto u = edges[i].u;
        auto v = edges[i].v;
        if (get_father(u, father) == get_father(v, father))
            continue;
        if (cost + u + v >= best)
            continue;
        chose.emplace_back(edges[i]);
        {
            auto tf = father;
            auto td = degree;
            set_union(u, v, tf, td);
            dfs(i + 1, count - 1, cost + u + v, std::move(tf), std::move(td), chose);
            // dfs(i + 1, count - 1, cost + u + v, tf, td, chose);
        }
        chose.pop_back();
    }
}

int main()
{
    std::iota(std::begin(father), std::end(father), 0);
    int tot;
    std::cin >> tot;
    while (tot--) {
        int u, v;
        std::cin >> u >> v;
        vis[u] = vis[v] = true;
        set_union(u, v, father, degree);
    }

    for (auto i = 1; i <= n; i++) {
        if (!vis[i]) continue;
        for (auto j = i + 1; j <= n; j++) {
            if (!vis[j] || get_father(i, father) == get_father(j, father))
                continue;
            edges.emplace_back(edge{i, j});
        }
    }

    std::unordered_set<int> count;
    for (auto i = 1; i <= n; i++)
        if (vis[i])
            count.insert(get_father(i, father));

    std::vector<edge> chose;
    dfs(0, count.size(), 0, father, degree, chose);

    std::cout << best << "\n";
    std::cout << ans.size() << "\n";
    for (auto const& e: ans)
        std::cout << e.u << " " << e.v << "\n";
}

