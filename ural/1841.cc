// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>

using ll = long long;

// t=0 means not a cableway
struct data { int x; ll v; int t; };

std::vector<data> da;
std::vector<int> disc;
std::vector<int> seg;
std::vector<ll> dist;
int n;

std::unordered_map<int, int> pos;
std::set<int> set;

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
        auto l = da[i - 1].x;
        auto r = da[i].x;
        if (l > r)
            std::swap(l, r);

        auto it = set.lower_bound(l);
        std::vector<int> to_erase;
        for (; it != std::end(set) && *it <= r; ++it) {
            auto j = pos[*it];
            to_erase.emplace_back(*it);
            dist[i] = std::min(dist[i], dist[j] + da[j].t + abs(x - da[j].x) * v);
        }

        for (auto i : to_erase)
            set.erase(i);

        if (da[i - 1].t) {
            set.insert(da[i - 1].x);
            pos[da[i - 1].x] = i - 1;
        }
    }

    std::cout << dist.back() << "\n";
}

