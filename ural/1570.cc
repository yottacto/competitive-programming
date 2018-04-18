// ml:run = $bin < input
#include <iostream>
#include <utility>
#include <vector>
#include <cmath>

auto constexpr maxn = 102;
auto constexpr maxm = 22 * 1000;
auto constexpr  inf = 1 << 30;

struct order
{
    operator bool() const
    {
        return price < inf;
    }

    int price{inf};
    int count;
};

auto operator<(order const& lhs, order const& rhs)
{
    return lhs.price < rhs.price
        || (lhs.price == rhs.price && lhs.count > rhs.count);
}

auto operator+(order const& lhs, order const& rhs)
{
    return order{lhs.price + rhs.price, lhs.count + rhs.count};
}

order f[maxn][maxm];
int from[maxn][maxm];
int count[maxn][maxm];
int n, m;

struct dish
{
    std::string name;
    int price;
    int fill;
};

auto& operator>>(std::istream& is, dish& d)
{
    double fill;
    is >> d.name >> d.price >> fill;
    d.fill = std::round(fill * 1000);
    return is;
}

std::vector<dish> dishes;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    m *= 1000;
    dishes.resize(n);
    for (auto& d : dishes)
        std::cin >> d;

    f[0][0] = {0, 0};
    count[0][0] = 0;
    {
        auto p    = dishes[0].price;
        auto fill = dishes[0].fill;
        for (auto i = 1; (i - 1) * fill < m; i++)
            for (auto j = (i - 1) * fill + 1; j <= std::min(m, i * fill); j++) {
                f[0][j] = {i * p, 1};
                count[0][j] = i;
            }
    }

    for (auto i = 1; i < n; i++) {
        auto p    = dishes[i].price;
        auto fill = dishes[i].fill;
        for (auto k = 0; k <= m; k++) {
            if (f[i - 1][k]) {
                f[i][k] = f[i - 1][k];
                from[i][k] = k;
                count[i][k] = 0;
            }
            auto prev = std::max(0, k - fill);
            if (f[i][prev] && f[i][prev] + order{p, !count[i][prev]} < f[i][k]) {
                f[i][k] = f[i][prev] + order{p, !count[i][prev]};
                from[i][k] = from[i][prev];
                count[i][k] = count[i][prev] + 1;
            }
        }

        for (auto k = m; k >= 0; k--)
            if (f[i][k + 1] && f[i][k + 1] < f[i][k]) {
                f[i][k] = f[i][k + 1];
                from[i][k] = from[i][k + 1];
                count[i][k] = count[i][k + 1];
            }
    }

    std::vector<std::pair<std::string, int>> ans;
    auto last = m;
    for (auto i = n - 1; i >= 0; i--) {
        if (count[i][last])
            ans.emplace_back(dishes[i].name, count[i][last]);
        last = from[i][last];
    }

    std::cout << f[n - 1][m].price << "\n";
    for (auto const& p : ans)
        std::cout << p.first << " " << p.second << "\n";
}

