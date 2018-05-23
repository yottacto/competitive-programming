// ml:run = $bin > output
#include <iostream>
#include <vector>
#include <cmath>

using ll = long long;

auto constexpr inf  = 1<<30;
auto constexpr maxn = 10000;
int k[maxn];
int sum[maxn];
ll n;

std::vector<int> v{
    2, 3, 6, 7, 8, 11, 12, 15, 18, 19, 22, 23, 24, 27, 28, 31, 32, 33, 43,
    44, 47, 48, 60, 67, 72, 76, 92, 96, 108, 112, 128,
};

ll calc(ll x)
{
    return x * (x + 1) * (2 * x + 1) / 6;
}

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
    n = 2000;
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

    for (auto i = 1; i <= n; i++) {
        // if (k[i] >= inf)
        //     std::cout << i << ", ";
        // std::cout << i << " = " << k[i] << " " << greater(i) << "\n";
        std::cout << i << " = " << k[i] << " " << greater(i) << " " << sum[i] << "\n";
    }
    std::cout << "\n";
}

