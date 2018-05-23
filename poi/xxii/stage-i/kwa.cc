// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <set>
#include <cmath>

using ll = long long;

auto constexpr inf  = 1<<30;
auto constexpr maxn = 600;
int k[maxn];
int sum[maxn];
ll n;

std::set<int> all{
    2, 3, 6, 7, 8, 11, 12, 15, 18, 19, 22, 23, 24, 27, 28, 31, 32, 33, 43,
    44, 47, 48, 60, 67, 72, 76, 92, 96, 108, 112, 128,
};

ll calc(ll x) { return x * (x + 1) * (2 * x + 1) / 6; }

ll greater(ll x)
{
    ll l = 1;
    ll r = 2 * std::cbrt(x);
    while (l + 1 < r) {
        auto mid = (l + r) / 2;
        if (calc(mid) < x)
            l = mid;
        else
            r = mid;
    }
    if (calc(l) >= x)
        return l;
    return r;
}

int main()
{
    n = 506;
    k[1] = 1;
    for (auto i = 2; i <= n; i++) {
        k[i] = inf;
        for (auto j = 1; j * j <= i; j++) {
            if (k[i - j * j] != inf && k[i - j * j] < j) {
                k[i] = j;
                break;
            }
        }
        if (k[i] != greater(i))
            sum[i] = 1;
        sum[i] += sum[i - 1];
    }

    std::cin >> n;
    if (all.count(n))
        std::cout << "- ";
    else {
        if (n <= 506) {
            if (k[n] >= inf)
                std::cout << "- ";
            else
                std::cout << k[n] << " ";
        } else {
            auto t = greater(n);
            if (all.count(calc(t) - n))
                t++;
            std::cout << t << " ";
        }
    }

    if (n <= 506) {
        std::cout << sum[n] << "\n";
        return 0;
    }

    auto ans = sum[506];
    auto t = greater(n);
    auto s = calc(t);
    ans += (t - 1 - 12 + 1) * 31ll;
    for (auto i = s - 128; i <= n; i++)
        ans += all.count(s - i);

    std::cout << ans << "\n";
}

