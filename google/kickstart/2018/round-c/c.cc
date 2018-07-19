// ml:run = $bin < C-small-practice.in > c-std.out
#include <iostream>
#include <algorithm>

using ll = long long;

auto constexpr maxn = 1000007;
auto constexpr mo = 1000000007ll;

ll x[maxn];
ll y[maxn];
ll a[maxn];
ll n, k;

ll quick(ll a, ll p)
{
    auto ret = 1ll;
    for (; p; p /= 2) {
        if (p & 1) ret = (ret * a) % mo;
        a = (a * a) % mo;
    }
    return ret;
}

int main()
{
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        ll c, d, e1, e2, f;
        std::cin >> n >> k >> x[1] >> y[1] >> c >> d >> e1 >> e2 >> f;

        a[1] = (x[1] + y[1]) % f;
        for (auto i = 2; i <= n; i++) {
            x[i] = (c * x[i-1] + d*y[i-1] + e1) % f;
            y[i] = (d * x[i-1] + c*y[i-1] + e2) % f;
            a[i] = (x[i] + y[i]) % f;
        }

        ll ans{0};
        for (auto p = 1; p <= k; p++)
        for (auto i = 1; i <= n; i++) {
            ll sum{0};
            for (auto j = i; j <= n; j++) {
                sum += a[j] * quick(j - i + 1, p);
                sum %= mo;
                ans = (ans + sum) % mo;
            }
        }
        std::cout << ans << "\n";
    }
}

