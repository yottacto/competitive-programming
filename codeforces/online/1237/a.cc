// ml:run = $bin < input
#include <iostream>
#include <cmath>

int main()
{
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    auto last = true;
    for (auto i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        if (x & 1) {
            std::cout << (last ? int(std::ceil(x / 2.)) : int(std::floor(x / 2.))) << "\n";
            last ^= true;
        } else {
            std::cout << x / 2 << "\n";
        }
    }
}

