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


struct data
{
    ll x;
    ll y;
};

int n;
ll sx, sy;
std::vector<data> da;

std::vector<std::vector<int>> dir{
    {-1, 0},
    {+1, 0},
    {0, -1},
    {0, +1},
};

int check(std::vector<int> const& dir)
{
    auto count = 0;
    for (auto const& i : da) {
        if (dir[0] && i.x == dir[0])
            count++;
        if (dir[1] && i.y == dir[1])
            count++;
    }
    return count;
}

ll change(ll x, ll t)
{
    if (x == t)
        return 0;
    if (x > t)
        return 1;
    return -1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n >> sx >> sy;
    da.resize(n);
    for (auto i = 0; i < n; i++) {
        std::cin >> da[i].x >> da[i].y;
        da[i].x = change(da[i].x, sx);
        da[i].y = change(da[i].y, sy);
    }

    auto max = 0;
    ll res_x;
    ll res_y;
    for (auto const& d : dir) {
        auto nx = sx + d[0];
        auto ny = sy + d[1];
        auto tmp = check(d);
        if (tmp > max) {
            max = tmp;
            res_x = nx;
            res_y = ny;
        }
    }
    std::cout << max << "\n";
    std::cout << res_x << " " << res_y << "\n";
}

