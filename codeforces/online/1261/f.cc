// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
using pair = std::pair<ll, ll>;
auto constexpr mo = 998244353ll;
auto constexpr inv2 = (mo + 1) / 2;

int na, nb;
std::vector<pair> a;
std::vector<pair> b;
std::vector<pair> level_a[60];
std::vector<pair> level_b[60];

ll lowbit(ll x)
{
    return x & -x;
}

template <class Vec>
void unique_vec(Vec& a)
{
    std::sort(a.begin(), a.end());
    a.erase(std::unique(a.begin(), a.end()), a.end());
}

template <class Vec>
void init(int& n, Vec& a)
{
    std::cin >> n;
    for (auto i = 0; i < n; i++) {
        ll l, r;
        std::cin >> l >> r;
        r++;
        while (l + lowbit(l) <= r) {
            a.emplace_back(l, l + lowbit(l) - 1);
            l += lowbit(l);
        }
        while (r - lowbit(r) >= l) {
            a.emplace_back(r - lowbit(r), r - 1);
            r -= lowbit(r);
        }
    }
    unique_vec(a);
}

auto length(pair const& p)
{
    return p.second - p.first + 1;
}

void walk_up(pair& cur, int i)
{
    auto up = ((1ll)<<(i + 1)) - 1;
    if ((cur.second & up) == up)
        cur.first -= ((1ll) << i);
    else
        cur.second += ((1ll) << i);
}

template <class Vec>
void walk(Vec& a, Vec (&level_a)[60])
{
    for (auto const& p : a) {
        auto cur = p;
        for (auto i = 0; i < 60; i++)
            if (length(cur) == ((1ll)<<i)) {
                level_a[i].emplace_back(cur);
                walk_up(cur, i);
            }
    }
    for (auto i = 0; i < 60; i++)
        unique_vec(level_a[i]);
}

template <class Vec>
void calc(Vec& a, Vec (&level_b)[60], int i, Vec& res)
{
    for (auto const& p1 : a) {
        if (length(p1) != ((1ll) << i))
            continue;
        for (auto const& p2 : level_b[i])
            res.emplace_back(
                p1.first ^ p2.first,
                (p1.first ^ p2.first) + ((1ll) << i) - 1
            );
    }
}

void update(ll& ans, ll l, ll r)
{
    auto tmp = (((l + r) % mo) * ((r - l + 1) % mo)) % mo;
    tmp = (tmp * inv2) % mo;
    ans = (ans + tmp) % mo;
}

ll calc()
{
    std::vector<pair> res;
    for (auto i = 0; i < 60; i++) {
        calc(a, level_b, i, res);
        calc(b, level_a, i, res);
    }
    unique_vec(res);
    ll ans{};
    auto l = res[0].first;
    auto r = res[0].second;
    for (auto const& p : res)
        if (p.first <= r) {
            r = std::max(r, p.second);
        } else {
            update(ans, l, r);
            l = p.first;
            r = p.second;
        }
    update(ans, l, r);
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    init(na, a);
    init(nb, b);
    walk(a, level_a);
    walk(b, level_b);
    std::cout << calc() << "\n";
}

