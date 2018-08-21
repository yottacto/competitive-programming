// ml:run = $bin < input
// ml:std = c++11
#include <iostream>
#include <functional>
#include <unordered_map>
#include <array>
#include <cmath>

using ll = long long;

auto constexpr maxn = 1000007;
int bead[maxn];
int last_color[maxn];
int count_color[maxn];
int next[maxn];
bool vis[maxn];
int n, k;

template <ll... Primes>
struct hash_value
{
    hash_value()
    {
        static_assert(sizeof...(Primes) > 0, "hash_value need at least one prime");
    }

    ll quick_pow(ll a, ll b, ll mo)
    {
        ll res = 1;
        for (; b; b /= 2) {
            if (b & 1) res = (res * a) % mo;
            a = (a * a) % mo;
        }
        return res % mo;
    }

    void add(int k, ll delta)
    {
        for (auto i = 0u; i < n; i++) {
            auto mo = primes[i];
            auto d = delta % mo;
            if (d < 0) d += mo;
            a[i] += (d * quick_pow(base, k, mo)) % mo;
            a[i] %= mo;
        }
    }

    static constexpr auto n = sizeof...(Primes);
    static constexpr std::array<ll, sizeof...(Primes)> primes{Primes...};
    static constexpr ll base = 7;

    std::array<ll, sizeof...(Primes)> a{};
};

template <ll... Primes>
constexpr std::array<ll, sizeof...(Primes)> hash_value<Primes...>::primes;

// using hash_type = hash_value<10000873, 10001659>;
using hash_type = hash_value<1000000007ll, 1000000009ll, 10001659ll>;

template <ll... P1, ll... P2>
bool operator==(hash_value<P1...> const& lhs, hash_value<P2...> const& rhs)
{
    if (sizeof...(P1) != sizeof...(P2))
        return false;
    for (auto i = 0u; i < lhs.a.size(); i++)
        if (lhs.a[i] != rhs.a[i])
            return false;
    return true;
}

namespace std
{
    template <ll... Primes>
    struct hash<hash_value<Primes...>>
    {
        using argument_type = hash_value<Primes...>;
        using result_type = std::size_t;

        result_type operator()(argument_type const& hv) const noexcept
        {
            auto const& a = hv.a;
            result_type res{0};
            std::hash<ll> hasher;
            for (auto i : a)
                res ^= hasher(i) + 0x9e3779b9 + (res << 6) + (res >> 2);
            return res;
        }
    };
}

ll choose2(ll n)
{
    return n * (n - 1) / 2ll;
}

int main()
{
    std::ios::sync_with_stdio(false);

    std::cin >> n >> k;
    for (auto i = 1; i <= n; i++) {
        std::cin >> bead[i];
        last_color[bead[i]] = i;
        count_color[bead[i]]++;
    }

    hash_type hv;
    std::unordered_map<hash_type, int> count;
    std::unordered_map<hash_type, int> last;

    count[hv] = 1;
    last[hv] = 1;

    for (auto i = 1; i < n; i++) {
        if (last_color[bead[i]] != i)
            hv.add(bead[i], 1);
        else
            hv.add(bead[i], -(count_color[bead[i]] - 1));

        count[hv]++;
        if (last.count(hv))
            next[last.at(hv)] = i + 1;
        last[hv] = i + 1;
    }

    ll ans{0};
    for (auto const& p : count)
        ans += choose2(p.second);

    auto len = n;
    for (auto i = 1; i <= n; i++) {
        if (vis[i] || !next[i])
            continue;
        vis[i] = true;
        auto p1 = i;
        auto p2 = i;
        for (; next[p1]; p1 = next[p1]) {
            for (; next[p2] && next[p2] - p1 <= n/2; )
                vis[p2 = next[p2]] = true;
            len = std::min(len, std::abs(n - 2*(p2 - p1)));
            if (next[p2])
                len = std::min(len, std::abs(n - 2*(next[p2] - p1)));
        }
    }
    std::cout << ans << " " << len << "\n";
}

