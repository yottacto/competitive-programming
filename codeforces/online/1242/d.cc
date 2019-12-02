// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
using pair = std::pair<ll, ll>;

ll n, k;

auto get_interval(ll n)
{
    return (n - 1) / (k * k + 1);
}

auto get_subinterval(ll n) -> pair
{
    auto p = get_interval(n);
    auto tn = n - (k * k + 1) * p;
    auto t = (tn - 1) / k;
    auto kth = tn - t * k;
    return {t, kth};
}

ll get_non_self(ll p)
{
    if (!p)
        return (k + 1) * k / 2;
    auto prev = p / k;
    auto pnon_self = get_non_self(prev);
    auto t = p % k;
    auto sum = (k * prev + t) * (k * k + 1) + k * (k + 1) / 2 - t;
    auto offset = 0ll;
    auto [t_prev, kth] = get_subinterval(pnon_self);
    if (t_prev < t)
        offset = k;
    else if (t_prev == t)
        offset = k - (kth - 1);
    return sum + offset;
}

auto calc(ll n)
{
    auto p = get_interval(n);
    auto non_self = get_non_self(p);
    if (n == non_self) {
        auto prev = p / k;
        auto t = p % k;
        return (prev * k + t + 1) * (k + 1);
    } else {
        auto [t, kth] = get_subinterval(n);
        if (non_self < n) {
            kth--;
            if (!kth) {
                t--;
                kth = k;
            }
        }
        return p * k * k + t * k + p * k + t + kth;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n >> k;
        std::cout << calc(n) << "\n";
    }
}

