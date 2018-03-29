// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <cmath>

struct pos
{
    double x;
    double y;
};

std::ostream& operator<<(std::ostream& os, pos const& p)
{
    os << p.x << ", " << p.y;
    return os;
}

std::istream& operator>>(std::istream& is, pos& p)
{
    is >> p.x >> p.y;
    return is;
}

pos operator-(pos const& lhs, pos const& rhs)
{
    return {lhs.x - rhs.x, lhs.y - rhs.y};
}

pos p0, p1, p2;
pos center;
double r;

double calc_center(pos const& p1, pos const& p2, pos const& p3)
{
    auto a11 = 2. * (p3.x - p2.x);
    auto a12 = 2. * (p3.y - p2.y);
    auto a21 = 2. * (p2.x - p1.x);
    auto a22 = 2. * (p2.y - p1.y);

    auto b1 = p3.x*p3.x - p2.x*p2.x + p3.y*p3.y - p2.y*p2.y;
    auto b2 = p2.x*p2.x - p1.x*p1.x + p2.y*p2.y - p1.y*p1.y;

    auto d = a11 * a22 - a12 * a21;
    auto d1 = b1 * a22 - a12 * b2;
    auto d2 = a11 * b2 - b1 * a21;

    center.x = d1 / d;
    center.y = d2 / d;

    return std::hypot(p1.x - center.x, p1.y - center.y);
}

auto const pi = std::acos(-1.);

double calc_angle(pos const& p)
{
    auto len = std::hypot(p.x, p.y);
    auto a = std::acos(p.x / len);
    if (p.y < 0) a = 2 * pi - a;
    return a;
}

bool inrange(double x, double l, double r)
{
    if (l > r) std::swap(l, r);
    return l <= x && x <= r;
}

double trans(double a) { return a * 180. / pi; }

template <class T>
T abs(T x) { return x < 0 ? -x : x; }

auto constexpr eps = 1e-6;

bool in_curve(pos const& p, pos const& p1, pos const& p2, pos const& mid)
{
    auto a1 = calc_angle(p1 - center);
    auto a2 = calc_angle(p2 - center);
    auto am = calc_angle(mid - center);
    auto ap = calc_angle(p - center);

    if (abs(ap - a1) <= eps || abs(ap - a2) <= eps) return true;
    return (inrange(ap, a1, a2)) == (inrange(am, a1, a2));
}

int main()
{
    std::cin >> p0 >> p2 >> p1;
    r = calc_center(p0, p1, p2);

    auto left = std::llround(std::min(p0.x, p2.x));
    if (in_curve({center.x - r, center.y}, p0, p2, p1))
        left = std::floor(center.x - r + eps);

    auto right = std::llround(std::max(p0.x, p2.x));
    if (in_curve({center.x + r, center.y}, p0, p2, p1))
        right = std::ceil(center.x + r - eps);

    auto up = std::llround(std::max(p0.y, p2.y));
    if (in_curve({center.x, center.y + r}, p0, p2, p1))
        up = std::ceil(center.y + r - eps);

    auto down = std::llround(std::min(p0.y, p2.y));
    if (in_curve({center.x, center.y - r}, p0, p2, p1))
        down = std::floor(center.y - r + eps);

    auto area = (up - down) * (right - left);
    std::cout << area << "\n";
}

