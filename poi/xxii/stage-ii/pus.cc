// ml:run = $bin < input
// ml:std = c++11
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

auto constexpr maxn = 100007;
auto constexpr inf = 1000000000;
int id[maxn];
int n, s, m;
int tot;

int alloc()
{
    return tot++;
}

int left[4 * maxn];
int right[4 * maxn];
int root;

struct edge
{
    int len;
    int to;
};

std::vector<edge> g[5 * maxn];
int in_degree[5 * maxn];
int f[5 * maxn];
int a[5 * maxn];

// u --l--> v
void add_edge(int u, int v, int len)
{
    in_degree[v]++;
    g[u].emplace_back(edge{len, v});
}

void add_edges(int id, int l, int r, int tl, int tr, int tid)
{
    if (tl > tr) return;
    if (tl == l && tr == r) {
        add_edge(id, tid, 1);
        return;
    }
    auto mid = (l + r) / 2;
    if (tl <= mid)
        add_edges(left[id], l, mid, tl, std::min(tr, mid), tid);
    if (tr > mid)
        add_edges(right[id], mid + 1, r, std::max(mid + 1, tl), tr, tid);
}

int build_tree(int& id, int l, int r)
{
    id = alloc();
    // std::cerr << id << ": [" << l << ", " << r << "]\n";
    if (l == r) {
        ::id[l] = id;
        return id;
    }
    auto mid = (l + r) / 2;
    add_edge(build_tree(left[id],  l,       mid), id, 0);
    add_edge(build_tree(right[id], mid + 1, r),   id, 0);
    return id;
}

bool topo()
{
    std::queue<int> q;
    for (auto i = 0; i < tot; i++)
        if (!in_degree[i]) {
            q.push(i);
            f[i] = 1;
        }
    auto count = 0;
    for (; !q.empty(); count++) {
        auto now = q.front();
        q.pop();
        if (f[now] > inf || (a[now] && f[now] > a[now]))
            return false;
        f[now] = std::max(f[now], a[now]);
        // std::cerr << "now = " << now << ", f[now] = " << f[now] << "\n";
        for (auto const& e : g[now]) {
            auto len = e.len;
            auto v = e.to;
            f[v] = std::max(f[v], f[now] + len);
            in_degree[v]--;
            if (!in_degree[v])
                q.push(v);
        }
    }
    return count == tot;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> s >> m;
    build_tree(root, 1, n);
    for (auto i = 0; i < s; i++) {
        int p, d;
        std::cin >> p >> d;
        a[id[p]] = d;
    }
    for (auto i = 0; i < m; i++) {
        int l, r, k;
        std::cin >> l >> r >> k;
        auto tl = l - 1;
        auto tid = alloc();
        for (auto j = 0; j < k; j++) {
            int tr;
            std::cin >> tr;
            add_edge(tid, id[tr], 0);
            add_edges(root, 1, n, tl + 1, tr - 1, tid);
            tl = tr;
        }
        add_edges(root, 1, n, tl + 1, r, tid);
    }
    if (topo()) {
        std::cout << "TAK\n";
        for (auto i = 1; i <= n; i++)
            std::cout << f[id[i]] << " ";
        std::cout << "\n";
    } else
        std::cout << "NIE\n";
}

