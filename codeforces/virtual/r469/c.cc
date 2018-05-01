// ml:run = $bin < input
#include <iostream>
#include <stack>
#include <vector>

auto constexpr maxn = 100004;
int u[maxn];
int n, m, h;
std::vector<std::vector<int>> g;

int low[maxn], dfn[maxn], color[maxn];
int count[maxn], out[maxn];
bool instack[maxn];
int tick, color_tick;
std::stack<int> stk;

void add_edge(int x, int y)
{
    if ((u[x] + 1) % h == u[y])
        g[x].emplace_back(y);
}

void tarjan(int u)
{
    low[u] = dfn[u] = ++tick;
    stk.push(u);
    instack[u] = true;
    for (auto v : g[u]) {
        if (!dfn[v]) {
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        } else if (instack[v])
            low[u] = std::min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int t;
        ++color_tick;
        do { t = stk.top(); stk.pop(); color[t] = color_tick; count[color_tick]++; } // FIXME instack[t] = false;
        while (t != u);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> h;
    g.resize(n + 1);

    for (auto i = 1; i <= n; i++)
        std::cin >> u[i];

    for (auto i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        add_edge(x, y);
        add_edge(y, x);
    }

    for (auto i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);

    for (auto i = 1; i <= n; i++)
        for (auto j : g[i])
            if (color[i] != color[j])
                out[color[i]]++;

    auto min = n + 1;
    auto c = 0;
    for (auto i = 1; i <= color_tick; i++)
        if (!out[i] && count[i] < min) {
            min = count[i];
            c = i;
        }

    std::cout << min << "\n";
    for (auto i = 1; i <= n; i++)
        if (color[i] == c)
            std::cout << i << " ";
    std::cout << "\n";
}

