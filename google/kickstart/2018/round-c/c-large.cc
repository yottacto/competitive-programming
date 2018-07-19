// ml:run = $bin < C-large-practice.in > c.out
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

ll quick_seq(ll a, ll k)
{
    if (k == 1) return a % mo;
    auto ret = quick_seq(a, k/2);
    ret = ret + ((ret * quick(a, k/2)) % mo);
    ret %= mo;
    if (k & 1)
        ret = (ret + quick(a, k)) % mo;
    return ret;
}

ll col[maxn];
ll sum[maxn];

void init()
{
    sum[1] = col[1] = k % mo;
    for (auto i = 2; i <= n; i++) {
        col[i] = quick_seq(i, k);
        sum[i] = (sum[i - 1] + col[i]) % mo;
    }
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

        init();

        ll ans{0};
        for (ll i = 1; i <= n; i++) {
            ans += (a[i] * (((n - i + 1) * sum[i]) % mo)) % mo;
            ans %= mo;
        }
        std::cout << ans << "\n";
    }
}

