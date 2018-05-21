// ml:run = $bin < input
#include <iostream>

using ll = long long;

auto constexpr maxn = 1000007;
int f[maxn];
int value[maxn];
int last[maxn];
int prev[maxn];
ll max[4 * maxn];
ll cover[4 * maxn];
int n, m;

void push_down(int id)
{
    if (!cover[id]) return;
    cover[id * 2]     += cover[id];
    cover[id * 2 + 1] += cover[id];
    max[id * 2]     += cover[id];
    max[id * 2 + 1] += cover[id];
    cover[id] = 0;
}

void push_up(int id)
{
    max[id] = std::max(max[id * 2], max[id * 2 + 1]);
}

ll query(int id, int l, int r, int tl, int tr)
{
    if (tl <= l && r <= tr)
        return max[id];
    push_down(id);
    auto mid = (l + r) / 2;
    auto max = 0ll;
    if (tl <= mid)
        max = query(id * 2, l, mid, tl, tr);
    if (tr > mid)
        max = std::max(max, query(id * 2 + 1, mid + 1, r, tl, tr));
    return max;
}

void update(int id, int l, int r, int tl, int tr, ll delta)
{
    if (tl > tr) return;
    if (tl <= l && r <= tr) {
        cover[id] += delta;
        max[id] += delta;
        return;
    }
    push_down(id);
    auto mid = (l + r) / 2;
    if (tl <= mid)
        update(id * 2, l, mid, tl, tr, delta);
    if (tr > mid)
        update(id * 2 + 1, mid + 1, r, tl, tr, delta);
    push_up(id);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    for (auto i = 1; i <= n; i++) {
        std::cin >> f[i];
        prev[i] = last[f[i]];
        last[f[i]] = i;
    }
    for (auto i = 1; i <= m; i++)
        std::cin >> value[i];

    auto ans = 0ll;
    for (auto i = 1; i <= n; i++) {
        auto id = f[i];
        update(1, 1, n, prev[i] + 1, i, value[id]);
        update(1, 1, n, prev[prev[i]] + 1, prev[i], -value[id]);
        ans = std::max(ans, query(1, 1, n, 1, i));

        // std::cerr << i << " " << query(1, 1, n, 1, i) << "\n";
    }
    std::cout << ans << "\n";
}

