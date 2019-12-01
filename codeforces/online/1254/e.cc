// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
using pair = std::pair<int, int>;
auto constexpr mo = 1000000007ll;
auto constexpr maxn = 500'007;
int depth[maxn];
int parent[maxn];
ll fact[maxn];
int n;
std::vector<std::vector<int>> tree;
std::vector<int> a;
std::vector<std::vector<pair>> edges;

template <class T, class U>
auto mul(T a, U b)
{
    return (a * b) % mo;
}

template <class T, class... Args>
auto mul(T x, Args... args)
{
    return mul(x, mul(args...));
}

void dfs(int u, int parent)
{
    ::parent[u] = parent;
    depth[u] = depth[parent] + 1;
    for (auto v : tree[u])
        if (v != parent)
            dfs(v, u);
}

void no_solution()
{
    std::cout << "0\n";
    exit(0);
}

std::vector<int> in;
std::vector<int> out;
std::vector<int> next;
std::vector<char> vis;

ll calc(int p)
{
    auto& nodes = tree[p];
    auto& edges = ::edges[p];
    nodes.emplace_back(0);
    nodes.emplace_back(n + 1);
    for (auto const& e : edges) {
        in[e.second]++;
        out[e.first]++;
        next[e.first] = e.second;
    }
    for (auto v : nodes)
        if (in[v] > 1 || out[v] > 1)
            no_solution();

    for (auto v : nodes) {
        if (vis[v])
            continue;
        vis[v] = true;
        auto u = v;
        for (; next[u] != -1 && !vis[next[u]]; u = next[u])
            vis[next[v]] = true;
        if (next[u] == v)
            no_solution();
    }
    auto u = 0;
    for (; next[u] != -1; u = next[u])
        ;
    int tot_n = nodes.size();
    int tot_e = edges.size();
    if (u == n + 1 && tot_n - 1 > tot_e)
        no_solution();

    for (auto v : nodes) {
        in[v] = out[v] = 0;
        next[v] = -1;
        vis[v] = false;
    }

    return std::max(0, tot_n - 2 - tot_e);
}

std::vector<int> path;
std::vector<int> head;
std::vector<int> tail;
// u->v
void get_path(int u, int v)
{
    head.clear();
    tail.clear();
    while (u != v) {
        if (depth[u] > depth[v]) {
            head.emplace_back(u);
            u = parent[u];
        } else {
            tail.emplace_back(v);
            v = parent[v];
        }
    }
    head.emplace_back(v);
    path = head;
    for (auto it = tail.rbegin(); it != tail.rend(); ++it)
        path.emplace_back(*it);
}

void work()
{
    auto dis = 0ll;
    for (auto i = 1; i <= n; i++)
        if (a[i]) {
            if (a[i] == i)
                no_solution();
            get_path(a[i], i);
            int m = path.size();

            dis += m - 1;
            // make sure worst case time complexity
            if (dis > 2 * n - 2)
                no_solution();
            edges[path[0]].emplace_back(0, path[1]);
            edges[path[m - 1]].emplace_back(path[m - 2], n + 1);
            for (auto i = 1; i < m - 1 ; i++)
                edges[path[i]].emplace_back(path[i - 1], path[i + 1]);
        }
    auto res = 1ll;
    for (auto i = 1; i <= n; i++)
        res = mul(res, fact[calc(i)]);
    std::cout << res << "\n";
}

void init()
{
    tree.resize(n + 1);
    edges.resize(n + 1);
    a.resize(n + 1);
    fact[0] = 1;
    for (auto i = 1; i <= n; i++)
        fact[i] = mul(fact[i - 1], i);

    in.resize(n + 2);
    out.resize(n + 2);
    next.resize(n + 2, -1);
    vis.resize(n + 2);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n;
    init();

    for (auto i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
    for (auto i = 1; i <= n; i++)
        std::cin >> a[i];

    dfs(1, 0);

    work();
}

