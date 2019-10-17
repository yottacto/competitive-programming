// ml:run = $bin < input
#include <iostream>

using ll = long long;
auto constexpr mo = 1000000007ll;
ll n, m;

ll quick(ll a, ll b)
{
    if (!b)
        return 1;
    auto res = quick(a, b/2);
    res = (res * res) % mo;
    if (b & 1)
        res = (res * a) % mo;
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> m;
    auto p = (quick(2, m) - 1) % mo;
    p = (p + mo) % mo;
    auto ans = quick(p, n);
    std::cout << ans << "\n";
}

