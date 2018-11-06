// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>

auto constexpr maxn = 100007;
int root[maxn];
int n;
std::vector<int> da;

struct edge
{
    int v;
    int weight;
};

std::vector<std::vector<edge>> tree;

struct node
{
    int l;
    int r;
    int xor_sum;
};

node pst[maxn * 40];
int alloc;

auto get_id(int x)
{
    return std::upper_bound(da.begin(), da.end(), x) - da.begin();
}

auto get_value(int id)
{
    return da[id - 1];
}

void init()
{
    alloc = 0;
    da.clear();
    tree.clear();
    tree.resize(n + 1);
}

void add_edge(int u, int v, int w)
{
    tree[u].emplace_back(edge{v, w});
    tree[v].emplace_back(edge{u, w});
}

auto query(int u, int v, int tl, int tr, int l = 1, int r = da.size())
{
    if (tl <= l && r <= tr)
        return pst[u].xor_sum ^ pst[v].xor_sum;
    auto sum = 0;
    auto mid = (l + r) / 2;
    if (tl <= mid)
        sum ^= query(pst[u].l, pst[v].l, tl, tr, l, mid);
    if (mid < tr)
        sum ^= query(pst[u].r, pst[v].r, tl, tr, mid + 1, r);
    return sum;
}

void update(int& now, int pre, int pos, int w, int l = 1, int r = da.size())
{
    pst[now = ++alloc] = pst[pre];
    pst[now].xor_sum ^= w;
    if (l == r) return;
    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(pst[now].l, pst[pre].l, pos, w, l, mid);
    else
        update(pst[now].r, pst[pre].r, pos, w, mid + 1, r);
}

void dfs(int u, int p = 0, int d = 1, int w = 0)
{
    update(root[u], root[p], get_id(w), w);
    for (auto e : tree[u]) {
        auto v = e.v;
        auto w = e.weight;
        if (v == p) continue;
        dfs(v, u, d + 1, w);
    }
}

auto xor_sum(int u, int v, int k)
{
    if (k < da[0]) return 0;
    return query(root[u], root[v], 1, get_id(k));
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T; std::cin >> T;
    while (T--) {
        std::cin >> n;
        init();
        da.reserve(n + 1);
        for (auto i = 1; i < n; i++) {
            int u, v, w; std::cin >> u >> v >> w;
            da.emplace_back(w);
            add_edge(u, v, w);
        }

        std::sort(da.begin(), da.end());
        da.erase(std::unique(da.begin(), da.end()), da.end());

        dfs(1);

        int m; std::cin >> m;
        for (int u, v, k; m--; ) {
            std::cin >> u >> v >> k;
            std::cout << xor_sum(u, v, k) << "\n";
        }
    }
}

