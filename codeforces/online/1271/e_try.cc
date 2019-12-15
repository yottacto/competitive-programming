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


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n = 11;
    std::vector<int> f(n + 1);
    f[n] = 1;
    for (auto i = n - 1; i >= 1; i--) {
        f[i] = 1;
        if (i & 1) {
            if (2 * i <= n)
                f[i] += f[2 * i];
        } else {
            f[i] += f[i + 1];
            if (2 * i <= n)
                f[i] += f[2 * i];
        }
    }
    std::set<int> all;
    for (auto i = 1; i <= n; i++) {
        std::cout << i << " " << f[i] << "\n";
        all.emplace(f[i]);
    }
    std::cout << "=====\n";
    std::cout << n << " " << all.size() << "\n";
}

