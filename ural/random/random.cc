// ml:run = cp $bin random
#include <iostream>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen{rd()};

    int m = 3;
    int n = 3;
    std::cout << m << " " << n << "\n";
    for (auto i = 0; i < m; i++) {
        std::uniform_int_distribution<> dis(-2, 2);
        for (auto j = 0; j < n; j++)
            std::cout << dis(gen) << " ";
        std::cout << "\n";
    }

    std::uniform_int_distribution<> dis(1, 100);
    for (auto i = 0; i < m; i++)
        std::cout << dis(gen) << "\n";
}

