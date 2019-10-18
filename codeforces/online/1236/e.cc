// ml:run = $bin < input
#include <iostream>

using ll = long long;
ll n, m;

auto constexpr maxn = 300007;
auto constexpr base = 100007;
ll a[maxn];
ll l[maxn];
ll r[maxn];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> m;
    if (n == 1) {
        std::cout << "0\n";
        return 0;
    }
    for (auto i = 1; i <= m; i++)
        std::cin >> a[i];
    for (auto i = m; i >= 1; i--) {
        l[a[i] + i + base] = l[a[i] + i + 1 + base] + 1;
        r[a[i] - i + base] = r[a[i] - i - 1 + base] + 1;
    }
    ll ans{0};
    for (auto i = 1; i <= n; i++) {
        auto tr = std::min(n, i + m + 1 - r[i + base]);
        auto tl = std::max(1ll, i - m - 1 + l[i + base]);
        ans += (tr - tl + 1);
    }
    std::cout << ans << "\n";
}

