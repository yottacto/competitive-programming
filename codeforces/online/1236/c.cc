// ml:run = $bin < input
#include <iostream>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> ans(n);
    for (auto i = 0; i < n; i++) {
        auto x = 0;
        auto y = i;
        for (auto j = 0; j < n; j++) {
            ans[i].emplace_back(x * n + y + 1);
            x = (x + 1) % n;
        }
    }
    for (auto j = 0; j < n/2; j++)
        for (auto i = 0; i < n/2; i++)
            std::swap(ans[i][j], ans[n - i - 1][j]);
    for (auto i = 0; i < n; i++) {
        for (auto v : ans[i])
            std::cout << v << " ";
        std::cout << "\n";
    }
}

