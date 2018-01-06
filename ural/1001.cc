// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <cmath>

using ll = long long;

void print()
{
    ll x;
    if (std::cin >> x) {
        print();
        std::cout << std::fixed << std::setprecision(4)
            << std::sqrt(x) << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    print();
}

