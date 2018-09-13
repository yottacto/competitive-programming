// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>

using pair = std::pair<int, int>;

static auto constexpr maxn = 500007;
static auto constexpr inf = 1<<29;

int d[maxn], h[maxn], endh[maxn];
int compl_d[maxn], compl_h[maxn], compl_endh[maxn];
pair end_points[maxn];
pair compl_end_points[maxn];

std::vector<std::vector<int>> tree;

int n;
pair min_ep1, min_ep2;
auto mid = false;

struct max_three
{
    void shift(int p)
    {
        for (auto i = 2; i >= p + 1; i--) {
            id[i] = id[i - 1];
            a[i] = a[i - 1];
        }
    }

    void push(int v, int tid)
    {
        for (auto i = 0; i < 3; i++) {
            if (!id[i] || a[i] <= v) {
                shift(i);
                a[i] = v;
                id[i] = tid;
                return;
            }
        }
    }

    auto sum_max(int p)
    {
        auto sum = 0;
        for (auto i = 0; i < p; i++) {
            if (!id[i]) return -inf;
            sum += a[i];
        }
        return sum;
    }

    auto get_max_except(int i)
    {
        if (!id[0]) return -inf;
        if (id[0] != i) { u = id[0]; return a[0]; }
        if (!id[1]) return -inf;
        u = id[1];
        return a[1];
    }

    auto get_max2_except(int i)
    {
        if (!id[1]) return -inf;
        if (id[0] != i) {
            u = id[0];
            if (id[1] != i) {
                v = id[1];
                return a[0] + a[1];
            }
            if (!id[2]) return -inf;
            v = id[2];
            return a[0] + a[2];
        }
        if (!id[2]) return -inf;
        u = id[1];
        v = id[2];
        return a[1] + a[2];
    }

    int a[3] = {};
    int id[3] = {};
    int u, v;
};

auto ans_min = inf;
int min_ru, min_rv, min_au, min_av;
auto ans_max = 0;
int max_ru, max_rv, max_au, max_av;

void dfs(int u, int parent)
{
    d[u] = h[u] = 0;
    endh[u] = u;
    end_points[u] = {u, u};
    max_three mt;
    for (auto v : tree[u]) {
        if (v == parent)
            continue;

        dfs(v, u);

        if (d[v] > d[u]) {
            d[u] = d[v];
            end_points[u] = end_points[v];
        }

        if (h[v] + 1 > d[u]) {
            d[u] = h[v] + 1;
            end_points[u] = {u, endh[v]};
        }

        if (h[v] + 1 > h[u]) {
            h[u] = h[v] + 1;
            endh[u] = endh[v];
        }

        mt.push(h[v], v);
    }
    if (d[u] < mt.sum_max(2) + 2) {
        d[u] = mt.sum_max(2) + 2;
        end_points[u] = {endh[mt.id[0]], endh[mt.id[1]]};
    }

}

void dfs2(int u, int parent)
{
    max_three mt;
    max_three mt2;
    for (auto v : tree[u]) {
        if (v == parent)
            continue;
        mt.push(h[v], v);
        mt2.push(d[v], v);
    }

    for (auto v : tree[u]) {
        if (v == parent)
            continue;

        compl_h[v] = compl_d[v] = 0;
        compl_endh[v] = u;
        compl_end_points[v] = {u, u};

        if (compl_h[v] < compl_h[u] + 1) {
            compl_h[v] = compl_h[u] + 1;
            compl_endh[v] = compl_endh[u];
        }

        if (compl_h[v] < mt.get_max_except(v) + 1) {
            compl_h[v] = mt.get_max_except(v) + 1;
            compl_endh[v] = endh[mt.u];
        }

        if (compl_d[v] < compl_h[v]) {
            compl_d[v] = compl_h[v];
            compl_end_points[v] = {u, compl_endh[v]};
        }

        // parent with sibling
        if (compl_d[v] < compl_h[u] + mt.get_max_except(v) + 2) {
            compl_d[v] = compl_h[u] + mt.get_max_except(v) + 2;
            compl_end_points[v] = {compl_endh[u], endh[mt.u]};
        }

        // two siblings
        if (compl_d[v] < mt.get_max2_except(v) + 2) {
            compl_d[v] = mt.get_max2_except(v) + 2;
            compl_end_points[v] = {endh[mt.u], endh[mt.v]};
        }

        if (compl_d[v] < compl_d[u]) {
            compl_d[v] = compl_d[u];
            compl_end_points[v] = compl_end_points[u];
        }

        if (compl_d[v] < mt2.get_max_except(v)) {
            compl_d[v] = mt2.get_max_except(v);
            compl_end_points[v] = compl_end_points[mt2.u];
        }


        auto min_d = std::max(d[v], compl_d[v]);
        min_d = std::max(min_d, (d[v] + 1) / 2 + (compl_d[v] + 1) / 2 + 1);

        if (ans_min > min_d) {
            ans_min = min_d;
            min_ru = u;
            min_rv = v;
            if (std::max(d[v], compl_d[v]) == min_d) {
                min_au = u;
                min_av = v;
                mid = false;
            } else {
                min_ep1 = end_points[v];
                min_ep2 = compl_end_points[v];
                mid = true;
            }
        }

        auto max_d = d[v] + compl_d[v] + 1;
        if (ans_max < max_d) {
            ans_max = max_d;
            max_ru = u;
            max_rv = v;
            max_au = end_points[v].second;
            max_av = compl_end_points[v].second;
        }

        dfs2(v, u);
    }

}

std::vector<int> path;

int dfs3(int u, int parent, int t)
{
    path.emplace_back(u);
    if (t == u)
        return path[path.size() / 2];
    for (auto v : tree[u]) {
        if (v == parent)
            continue;
        auto mid = dfs3(v, u, t);
        if (mid >= 0)
            return mid;
    }
    path.pop_back();
    return -1;
}

auto find_mid(pair const& p)
{
    auto u = p.first;
    auto v = p.second;
    path.clear();
    path.reserve(n);
    return dfs3(u, -1, v);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    tree.resize(n);
    for (auto i = 1; i < n; i++) {
        int u, v;
        std::cin >> u >> v;
        u--; v--;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }

    dfs(0, -1);

    compl_h[0] = compl_d[0] = -inf;
    dfs2(0, -1);

    if (mid) {
        min_au = find_mid(min_ep1);
        min_av = find_mid(min_ep2);
    }

    std::cout << ans_min << " " << min_ru + 1 << " " << min_rv + 1 << " " << min_au + 1 << " " << min_av + 1 << "\n";
    std::cout << ans_max << " " << max_ru + 1 << " " << max_rv + 1 << " " << max_au + 1 << " " << max_av + 1 << "\n";
}

