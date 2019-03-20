// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
#include <unordered_set>
#include <queue>

auto constexpr maxn = 100007;
auto constexpr maxd = 57;

int n, m, d;
std::vector<std::vector<int>> g;
std::vector<std::string> schedule;
std::unordered_set<int> value[maxn * maxd];

std::vector<std::unordered_set<int>> gg;
std::vector<std::unordered_set<int>> gg_rev;
std::vector<int> outdegree;
std::vector<int> dp;

// need for tarjan
std::vector<int> low;
std::vector<int> dfn;
std::vector<int> color;
bool instack[maxn * maxd];
int tick, color_tick;
std::stack<int> stk;

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

void tarjan(int u, int parent)
{
    low[u] = dfn[u] = ++tick;
    stk.push(u);
    instack[u] = true;
    for (auto v : g[u]) {
        if (v == parent) continue;
        if (!dfn[v]) {
            tarjan(v, u);
            low[u] = std::min(low[u], low[v]);
        } else if (instack[v])
            low[u] = std::min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        int t;
        ++color_tick;
        do {
            t = stk.top();
            stk.pop();
            instack[t] = false;
            color[t] = color_tick;
        }
        while (t != u);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> d;
    g.resize(n * d);
    low.resize(n * d);
    dfn.resize(n * d);
    color.resize(n * d);
    for (auto i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        add_edge(--u, --v);
    }
    schedule.resize(n);
    for (auto i = 0; i < n; i++)
        std::cin >> schedule[i];

    for (auto i = 0; i < n * d; i++)
        if (!dfn[i])
            tarjan(i, -1);

    gg.resize(color_tick + 1);
    gg_rev.resize(color_tick + 1);
    outdegree.resize(color_tick + 1);
    dp.resize(color_tick + 1);
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < d; j++) {
            auto u = id(i, j);
            if (open(i, j))
                value[color[u]].emplace(i);
            for (auto v : g[u])
                if (!gg[color[u]].count(color[v])) {
                    gg[color[u]].emplace(color[v]);
                    gg_rev[color[v]].emplace(color[u]);
                    outdegree[color[u]]++;
                }
        }
    std::queue<int> q;
    for (auto i = 1; i <= color_tick; i++)
        if (!outdegree[i])
            q.emplace(i);

    std::vector<int> seq;
    seq.reserve(color_tick);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        seq.emplace_back(v);
        // u -> v
        for (auto u : gg_rev[v]) {
            outdegree[u]--;
            if (!outdegree[u])
                q.emplace(u);
        }
    }

    for (auto u : seq) {
        auto max = 0;
        for (auto v : gg[u])
            max = std::max(max, dp[v]);
        dp[u] = max + value[u].size();
    }

    std::cout << dp[color[0]] << "\n";
}

