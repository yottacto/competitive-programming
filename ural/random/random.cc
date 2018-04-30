// ml:run = cp $bin random
#include <iostream>
#include <algorithm>
#include <random>

int main()
{
    std::random_device rd;
    std::mt19937 gen{rd()};
    auto n = 4;

    std::uniform_int_distribution<> dis_char(1, 26);
    std::uniform_int_distribution<> dis(1, n);
    std::uniform_int_distribution<> dis_opt(1, 2);
    std::uniform_int_distribution<> dis_k(1, std::min(n, 50));

    auto k = dis_k(gen);
    std::string s(n, 'a');

    std::cout << s << " " << k << "\n";

    auto q = 4;
    std::cout << q << "\n";
    for (auto i = 0; i < q; i++) {
        auto opt = dis_opt(gen);
        auto l = dis(gen);
        auto r = dis(gen);
        if (l > r) std::swap(l, r);
        std::cout << opt << " " << l << " " << r;
        if (opt == 1) {
            char ch = dis_char(gen) + 'a' - 1;
            std::cout << " " << ch;
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

