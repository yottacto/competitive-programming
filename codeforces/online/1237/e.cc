// ml:run = $bin < input
#include <iostream>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    auto x = 1;
    while (x <= n) {
        if (x == n || x + 1 == n) {
            std::cout << "1\n";
            return 0;
        }
        if (x & 1)
            x = 2 * x + 2;
        else
            x = 2 * x + 1;
    }
    std::cout << "0\n";
}

