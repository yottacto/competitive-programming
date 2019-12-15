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
}

