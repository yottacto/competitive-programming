// ml:run = time -p $bin < input
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cassert>

using ll = long long;

struct pos
{
    ll x;
    ll y;
};

auto operator-(pos const& lhs, pos const& rhs)
{
    return pos{lhs.x - rhs.x, lhs.y - rhs.y};
}

auto operator==(pos const& lhs, pos const& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

auto& operator>>(std::istream& is, pos& p)
{
    is >> p.x >> p.y;
    return is;
}

auto& operator<<(std::ostream& os, pos const& p)
{
    os << "("  << p.x << ", " << p.y << ")";
    return os;
}

auto mul(pos const& lhs, pos const& rhs)
{
    return lhs.x * rhs.y - rhs.x * lhs.y;
}

auto quadrant(pos const& lhs)
{
    if (lhs.x <= 0 && lhs.y <= 0)
        return 1;
    if (lhs.y <= 0)
        return 2;
    if (lhs.x >= 0)
        return 3;
    return 4;
}

auto operator<(pos const& lhs, pos const& rhs)
{
    return quadrant(lhs) < quadrant(rhs)
        || (quadrant(lhs) == quadrant(rhs) && mul(lhs, rhs) > 0);
}

std::vector<pos> points;
int n;

auto c2(ll x)
{
    return x * (x - 1) / 2;
}

auto constexpr maxn = 2010;
pos tp[2 * maxn];

auto calc() -> ll
{
    auto res = 0ll;
    for (auto const& p1 : points) {
        auto tot = 0;
        for (auto const& p : points) {
            if (p == p1) continue;
            tp[tot++] = p - p1;
        }
        std::sort(tp, tp + tot);
        std::copy(tp, tp + tot, tp + tot);

        auto tail = 1;
        for (auto i = 0; i < tot; i++) {
            auto const& p2 = tp[i];
            if (i == tail) tail++;
            while (mul(tp[tail], p2) < 0)
                tail++;
            ll tn = tail - i - 1;

            // std::cerr << p1 << " " << p2 << " " << tn << "\n";
            // std::cerr << "tail=" << tail << " i=" << i << " " << tp[tail] << "\n";

            res += c2(tn) * c2(n - tn - 2);
        }
    }
    return res / 2;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    points.resize(n);
    for (auto& p : points)
        std::cin >> p;

    std::cout << calc() << "\n";
}

