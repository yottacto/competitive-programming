// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr inf = 10000000000ll;
int n, k;
std::vector<ll> a;

ll _pow(ll a, ll b)
{
    if (!b)
        return 1;
    auto tmp = _pow(a, b / 2);
    if (tmp > inf)
        return tmp;
    tmp = tmp * tmp;
    if (tmp > inf)
        return tmp;
    if (b & 1)
        tmp = tmp * a;
    return tmp;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> k;
    a.resize(n);
    auto count1 = 0ll;
    for (auto i = 0; i < n; i++) {
        std::cin >> a[i];
        if (a[i] == 1)
            count1++;
    }
    if (k >= 34) {
        std::cout << count1 * (count1 - 1) / 2 << "\n";
        return 0;
    }
    ll ans{};
    std::unordered_map<ll, ll> count;
    for (auto i = 0; i < n; i++) {
        auto target = 1ll;
        auto tmp = a[i];
        auto base = 1ll;
        for (auto i = 2; i * i <= tmp; i++) {
            if (tmp % i)
                continue;
            auto c = 0ll;
            for (; !(tmp % i); tmp /= i)
                c++;
            c %= k;
            base *= _pow(i, c);
            target *= _pow(i, (k - c) % k);
            if (target > inf)
                break;
        }
        if (tmp > 1) {
            base *= _pow(tmp, 1);
            target *= _pow(tmp, k - 1);
        }
        if (count.count(target))
            ans += count.at(target);
        if (base <= inf)
            count[base]++;
    }
    std::cout << ans << "\n";
}

