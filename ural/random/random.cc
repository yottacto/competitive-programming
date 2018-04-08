// ml:run = cp $bin random
#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen{rd()};

    auto n = 10;
    std::cout << n << "\n";
    auto m = 2 * n + 1;
    std::uniform_int_distribution<> dis(0, 1);
    for (auto i = 0; i < m; i++) {
        for (auto j = 0; j < m; j++)
            std::cout << (dis(gen) ? '+' : '-');
        std::cout << "\n";
    }
}

