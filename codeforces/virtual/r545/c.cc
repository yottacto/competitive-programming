// ml:run = $bin < input
#include <iostream>
#include <vector>

auto constexpr maxn = 100007;
auto constexpr maxd = 57;

int n, m, d;
std::vector<std::vector<int>> g;
std::vector<std::string> schedule;
bool vis[maxn * maxd];
bool vis_city[maxn];
int count;

auto id(int u, int day)
{
    return u * d + day;
}

void add_edge(int u, int v)
{
    for (auto i = 0; i < d; i++)
        g[id(u, i)].emplace_back(id(v, (i + 1)%d));
}

auto open(int city, int day)
{
    return schedule[city][day] == '1';
}

void dfs(int u)
{
    vis[u] = true;
    auto city = u / d;
    auto day = u % d;
    if (open(city, day) && !vis_city[city]) {
        if (city == 1)
            std::cerr << city << " " << day << "\n";
        vis_city[city] = true;
        count++;
    }
    for (auto v : g[u])
        if (!vis[v])
            dfs(v);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> d;
    g.resize(n * d);
    for (auto i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        add_edge(--u, --v);
    }
    schedule.resize(n);
    for (auto i = 0; i < n; i++)
        std::cin >> schedule[i];
    dfs(0);

    std::cout << count << "\n";
}

