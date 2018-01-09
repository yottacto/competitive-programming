// ml:run = $bin < input
#include <iostream>
#include <vector>

struct edge
{
    int v;
    int id;
};

int n, m, count;
bool vis[100];
std::vector<int> ans;
std::vector<std::vector<edge>> g;

void dfs(int u)
{
    vis[u] = true;
    for (auto e : g[u]) {
        auto v = e.v;
        auto id = e.id;
        if (!ans[id]) ans[id] = ++count;
        if (!vis[v]) dfs(v);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    g.resize(n + 1);
    ans.resize(m);
    for (int i = 0; i < m; i++) {
        int x, y; std::cin >> x >> y;
        g[x].emplace_back(edge{y, i});
        g[y].emplace_back(edge{x, i});
    }

    for (int i = 1; i <= n; i++)
        if (!vis[i])
            dfs(1);

    std::cout << "YES\n";
    for (auto i : ans)
        std::cout << i << " ";
    std::cout << "\n";
}

