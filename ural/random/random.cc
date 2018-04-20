// ml:run = cp $bin random
#include <iostream>
#include <algorithm>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen{rd()};

    auto n = 900;
    std::cout << n << "\n";

    auto m = 1000;
    std::uniform_int_distribution<> dis(1, m);
    for (auto x = 0; x < n; x++) {
        auto y = dis(gen);
        std::cout << x << " " << y << "\n";
    }
    std::cout << "\n";
}

