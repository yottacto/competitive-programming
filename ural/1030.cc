// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

struct point
{
    double latitude;
    double longitude;
};

auto const pi = std::acos(-1.);

double degrees_to_radians(std::stringstream& buf)
{
    int degree;
    int minute;
    int second;
    {
        char ch;
        buf >> degree >> ch >> minute >> ch >> second;
    }
    double d{degree + minute / 60. + second / 3600.};
    return d * pi / 180.;
}

std::istream& operator>>(std::istream& is, point& p)
{
    {
        std::string line;
        std::getline(is, line);
        std::stringstream buf{line};
        p.latitude = degrees_to_radians(buf);
        buf >> line >> line;
        if (line[0] == 'S')
            p.latitude = 2 * pi - p.latitude;
    }
    {
        std::string line;
        std::getline(is, line);
        std::stringstream buf{line};
        buf >> line;
        p.longitude = degrees_to_radians(buf);
        buf >> line >> line;
        if (line[0] == 'W')
            p.longitude = 2 * pi - p.longitude;
    }
    // std::cerr << "point: [lat: " << p.latitude << ", long: " << p.longitude << "]\n";
    return is;
}

template <class T>
T abs(T x) { return x < 0 ? -x : x; }

double great_circle_distance(point const& p1, point const& p2, double r = 6875. / 2. /* miles */)
{
    auto d_long = abs(p1.longitude - p2.longitude);
    auto central_angle = std::acos(
        std::sin(p1.latitude) * std::sin(p2.latitude) +
        std::cos(p1.latitude) * std::cos(p2.latitude) * std::cos(d_long)
    );
    return central_angle * r;
}

int main()
{
    std::string line;
    for (auto i = 0; i < 3; i++)
        std::getline(std::cin, line);

    point ship;
    std::cin >> ship;

    std::getline(std::cin, line);

    point iceberg;
    std::cin >> iceberg;

    auto dis = great_circle_distance(ship, iceberg);
    std::cout << "The distance to the iceberg: "
        << std::fixed << std::setprecision(2)
        << dis << " miles.\n";
    if (int(dis * 100 + 0.5) < 10000)
        std::cout << "DANGER!\n";
}

