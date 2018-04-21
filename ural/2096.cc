// ml:run = $bin < input
#include <iostream>
#include <vector>

struct query { int day; int plan; int id; };
struct change { int first; int tot; int period; int act; };
struct restore { int day; int act; };

auto& operator>>(std::istream& is, change& c)
{
    is >> c.first >> c.tot >> c.period >> c.act;
    c.first--;
    return is;
}

int n, m;
std::vector<int> a;
std::vector<std::vector<int>> g;
std::vector<std::vector<query>> queries;
std::vector<std::vector<change>> changes;
std::vector<std::vector<restore>> restores;
std::vector<std::vector<int>> ans;

void add_edge(int u, int v)
{
    g[u].emplace_back(v);
    g[v].emplace_back(u);
}

void forward_change(int u)
{
    for (auto const& c : changes[u])
        for (auto d = c.first, i = 0; i < c.tot; d += c.period, i++)
            restores[u].emplace_back(restore{d, a[d]});

    for (auto const& c : changes[u])
        for (auto d = c.first, i = 0; i < c.tot; d += c.period, i++)
            a[d] = c.act;
}

void backward_change(int u)
{
    for (auto const& r : restores[u])
        a[r.day] = r.act;
}

void dfs(int u, int parent)
{
    forward_change(u);
    for (auto const& q : queries[u])
        ans[q.plan][q.id] = a[q.day];
    for (auto v : g[u]) {
        if (v == parent)
            continue;
        dfs(v, u);
    }
    backward_change(u);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    a.resize(n);
    g.resize(m + 1);
    queries.resize(m + 1);
    changes.resize(m + 1);
    restores.resize(m + 1);
    ans.resize(m);

    for (auto& i : a)
        std::cin >> i;

    for (auto i = 0; i < m; i++) {
        int q;
        std::cin >> q;
        ans[i].resize(q);
        for (auto id = 0; id < q; id++) {
            int plan, day;
            std::cin >> plan >> day;
            queries[plan].emplace_back(query{day - 1, i, id});
        }
        int basis, count;
        std::cin >> basis >> count;
        add_edge(basis, i + 1);
        changes[i + 1].resize(count);
        for (auto& c : changes[i + 1])
            std::cin >> c;
    }

    dfs(0, -1);

    for (auto const& v : ans) {
        for (auto i : v)
            std::cout << i << " ";
        std::cout << "\n";
    }
}

