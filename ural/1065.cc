// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <vector>
#include <cmath>

struct point { int x; int y; };

std::istream& operator>>(std::istream& is, point& p)
{
    is >> p.x >> p.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, point const& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

// also vector: p1 -> p2
struct segment { point p1; point p2; };

int operator*(segment const& lhs, segment const& rhs)
{
    auto x1 = lhs.p2.x - lhs.p1.x;
    auto y1 = lhs.p2.y - lhs.p1.y;
    auto x2 = rhs.p2.x - rhs.p1.x;
    auto y2 = rhs.p2.y - rhs.p1.y;
    return x1 * y2 - x2 * y1;
}


auto constexpr maxn = 2 * 51;
auto constexpr inf = 1e20;

double dp[maxn][maxn];
double dis[maxn][maxn];
bool clean_left[maxn][maxn];

std::vector<point> points;
std::vector<point> monuments;
int n, m;

bool left_side(point const& mon, segment const& seg)
{
    return segment{mon, seg.p1} * segment{mon, seg.p2} >= 0;
}

double distance(point const& p1, point const& p2)
{
    return std::hypot(p1.x - p2.x, p1.y - p2.y);
}

int main()
{
    std::cin >> n >> m;
    points.resize(2 * n);
    monuments.resize(m);
    for (auto i = 0; i < n; i++)
        std::cin >> points[i];
    for (auto i = 0; i < m; i++)
        std::cin >> monuments[i];
    std::copy_n(std::begin(points), n, std::begin(points) + n);

    for (auto i = 0; i < 2 * n; i++)
        for (auto j = i + 1; j < 2 * n; j++)
            dis[i][j] = dis[j][i] = distance(points[i], points[j]);

    for (auto i = 0; i < n; i++)
        for (auto j = 1; j < n; j++) {
            clean_left[i][i + j] = true;
            for (auto k = 0; k < m; k++) {
                if (left_side(monuments[k], {points[i], points[i + j]})) {
                    clean_left[i][i + j] = false;
                    break;
                }
            }
        }

    auto ans = inf;
    std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), inf);
    for (auto start = 0; start < n; start++) {
        dp[start][start] = 0;
        for (auto i = start + 1; i < start + n; i++) {
            for (auto j = i - 1; j >= start; j--) {
                if (clean_left[j][i])
                    dp[start][i] = std::min(dp[start][i], dp[start][j] + dis[j][i]);
            }
        }
    }

    for (auto i = 0; i < n; i++)
        for (auto j = i + 1; j < n; j++)
            for (auto k = j + 1; k < n; k++) {
                auto l1 = segment{points[i], points[j]};
                auto l2 = segment{points[i], points[k]};
                if (l1 * l2 == 0) continue;
                ans = std::min(ans, dp[i][j] + dp[j][k] + dp[k][i + n]);
            }

    std::cout << std::fixed << std::setprecision(2) << ans << "\n";
}

