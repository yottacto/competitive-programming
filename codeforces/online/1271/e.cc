// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr mo = 998244353ll;

ll add(ll x, ll y)
{
    auto res = (x + y) % mo;
    if (res < 0)
        res += mo;
    return res;
}

ll sub(ll x, ll y)
{
    auto res = (x - y) % mo;
    if (res < 0)
        res += mo;
    return res;
}

ll mul(ll x, ll y)
{
    auto res = (x * y) % mo;
    if (res < 0)
        res += mo;
    return res;
}

ll n, k;

std::unordered_map<ll, ll> f;
std::unordered_map<ll, ll> pos;
ll last_odd;
ll last_even;
ll y{1};

ll get(ll x)
{
    if (f.count(x))
        return f[x];
    if (x & 1)
        return last_odd;
    return last_even;
}

void update(ll tt, ll tmp)
{
    f[tt] = tmp;
    if (pos.count(tmp))
        pos[tmp] = std::max(tt, pos[tmp]);
    else
        pos[tmp] = tt;
    if (tmp >= k)
        y = std::max(y, tt);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> k;
    auto tn = n;
    for (; tn; ) {
        for (auto i = 0; i < 4; i++) {
            auto tt = tn - i;
            if (tt & 1) {
                auto tmp = 1 + get(2 * tt);
                update(tt, tmp);
            } else {
                auto tmp = 1 + get(2 * tt) + get(tt + 1);
                update(tt, tmp);
            }
        }
        if ((tn - 2) & 1) {
            last_odd = f[tn - 2];
            last_even = f[tn - 3];
        } else {
            last_odd = f[tn - 3];
            last_even = f[tn - 2];
        }
        tn /= 2;
    }
    std::cout << y << "\n";
}

