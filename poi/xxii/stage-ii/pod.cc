// luogu-judger-enable-o2
// ml:run = $bin < input
// ml:std = c++11
#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <array>
#include <cmath>

using ll = long long;

namespace detail
{

template <ll... X> struct list
{
    static constexpr std::array<ll, sizeof...(X)> value{X...};
};

template <ll A, class T>
struct push_front;

template <ll A, ll... X>
struct push_front<A, list<X...>>
{
    using type = list<A, X...>;
    static constexpr auto value = type::value;
};

template <ll... X>
struct select_even;

template <ll A>
struct select_even<A>
{
    using type = list<A>;
    static constexpr auto value = type::value;
};

template <ll A, ll B>
struct select_even<A, B>
{
    using type = list<A>;
    static constexpr auto value = type::value;
};

template <ll A, ll B, ll... X>
struct select_even<A, B, X...>
{
    using type = typename push_front<A, typename select_even<X...>::type>::type;
    static constexpr auto value = type::value;
};

template <ll... X>
struct select_odd;

template <ll A>
struct select_odd<A>
{
    using type = list<>;
    static constexpr auto value = type::value;
};

template <ll A, ll B>
struct select_odd<A, B>
{
    using type = list<B>;
    static constexpr auto value = type::value;
};

template <ll A, ll B, ll... X>
struct select_odd<A, B, X...>
{
    using type = typename select_even<B, X...>::type;
    static constexpr auto value = type::value;
};

} // namespace detail

using detail::select_odd;
using detail::select_even;

// template <ll... X>
// auto constexpr select_even_v = detail::select_even<X...>::value;

// template <ll... X>
// auto constexpr select_odd_v = detail::select_odd<X...>::value;


auto constexpr maxn = 1000007;
int bead[maxn];
int last_color[maxn];
int count_color[maxn];
std::size_t hash[maxn];
int id[maxn];
int n, k;

template <ll... X>
struct hash_value
{
    static_assert(sizeof...(X) > 0, "hash_value need at least one prime");
    static_assert(sizeof...(X) % 2 == 0, "(base, prime) tuples must have even length");

    explicit hash_value(int k)
    {
        for (auto i = 0; i < n; i++) {
            power[i].resize(k + 1);
            power[i][0] = 1;
            auto mo = primes[i];
            auto base = bases[i];
            for (auto j = 1; j <= k; j++)
                power[i][j] = (power[i][j - 1] * base) % mo;
        }
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
        for (auto i = 0; i < n; i++) {
            auto mo = primes[i];
            auto d = delta % mo;
            if (d < 0) d += mo;
            a[i] += (d * power[i][k]) % mo;
            a[i] %= mo;
        }
    }

    static constexpr auto n = sizeof...(X)/2;
    static constexpr std::array<ll, n> bases = select_even<X...>::value;
    static constexpr std::array<ll, n> primes = select_odd<X...>::value;

    std::array<ll, n> a{};
    std::vector<ll> power[n];
};

template <ll... X>
constexpr std::array<ll, hash_value<X...>::n> hash_value<X...>::bases;

template <ll... X>
constexpr std::array<ll, hash_value<X...>::n> hash_value<X...>::primes;

// using hash_type = hash_value<10000873, 10001659>;
using hash_type = hash_value<
    1791507258ll, 1000000007ll,
    143248393ll, 1000000007ll,
    1791507258ll, 1000000009ll,
    143248393ll, 1000000009ll
>;

template <ll... X1, ll... X2>
bool operator==(hash_value<X1...> const& lhs, hash_value<X2...> const& rhs)
{
    if (lhs.a.size() != rhs.a.size())
        return false;
    for (auto i = 0u; i < lhs.a.size(); i++)
        if (lhs.a[i] != rhs.a[i])
            return false;
    return true;
}

namespace std
{
    template <ll... X>
    struct hash<hash_value<X...>>
    {
        using argument_type = hash_value<X...>;
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

template <class T>
void print(T a[], int l, int r)
{
    for (auto i = l; i <= r; i++)
        std::cout << a[i] << " ";
    std::cout << "\n";
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

    hash_type hv(k);
    std::hash<hash_type> hasher;
    hash[1] = hasher(hv);

    for (auto i = 1; i < n; i++) {
        if (last_color[bead[i]] != i)
            hv.add(bead[i], 1);
        else
            hv.add(bead[i], -(count_color[bead[i]] - 1));

        hash[i + 1] = hasher(hv);
    }

    // print(hash, 1, n);

    std::iota(id + 1, id + n + 1, 1);
    std::stable_sort(id + 1, id + n + 1, [](int lhs, int rhs) {
        return hash[lhs] < hash[rhs];
    });

    // for (auto i = 1; i <= n; i++)
    //     std::cout << id[i] << " ";
    // std::cout << "\n";

    // for (auto i = 1; i <= n; i++)
    //     std::cout << hash[id[i]] << " ";
    // std::cout << "\n";

    ll ans{0};
    auto len = n;
    for (auto i = 1, j = 1; i <= n; i = j) {
        for (; j <= n && hash[id[i]] == hash[id[j]]; j++)
            ;
        ans += choose2(j - i);
        for (auto p1 = i, p2 = i; p1 < j; p1++) {
            for (; p2 < j - 1 && id[p2+1] - id[p1] <= n/2; p2++)
                ;
            len = std::min(len, std::abs(n - 2*(id[p2] - id[p1])));
            if (p2 < j - 1)
                len = std::min(len, std::abs(n - 2*(id[p2+1] - id[p1])));
        }
    }
    std::cout << ans << " " << len << "\n";
}

