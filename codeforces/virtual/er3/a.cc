// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

int n, m;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    std::vector<int> v(n);
    for (auto& i : v)
        std::cin >> i;
    std::sort(v.begin(), v.end(), std::greater<int>());
    auto sum = 0;
    for (auto i = 0; i < n; i++) {
        sum += v[i];
        if (sum >= m) {
            std::cout << i + 1 << "\n";
            return 0;
        }
    }
}

