// ml:run = $bin < input
#include <iostream>

using ll = long long;

auto calc(ll p, ll n) -> ll
{
    if (p & 1)
        return (p + 1) / 2;
    auto shift_right = (n + 1) / 2;
    auto tn = n / 2;
    auto new_p = p / 2;
    auto old_p = new_p - shift_right;
    if (old_p <= 0)
        old_p += tn;
    auto tp = calc(old_p, tn);
    return tp + (n+1)/2;
}

int main()
{
    std::ios::sync_with_stdio(false);
    ll n, q;
    std::cin >> n >> q;
    while (q--) {
        ll p;
        std::cin >> p;
        std::cout << calc(p, n) << "\n";
    }
}

