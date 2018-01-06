// ml:run = $bin < input
#include <iostream>
#include <cmath>

double const eps = 1e-6;

int main()
{
    std::ios::sync_with_stdio(false);
    double p, q;
    std::cin >> p >> q;
    for (int i = 1; ; i++) {
        auto low = std::ceil(i * p / 100. + eps);
        auto up = int(i * q / 100. - eps);
        if (low > 0 && low <= up) {
            std::cout << i << "\n";
            break;
        }
    }
}

