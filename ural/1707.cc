// ml:run = $bin < input
// binary indexed tree, counting star
#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>

struct point
{
    int x, y;
    bool count;
};

auto operator<(point const& lhs, point const& rhs)
{
    return lhs.x < rhs.x
        || (lhs.x == rhs.x && lhs.y < rhs.y)
        || (lhs.x == rhs.x && lhs.y == rhs.y && lhs.count > rhs.count);
}

auto operator==(point const& lhs, point const& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.count == rhs.count;
}

auto& operator<<(std::ostream& os, point const& p)
{
    os << p.x << ", " << p.y << "  " << p.count;
    return os;
}

auto constexpr maxn = 6000 * 2;
auto constexpr mo = 200'904'040'930ll + 33ll;
int tree[maxn];
int n, m;
std::vector<point> points;
std::vector<int> left_down_count;
std::vector<std::vector<int>> queries;

auto lowbit(int x) { return x & (-x); }

auto sum(int p)
{
    auto count = 0;
    for (; p > 0; p -= lowbit(p))
        count += tree[p];
    return count;
}

void update(int p)
{
    for (; p < maxn; p += lowbit(p))
        tree[p]++;
}

auto bin_search(point const& p)
{
    auto it = std::lower_bound(std::begin(points), std::end(points), p);
    return it - std::begin(points);
}

int main()
{
    std::cin >> n >> m;
    for (auto i = 0; i < m; i++) {
        int s0, t0, ds, dt, k;
        std::cin >> s0 >> t0 >> ds >> dt >> k;
        for (auto j = 0; j < k; j++) {
            auto x = (s0 + j * ds) % n;
            auto y = (t0 + j * dt) % n;
            points.emplace_back(point{
                (x + n) % n,
                (y + n) % n,
                true
            });
        }
    }

    int p;
    std::cin >> p;
    for (auto i = 0; i < p; i++) {
        int a0, b0, c0, d0, da, db, dc, dd, q;
        std::cin >> a0 >> b0 >> c0 >> d0 >> da >> db >> dc >> dd >> q;
        queries.emplace_back(std::vector<int>{
            a0, b0, c0, d0, da, db, dc, dd, q
        });
        for (auto j = 0; j < q; j++) {
            auto aj = (a0 + j * da) % n;
            auto bj = (b0 + j * db) % n;
            auto cj = (c0 + j * dc) % n;
            auto dj = (d0 + j * dd) % n;
            aj = (aj + n) % n;
            bj = (bj + n) % n;
            cj = (cj + n) % n;
            dj = (dj + n) % n;
            auto x1 = std::min(aj, bj);
            auto x2 = std::max(aj, bj);
            auto y1 = std::min(cj, dj);
            auto y2 = std::max(cj, dj);
            points.emplace_back(point{x2,     y2,     false});
            points.emplace_back(point{x1 - 1, y2,     false});
            points.emplace_back(point{x2,     y1 - 1, false});
            points.emplace_back(point{x1 - 1, y1 - 1, false});
        }
    }

    std::sort(std::begin(points), std::end(points));
    auto last = std::unique(std::begin(points), std::end(points));
    points.erase(last, std::end(points));

    // for (auto const& p : points)
    //     std::cout << p << "\n";

    auto tot = points.size();
    left_down_count.resize(tot);
    for (auto i = 0u; i < tot; i++) {
        auto y = points[i].y + 2;
        auto c = points[i].count;
        left_down_count[i] = sum(y);
        if (c)
            update(y);
    }

    for (auto const& v : queries) {
        int a0{v[0]}, b0{v[1]}, c0{v[2]}, d0{v[3]}, da{v[4]}, db{v[5]}, dc{v[6]}, dd{v[7]}, q{v[8]};
        std::string ans(q, '0');
        auto sum = 0ll;
        auto seven = 1ll;
        for (auto j = 0; j < q; j++) {
            auto aj = (a0 + j * da) % n;
            auto bj = (b0 + j * db) % n;
            auto cj = (c0 + j * dc) % n;
            auto dj = (d0 + j * dd) % n;
            aj = (aj + n) % n;
            bj = (bj + n) % n;
            cj = (cj + n) % n;
            dj = (dj + n) % n;
            auto x1 = std::min(aj, bj);
            auto x2 = std::max(aj, bj);
            auto y1 = std::min(cj, dj);
            auto y2 = std::max(cj, dj);
            auto p1 = bin_search(point{x2,     y2,     false});
            auto p2 = bin_search(point{x1 - 1, y2,     false});
            auto p3 = bin_search(point{x2,     y1 - 1, false});
            auto p4 = bin_search(point{x1 - 1, y1 - 1, false});
            auto count = left_down_count[p1]
                - left_down_count[p2]
                - left_down_count[p3]
                + left_down_count[p4];
            // std::cout << "::" << p1 << " " << p2 << " " << p3 << " " << p4 << "  = " << count << "\n";
            if (count) {
                ans[j] = '1';
                sum = (sum + seven) % mo;
            }
            seven = (seven * 7) % mo;
        }
        if (q > 20)
            std::cout << sum << "\n";
        else
            std::cout << ans << "\n";
    }
}

