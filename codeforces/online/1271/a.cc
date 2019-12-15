// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr mo = 998244353ll;

ll add(ll x, ll y)
{
    auto res = (x + y) % mo;
    if (res < 0)
        res += mo;
    return res;
}

ll sub(ll x, ll y)
{
    auto res = (x - y) % mo;
    if (res < 0)
        res += mo;
    return res;
}

ll mul(ll x, ll y)
{
    auto res = (x * y) % mo;
    if (res < 0)
        res += mo;
    return res;
}


ll a, b, c, d;
ll e, f;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> a >> b >> c >> d;
    std::cin >> e >> f;

    // 1: a, d
    // 2: b, c, d
    auto max = 0ll;
    for (auto i = 0; i <= std::min(a, d); i++) {
        auto make = e * i;
        make += std::min(std::min(b, c), d - i) * f;
        max = std::max(max, make);
    }
    std::cout << max << "\n";
}

