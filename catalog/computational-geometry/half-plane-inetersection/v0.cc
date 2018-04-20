// ural1062
// ml:run = $bin < input
// ml:ccf += -g -O0
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <deque>
#include <cmath>

auto constexpr eps = 1e-11;

struct point { double x; double y; };
using vec = point;

auto operator-(point const& p0, point const& p1) { return vec{p0.x - p1.x, p0.y - p1.y}; }
auto operator+(point const& p0, vec const& v) { return vec{p0.x + v.x, p0.y + v.y}; }
auto operator*(double t, vec const& p) { return vec{t * p.x, t * p.y}; }

vec normal(vec v)
{
    auto len = std::hypot(v.x, v.y);
    v.x /= len;
    v.y /= len;
    return v;
}

struct line
{
    line() = default;
    // TODO p std::move?
    line(point p, vec v) :
        p{std::move(p)},
        v{normal(v)},
        angle{std::atan2(v.y, v.x)}
    {
    }

    point p;
    // must be unit vector
    vec v;
    double angle;
};

auto& operator<<(std::ostream& os, line const& l)
{
    os << "point = (" << l.p.x << ", " << l.p.y << "), "
        << "vec = (" << l.v.x << ", " << l.v.y << ")";
    return os;
}

struct data { double u; double v; double w; };
std::vector<data> da;
int n;

template <class T>
T abs(T x) { return x < 0 ? -x : x; }
auto equal(double lhs, double rhs) { return abs(lhs - rhs) <= eps; }
auto less(double lhs, double rhs) { return lhs + eps < rhs; }
auto greater_equal(double lhs, double rhs) { return less(rhs, lhs) || equal(rhs, lhs); }

auto cross(vec const& lhs, vec const& rhs) { return lhs.x * rhs.y - rhs.x * lhs.y; }
auto onleft(point const& p, line const& l) { return less(cross(p - l.p, l.v), 0); }

auto lines_intersection(line const& lhs, line const& rhs) -> point
{
    auto u = lhs.p - rhs.p;
    auto t = cross(rhs.v, u) / cross(lhs.v, rhs.v);
    return lhs.p + t * lhs.v;
}

// half-plane intersection
auto hp_intersection(std::vector<line>& lines)
{
    std::sort(std::begin(lines), std::end(lines), [](line const& lhs, line const& rhs) {
        return less(lhs.angle, rhs.angle);
    });

    // h* means half-*
    std::deque<line> hlines;
    std::deque<point> hpoints;
    hlines.emplace_back(lines.front());

    for (auto it = std::next(std::begin(lines)); it != std::end(lines); ++it) {
        while (!hpoints.empty() && !onleft(hpoints.back(), *it)) {
            hlines.pop_back();
            hpoints.pop_back();
        }
        while (!hpoints.empty() && !onleft(hpoints.front(), *it)) {
            hlines.pop_front();
            hpoints.pop_front();
        }

        auto last_line = hlines.back();
        hlines.emplace_back(*it);
        hpoints.emplace_back();

        // it will be at least two lines
        if (equal(cross(it->v, last_line.v), 0)) {
            hlines.pop_back();
            hpoints.pop_back();
            if (onleft(it->p, last_line))
                hlines.back() = *it;
        }

        if (!hpoints.empty()) {
            auto last_line = std::prev(std::end(hlines));
            // hpoints.back() = lines_intersection(last_line[0], last_line[-1]);
            hpoints.back() = lines_intersection(*last_line, *std::prev(last_line));
        }
    }
    while (!hpoints.empty() && !onleft(hpoints.back(), hlines.front())) {
        hlines.pop_back();
        hpoints.pop_back();
    }
    if (!hpoints.empty()) {
        auto last_line = std::prev(std::end(hlines));
        hpoints.back() = lines_intersection(*last_line, *std::prev(last_line));
    }

    // std::cerr << hlines.size() << "\n";
    // for (auto const& l : hlines)
    //     std::cerr << l << "\n";

    return hlines.size() >= 3;
}

int main()
{
    std::cin >> n;
    da.resize(n);
    for (auto& i : da) {
        std::cin >> i.u >> i.v >> i.w;
        i.u = 1. / i.u;
        i.v = 1. / i.v;
        i.w = 1. / i.w;
    }

    for (auto i = 0; i < n; i++) {
        std::vector<line> lines;
        // x >= 0
        lines.emplace_back(point{0, 0}, vec{+0, -1});
        // y >= 0
        lines.emplace_back(point{0, 0}, vec{+1, +0});
        // x + y <= 1
        lines.emplace_back(point{0, 1}, vec{-1, +1});

        auto solvable = true;
        for (auto j = 0; j < n; j++) {
            if (i == j) continue;
            // Ui * x + Vi * y + Wi * (1 - x - y) <=
            // Uj * x + Vj * y + Wj * (1 - x - y)
            // a y >= b x + c
            auto a = da[j].v - da[i].v + da[i].w - da[j].w;
            auto b = da[i].u - da[j].u - da[i].w + da[j].w;
            auto c = da[i].w - da[j].w;

            // std::cerr << a << " " << b << " " << c << "\n";

            point p;
            if (equal(a, 0)) {
                if (equal(b, 0)) {
                    if (greater_equal(c, 0)) {
                        solvable = false;
                        break;
                    } else
                        continue;
                }
                p = {-c / b, 0};
            } else
                p = {0, c / a};
            lines.emplace_back(p, vec{a, b});
        }

        if (solvable && hp_intersection(lines))
            std::cout << "Yes\n";
        else
            std::cout << "No\n";
    }
}

