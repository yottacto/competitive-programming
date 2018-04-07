// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <complex>
#include <vector>
#include <cmath>

auto const pi = std::acos(-1.);

using complex = std::complex<double>;

int n;
std::vector<complex> m;
std::vector<complex> r;

int main()
{
    std::cin >> n;

    for (auto i = 0; i < n; i++) {
        double real, imag;
        std::cin >> real >> imag;
        m.emplace_back(real, imag);
    }

    for (auto i = 0; i < n; i++) {
        double degree;
        std::cin >> degree;
        auto a = degree * pi / 180.;
        r.emplace_back(std::cos(a), std::sin(a));
    }

    // deduce pn = k * p1 + c
    complex k{1};
    complex c;
    for (auto i = 0; i < n; i++) {
        k *= r[i];
        c = r[i] * (c - m[i]) + m[i];
    }

    // solve p1 and reproduce all pn
    auto p = c / (complex{1} - k);
    for (auto i = 0; i < n; i++) {
        std::cout << std::fixed << std::setprecision(2)
            << p.real() << " " << p.imag() << "\n";
        p = (p - m[i]) * r[i] + m[i];
    }
}

