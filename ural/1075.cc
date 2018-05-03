// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <cmath>

struct pos { int x; int y; int z; };

template <class T>
double hypot(T a, T b, T c)
{
    return std::sqrt(a * a + b * b + c * c);
}

double dis(pos const& lhs, pos const& rhs)
{
    return hypot(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

std::istream& operator>>(std::istream& is, pos& p)
{
    is >> p.x >> p.y >> p.z;
    return is;
}

double r;

double heron(double a, double b, double c)
{
    auto s = (a + b + c) / 2.;
    return std::sqrt(s * (s - a) * (s - b) * (s - c));
}

double law_of_cosines(double a, double b, double c)
{
    return (a * a + b * b - c * c) / (2. * a * b);
}

template <class T>
T abs(T x) { return x < 0 ? -x : x; }

auto my_acos(double x)
{
    if (x > +1) x = +1;
    if (x < -1) x = -1;
    return std::acos(x);
}

double calc(pos const& a, pos const& b, pos const& c)
{
    auto len_ac = dis(a, c);
    auto len_bc = dis(b, c);
    auto len_ab = dis(a, b);
    auto area = heron(len_ac, len_bc, len_ab);
    auto dis = 2. * area / len_ab;

    if (dis >= r) return len_ab;

    double angle_a_is_acute = law_of_cosines(len_ac, len_ab, len_bc) >= 0;
    double angle_b_is_acute = law_of_cosines(len_bc, len_ab, len_ac) >= 0;
    if (!(angle_a_is_acute && angle_b_is_acute))
        return len_ab;

    double d1 = std::sqrt(len_ac * len_ac - r * r);
    double a1 = my_acos(r / len_ac);
    double d2 = std::sqrt(len_bc * len_bc - r * r);
    double a2 = my_acos(r / len_bc);

    double alpha = my_acos(law_of_cosines(len_ac, len_bc, len_ab));
    double a_mid = alpha - a1 - a2;

    // std::cerr << d1 << " " << d2 << " " << a_mid * r << "\n";
    // std::cerr << a1 << " " << a2 << " " << alpha << "\n";

    return d1 + d2 + a_mid * r;
}

int main()
{
    pos a;
    pos b;
    pos c;
    std::cin >> a >> b >> c >> r;

    std::cout
        << std::fixed << std::setprecision(2)
        << calc(a, b, c) << "\n";
}

