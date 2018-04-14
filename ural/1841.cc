// ml:run = $bin < input
// ml:ccf += -g
// ml:opt = 0
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

using ll = long long;

struct data
{
    int x;
    ll v;
    // 0 means not a cableway
    int t;
};

auto constexpr maxn = 2000002;
auto constexpr inf = 1ll << 40;
int tree[maxn];
int pos[maxn];

std::vector<data> da;
std::vector<int> disc;
std::vector<int> seg;
std::vector<ll> dist;
int n;

auto constexpr delta = 1000001;

template <class T>
T abs(T x) { return x < 0 ? -x : x; }

void trans(int& x) { x += delta; }
int trans_back(int x) { return x - delta; }

auto lowbit(int x) { return x & (-x); }

auto sum(int p)
{
    auto ret = 0;
    for (; p; p -= lowbit(p))
        ret += tree[p];
    return ret;
}

auto update(int p, int d)
{
    for (; p < maxn; p += lowbit(p))
        tree[p] += d;
}

auto bin_search(int pl, int pr)
{
    auto l = pl;
    auto r = pr;
    while (l + 1 < r) {
        auto mid = (l + r) / 2;
        if (sum(mid) - sum(pl - 1))
            r = mid;
        else
            l = mid;
    }
    if (sum(l) - sum(pl - 1))
        return l;
    return r;
}

int main()
{
    std::cin >> n;
    seg.resize(n + 1);
    for (auto i = 0; i <= n; i++) {
        std::cin >> seg[i];
        trans(seg[i]);
        disc.emplace_back(seg[i]);
    }
    for (auto i = 0; i < n; i++) {
        int v, m;
        std::cin >> v >> m;
        da.emplace_back(data{seg[i], v, 0});
        while (m--) {
            int x, t;
            std::cin >> x >> t;
            trans(x);
            da.emplace_back(data{x, v, t});
            disc.emplace_back(x);
        }
        da.emplace_back(data{seg[i + 1], v, 0});
    }

    for (auto i = 1u; i < da.size(); i++)
        if (da[i - 1].x == da[i].x && da[i - 1].v == da[i].v && da[i - 1].t)
            // FIXME v
            std::swap(da[i - 1], da[i]);

    std::sort(std::begin(disc), std::end(disc));
    auto last = std::unique(std::begin(disc), std::end(disc));
    disc.erase(last, std::end(disc));

    dist.resize(da.size(), inf);
    dist[0] = 0;
    for (auto i = 1u; i < da.size(); i++) {
        auto x = da[i].x;
        auto v = da[i].v;
        dist[i] = dist[i - 1] + abs(x - da[i - 1].x) * v;

        using std::begin;
        using std::end;
        auto l = disc[std::lower_bound(begin(disc), end(disc), da[i - 1].x) - begin(disc)];
        auto r = disc[std::lower_bound(begin(disc), end(disc), da[i    ].x) - begin(disc)];
        if (l > r)
            std::swap(l, r);

        while (sum(r) - sum(l - 1)) {
            auto p = bin_search(l, r);
            auto j = pos[p];
            // std::cerr << "::" << i << " " << trans_back(p) << "\n";
            dist[i] = std::min(dist[i], dist[j] + da[j].t + abs(x - da[j].x) * v);
            update(p, -1);
        }

        if (da[i - 1].t) {
            update(da[i - 1].x, 1);
            // std::cerr << "i = " << i << " update " << trans_back(da[i - 1].x) << "\n";
            pos[da[i - 1].x] = i - 1;
        }

        // std::cerr << trans_back(l) << " " << trans_back(r) << " " << dist[i] << "\n";

    }

    std::cout << dist.back() << "\n";
}

