// ml:run = $bin < input
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

auto constexpr inf = 1<<30;

namespace tue
{

struct priority_queue
{
    void emplace(int x)
    {
        q.emplace(x);
    }

    void remove(int x)
    {
        trash.emplace(x);
    }

    void clean_top_trash()
    {
        while (!trash.empty() && q.top() == trash.top()) {
            q.pop();
            trash.pop();
        }
    }

    auto top()
    {
        clean_top_trash();
        if (q.empty())
            return -inf;
        return q.top();
    }

    void pop()
    {
        clean_top_trash();
        q.pop();
    }

    std::priority_queue<int> q;
    std::priority_queue<int> trash;
};

} // namespace tue

std::vector<std::vector<int>> g;
std::vector<std::vector<int>> rev_g;
std::vector<int> in_degree;
std::vector<int> topo_seq;
std::vector<int> dist_s;
std::vector<int> dist_t;
int n, m;

void add_edge(int u, int v)
{
    in_degree[v]++;
    g[u].emplace_back(v);
    rev_g[v].emplace_back(u);
}

void init()
{
    std::scanf("%d%d", &n, &m);
    g.resize(n + 1);
    rev_g.resize(n + 1);
    in_degree.resize(n + 1);
    for (auto i = 0; i < m; i++) {
        int u, v;
        std::scanf("%d%d", &u, &v);
        add_edge(u, v);
    }
}

void topo_sort()
{
    std::queue<int> q;
    for (auto i = 1; i <= n; i++)
        if (!in_degree[i])
            q.emplace(i);
    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        topo_seq.emplace_back(now);
        for (auto v : g[now]) {
            in_degree[v]--;
            if (!in_degree[v])
                q.emplace(v);
        }
    }
}

void dp()
{
    dist_s.resize(n + 1);
    dist_t.resize(n + 1);

    for (auto u : topo_seq)
        for (auto v : g[u])
            dist_t[v] = std::max(dist_t[v], dist_t[u] + 1);

    for (auto it = topo_seq.rbegin(); it != topo_seq.rend(); ++it) {
        auto u = *it;
        for (auto v : rev_g[u])
            dist_s[v] = std::max(dist_s[v], dist_s[u] + 1);
    }
}

void work()
{
    tue::priority_queue s;
    tue::priority_queue t;
    tue::priority_queue cross;
    for (auto i : topo_seq)
        t.emplace(dist_s[i]);

    auto ans = inf;
    int pos;
    for (auto u : topo_seq) {
        t.remove(dist_s[u]);
        for (auto v : rev_g[u])
            cross.remove(dist_t[v] + dist_s[u] + 1);
        auto max = std::max(std::max(t.top(), s.top()), cross.top());
        s.emplace(dist_t[u]);
        for (auto v : g[u])
            cross.emplace(dist_t[u] + dist_s[v] + 1);
        if (max < ans) {
            ans = max;
            pos = u;
        }
    }
    std::printf("%d %d\n", pos, ans);
}

int main()
{
    init();
    topo_sort();
    dp();
    work();
}

