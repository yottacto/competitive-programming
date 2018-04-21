// ml:run = $bin < input
#include <iostream>
#include <utility>
#include <algorithm>
#include <vector>
#include <unordered_map>

struct query { int day; int plan; int id; };
struct change { int first; int tot; int period; int act; };
struct restore { int day; int act; };

auto& operator>>(std::istream& is, change& c)
{
    is >> c.first >> c.tot >> c.period >> c.act;
    c.first--;
    return is;
}

auto constexpr maxn = 100'010;
auto constexpr maxchange = 5'000'010;

template <class T, int N, int MAXN>
struct pool
{
    pool()
    {
        std::fill(next, next + MAXN, 0);
        std::fill(head, head + N, 0);
    }

    void push(int id, T&& v)
    {
        value[alloc] = v;
        if (!head[id]) {
            tail[id] = alloc;
            head[id] = alloc++;
        } else {
            next[tail[id]] = alloc;
            tail[id] = alloc++;
        }
    }

    T value[MAXN];
    int next[MAXN];
    int head[N];
    int tail[N];
    int alloc{1};
};

int n, m;
int a[maxn];
std::vector<int> g[maxn];
// std::vector<query> queries[maxn];
pool<query, maxn, maxn> queries;
// std::vector<change> changes[maxn];
pool<change, maxn, maxn> changes;
pool<restore, maxn, maxchange> restores;
// std::unordered_map<int, int> restores[maxn];
std::vector<int> ans[maxn];

void add_edge(int u, int v)
{
    g[u].emplace_back(v);
}

void forward_change(int u)
{
    // for (auto const& c : changes[u])
    for (auto p = changes.head[u]; p; p = changes.next[p]) {
        auto const& c = changes.value[p];
        for (auto d = c.first, i = 0; i < c.tot; d += c.period, i++)
            restores.push(u, {d, a[d]});
                // restores[u][d] = a[d];
            // restores[u].emplace_back(restore{d, a[d]});
    }

    // for (auto const& c : changes[u])
    for (auto p = changes.head[u]; p; p = changes.next[p]) {
        auto const& c = changes.value[p];
        for (auto d = c.first, i = 0; i < c.tot; d += c.period, i++)
            a[d] = c.act;
    }
}

void backward_change(int u)
{
    for (auto p = restores.head[u]; p; p = restores.next[p]) {
        auto const& r = restores.value[p];
        a[r.day] = r.act;
    }
}

void dfs(int u)
{
    forward_change(u);
    // for (auto const& q : queries[u])
    for (auto p = queries.head[u]; p; p = queries.next[p]) {
        auto const& q = queries.value[p];
        ans[q.plan][q.id] = a[q.day];
    }
    for (auto v : g[u])
        dfs(v);
    backward_change(u);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;

    // auto size = (sizeof(change)*maxn
    //     + sizeof(query)*maxn
    //     + sizeof(restore)*maxchange);
    // std::cout << size/1024/1024 << "\n";

    // a.resize(n);
    // g.resize(m + 1);
    // queries.resize(m + 1);
    // changes.resize(m + 1);
    // restores.resize(m + 1);

    for (auto i = 0; i < n; i++)
        std::cin >> a[i];

    for (auto i = 0; i < m; i++) {
        int q;
        std::cin >> q;
        ans[i].resize(q);
        for (auto id = 0; id < q; id++) {
            int plan, day;
            std::cin >> plan >> day;
            // queries[plan].emplace_back(query{day - 1, i, id});
            queries.push(plan, query{day - 1, i, id});
        }
        int basis, count;
        std::cin >> basis >> count;
        add_edge(basis, i + 1);
        // changes[i + 1].resize(count);
        while (count--) {
            change c;
            std::cin >> c;
            changes.push(i + 1, std::move(c));
        }
        // for (auto& c : changes[i + 1])
        //     std::cin >> c;
    }

    dfs(0);

    for (auto i = 0; i < m; i++) {
        for (auto j : ans[i])
            std::cout << j << " ";
        std::cout << "\n";
    }
}

