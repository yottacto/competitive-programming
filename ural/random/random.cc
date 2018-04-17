// ml:run = cp $bin random
#include <iostream>
#include <algorithm>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen{rd()};

    auto n = 9;
    std::cout << n << "\n";

    std::vector<int> a(n);
    std::iota(std::begin(a), std::end(a), 1);
    std::uniform_int_distribution<> dis(1, n);
    auto q = dis(gen);
    for (auto t = 1; t <= q; t++) {
        auto l = dis(gen);
        auto r = dis(gen);
        std::swap(a[l - 1], a[r - 1]);
    }
    for (auto i : a)
        std::cout << i << " ";
    std::cout << "\n";
}

