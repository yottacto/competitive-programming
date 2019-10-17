// ml:run = $bin < input
#include <iostream>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    for (auto i = 0; i < n; i++) {
        int a, b, c;
        auto ans = 0;
        std::cin >> a >> b >> c;
        auto t = std::min(b, c / 2);
        ans += 3 * t;
        b -= t;
        c -= 2 * t;
        t = std::min(a, b / 2);
        ans += 3 * t;
        std::cout << ans << "\n";
    }
}

