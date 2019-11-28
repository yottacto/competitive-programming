// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
// is a prime number
auto constexpr mo = 998244353ll;
std::vector<ll> a;
std::vector<ll> fact;
std::vector<ll> fact_inv;
ll n, k;
ll count_diff;

ll sub(ll a, ll b)
{
    auto res = (a - b) % mo;
    if (res < 0)
        res += mo;
    return res;
}

template <class T>
ll add(T a, T b)
{
    return (a + b) % mo;
}

template <class T, class... Args>
ll add(T a, Args... args)
{
    return add(a, add(args...));
}

template <class T>
ll mul(T a, T b)
{
    return (a * b) % mo;
}

template <class T, class... Args>
ll mul(T a, Args... args)
{
    return mul(a, mul(args...));
}

ll quick_pow(ll a, ll b)
{
    if (!b)
        return 1;
    auto res = quick_pow(a, b / 2);
    res = mul(res, res);
    if (b & 1)
        res = mul(res, a);
    return res;
}

// Fermat's little theorem
ll inv(ll x)
{
    return quick_pow(x, mo - 2);
}

ll choose(ll n, ll m)
{
    return mul(fact[n], fact_inv[m], fact_inv[n - m]);
}

ll calc(ll n)
{
    if (n & 1) {
        return quick_pow(2, n - 1);
    } else {
        return mul(sub(quick_pow(2, n), choose(n, n / 2)), inv(2));
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n >> k;

    fact.resize(n + 1);
    fact_inv.resize(n + 1);
    fact[0] = 1;
    fact_inv[0] = 1;
    for (auto i = 1; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mo;
        fact_inv[i] = inv(fact[i]);
    }

    a.resize(n);
    for (auto i = 0; i < n; i++)
        std::cin >> a[i];
    for (auto i = 0; i < n; i++)
        if (a[i] != a[(i + 1) % n])
            count_diff++;

    auto ans = 0ll;
    for (auto i = 0; i <= count_diff; i++)
        ans = add(
            ans,
            mul(
                quick_pow(k - 2, i),
                choose(count_diff, i),
                calc(count_diff - i)
            )
        );
    ans = mul(ans, quick_pow(k, n - count_diff));
    std::cout << ans << "\n";
}

