// ml:run = cp $bin random
#include <iostream>
#include <algorithm>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen{rd()};
    auto n = 4;

    std::uniform_real_distribution<> dis(0, 259);
    std::uniform_real_distribution<> dis_w(0.01, 1);
    std::uniform_real_distribution<> dis_d(1, 1000);

    auto a = dis(gen);
    auto w = dis_w(gen);

    std::cout << a << " " << w << " " << n << "\n";

    for (auto i = 0; i < n; i++)
        std::cout << dis(gen) << " " << dis_d(gen) << " " << dis_w(gen) << "\n";
}

