// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using ll = long long;
ll n, a, b, p, m;
std::string sm;

// [l, r)
struct range
{
    // range() = default;
    range(ll l, ll r) : l(l), r(r) {}

    ll l;
    ll r;
};

bool operator<(range const& lhs, range const& rhs)
{
    return (lhs.l < rhs.l)
        || (lhs.l == rhs.l && lhs.r < rhs.r);
}

range operator+(range const& lhs, range const& rhs)
{
    return range{std::min(lhs.l, rhs.l), std::max(lhs.r, rhs.r)};
}

std::vector<range> ranges;

ll mod(ll x, ll mo)
{
    return ((x % mo) + mo) % mo;
}

void add_range(ll l, ll r)
{
    if (l < r) {
        if (l > 0)
            ranges.emplace_back(0, l);
        ranges.emplace_back(r, n);
    } else {
        ranges.emplace_back(r, l);
    }
}

ll count_ranges()
{
    ranges.emplace_back(0, 0);
    ranges.emplace_back(n, n);
    std::sort(ranges.begin(), ranges.end());
    auto res = 0;
    auto len = ranges.size();
    for (auto i = 0u, j = 0u; i < len; i = j) {
        auto r = ranges[i].r;
        for (; j < len && ranges[j].l <= r; j++)
            r = std::max(r, ranges[j].r);
        if (j < len)
            res += ranges[j].l - r;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> a >> b >> p >> m;
    std::cin >> sm;
    auto sum = 0ll;
    for (auto i = 0; i < m; i++) {
        if (sm[i] == '0') {
            add_range(mod(0 - sum, n), mod(p - sum, n));
        } else {
            add_range(mod(p - sum, n), mod(n - sum, n));
        }
        (sum += a) %= n;
    }

    for (auto i = n - m + 1; i < n; i++)
        ranges.emplace_back(mod(i*a+b, n), mod(i*a+b, n) + 1);

    std::cout << count_ranges() << "\n";

    // for (auto const& r : ranges)
    //     std::cout << r.l << " " << r.r << "\n";
}

