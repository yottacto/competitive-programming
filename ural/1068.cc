// ml:run = $bin < input
#include <iostream>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(false);
    auto r  = 1;
    int l;
    std::cin >> l;
    if (r < l) std::swap(l, r);
    std::cout << (l + r) * (r - l + 1) / 2 << "\n";
}

