// ml:run = $bin < input
//
// f[i] = min( max(a[i], f[j] + i - j - 1) + 2 * s + i - j - 1)
//
// a[i] - i > f[j] - j - 1,
//      => a[i] + 2 * s + i - j - 1
// a[i] - i <= f[j] - j - 1,
//      => f[j] - 2 * j + 2 * (s + i - 1)
#include <iostream>
#include <limits>
#include <algorithm>

using ll = long long;

auto constexpr maxn = 1'000'007;
auto constexpr inf = std::numeric_limits<ll>::max();

ll a[maxn];
ll f[maxn];
int n, s;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> s;
    for (auto i = 1; i <= n; i++) {
        std::cin >> a[i];
        a[i] = std::max(a[i], a[i - 1] + 1);
        f[i] = inf;
    }
    auto j = 1;
    f[0] = 0;
    for (auto i = 1; i <= n; i++) {
        while (j < i && f[j] - j - 1 < a[i] - i)
            j++;
        f[i] = std::min(f[i], a[i] + 2 * s + i - (j - 1) - 1);
        if (f[j] != inf && f[j] + i - j - 1 >= a[i])
            f[i] = std::min(f[i], f[j] - 2 * j + 2 * (s + i - 1));
    }
    std::cout << f[n] << "\n";
}

