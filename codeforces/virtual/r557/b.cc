// ml:run = $bin < input
// ml:std = c++14
#include <iostream>
#include <algorithm>
#include <vector>

auto constexpr base0 = 37ll;
auto constexpr mo0 = 2'098'960ll;
auto constexpr base1 = 5051ll;
auto constexpr mo1 = 9'808'358ll;

using ll = long long;
int n, m;

std::vector<std::vector<ll>> points;
std::vector<ll> h;

ll hash(std::vector<ll> const& v, ll base = base0, ll mo = mo0)
{
    auto b = 1ll;
    auto res = 0ll;
    for (auto i : v) {
        res = (res + b * i) % mo;
        b = (b * base) % mo;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    points.resize(n);
    h.resize(n);
    for (auto i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        if (u > v)
            std::swap(u, v);
        points[u - 1].emplace_back(v - u);
        points[v - 1].emplace_back(n - (v - u));
    }
    for (auto& p : points)
        std::sort(p.begin(), p.end());

    // for (auto& p : points) {
    //     for (auto i : p)
    //         std::cout << i << " ";
    //     std::cout << "\n";
    // }

    for (auto i = 0; i < n; i++)
        h[i] = hash(points[i]);

    // for (auto i : h)
    //     std::cout << i << " ";
    // std::cout << "\n";

    auto h0 = hash(h, base1, mo1);
    auto top_base = 1ll;
    for (auto i = 0; i < n; i++)
        top_base = (top_base * base1) % mo1;
    // std::cout << "h0=" << h0 << "\n";
    // std::cout << "top_base=" << top_base << "\n";
    // std::cout << "mo1  =" << mo1 << "\n";
    auto h1 = h0;
    for (auto i = 1; i < n; i++) {
        h1 = (h1 * base1) % mo1;
        h1 = (h1 - ((h[n - i] * top_base) % mo1)) % mo1;
        h1 = (h1 + mo1) % mo1;
        h1 = (h1 + h[n - i]) % mo1;
        // std::cout << "h[" << i << "]=" << h1 << "\n";
        if (h1 == h0) {
            std::cout << "Yes\n";
            return 0;
        }
    }
    std::cout << "No\n";
}

