// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <utility>

auto constexpr maxn = 100007;
auto constexpr maxd = 57;
bool open[maxn][maxd];
int vis[maxn];
int value[maxn * maxd];
int f[maxn * maxd];
int top;
int n, m, d;
std::vector<int> g[maxn];
std::vector<int> cg[maxn * maxd];

using pair_type = std::pair<int, int>;
pair_type stk[maxn * maxd];
int dfn[maxn][maxd];
int low[maxn][maxd];
int color[maxn][maxd];
int tick;
int color_tick;

inline void tarjan(int u, int t)
{
    low[u][t] = dfn[u][t] = ++tick;
    stk[top++] = {u, t};
    auto nt = (t + 1) % d;
    for (auto v : g[u]) {
        if (color[v][nt]) {
            continue;
        } else if (dfn[v][nt]) {
            low[u][t] = std::min(low[u][t], dfn[v][nt]);
        } else {
            tarjan(v, nt);
            low[u][t] = std::min(low[u][t], low[v][nt]);
        }
    }
    if (low[u][t] == dfn[u][t]) {
        int v, nt;
        ++color_tick;
        do {
            --top;
            v = stk[top].first;
            nt = stk[top].second;
            color[v][nt] = color_tick;
            if (open[v][nt] && vis[v] != color_tick) {
                vis[v] = color_tick;
                value[color_tick]++;
            }
        } while (v != u || nt != t);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> d;
    for (auto i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        g[--u].emplace_back(--v);
    }
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < d; j++) {
            char ch;
            std::cin >> ch;
            open[i][j] = ch == '1';
        }
    }

    tarjan(0, 0);

    for (auto u = 0; u < n; u++)
        for (auto t = 0; t < d; t++)
            for (auto v : g[u]) {
                auto nt = (t + 1) % d;
                if (color[u][t] != color[v][nt])
                    cg[color[u][t]].emplace_back(color[v][nt]);
            }

    for (auto i = 1; i <= color_tick; i++) {
        for (auto j : cg[i])
            f[i] = std::max(f[i], f[j]);
        f[i] += value[i];
    }
    std::cout << f[color[0][0]] << "\n";
}

