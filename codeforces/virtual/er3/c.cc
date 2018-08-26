// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

int n;
std::vector<int> a;

auto avg(int x)
{
    auto above = 0;
    auto below = 0;
    for (auto i : a) {
        if (i > x)
            above += i - x;
        else if (i < x)
            below += x - i;
    }
    return above + below - std::min(above, below);
}

auto calc(int x)
{
    auto above = 0;
    auto below = 0;
    for (auto i : a) {
        if (i > x + 1)
            above += i - (x+1);
        else if (i < x)
            below += x - i;
    }
    return above + below - std::min(above, below);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    a.resize(n);
    auto sum = 0;
    for (auto& i : a) {
        std::cin >> i;
        sum += i;
    }
    if (sum % n) {
        std::cout << calc(sum / n) << "\n";
    } else {
        std::cout << avg(sum / n) << "\n";
    }
}

