// ml:run = cp $bin random
#include <iostream>
#include <algorithm>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen{rd()};

    auto n = 1000000000;
    auto p = 100;
    std::cout << n << " " << p << "\n";

    std::uniform_int_distribution<> dis(1, n);
    auto q = 100000;
    std::cout << q << "\n";
    for (auto t = 1; t <= q; t++) {
        std::cout << t << " ";
        if (false) {
            std::cout << "save ";
            auto l = dis(gen);
            auto r = dis(gen);
            if (l > r)
                std::swap(l, r);
            std::cout << l << " " << r << "\n";
        } else {
            std::cout << "enforce ";
            auto p = dis(gen);
            std::uniform_int_distribution<> tdis(1, std::min(n - p + 1, p));
            auto d = tdis(gen);
            std::cout << p << " " << d << "\n";
        }
    }
}

