// ml:run = $bin < input
#include <iostream>

using ll = long long;
ll n, k;

auto find_left()
{
    return std::max(1ll, k - n);
}

auto calc(ll l, ll r)
{
    if (l >= n)
        return 0ll;
    return ((l + r - 1) / 2) - l + 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> k;
    auto l = find_left();
    auto r = k - l;
    std::cout << calc(l, r) << "\n";
}

