// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>

using ll = long long;

struct data
{
    int x;
    ll v;
    // 0 means not a cableway
    int t;
};

std::vector<data> da;
std::vector<int> disc;
std::vector<int> seg;
std::vector<ll> dist;
int n;

std::map<int, int> map;

auto constexpr delta = 1000001;

template <class T>
T abs(T x) { return x < 0 ? -x : x; }

void trans(int& x) { x += delta; }

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
            std::swap(da[i - 1], da[i]);

    std::sort(std::begin(disc), std::end(disc));
    auto last = std::unique(std::begin(disc), std::end(disc));
    disc.erase(last, std::end(disc));

    dist.resize(da.size());
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

        auto it = map.lower_bound(l);
        std::vector<int> to_erase;
        for (; it != std::end(map) && it->first <= r; ++it) {
            auto j = it->second;
            to_erase.emplace_back(it->first);
            dist[i] = std::min(dist[i], dist[j] + da[j].t + abs(x - da[j].x) * v);
        }

        for (auto i : to_erase)
            map.erase(i);

        if (da[i - 1].t) {
            map[da[i - 1].x] = i - 1;
        }
    }

    std::cout << dist.back() << "\n";
}

