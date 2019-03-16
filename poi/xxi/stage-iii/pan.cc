// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

auto check(int k, int l, int r)
{
    return (l + k - 1) / k <= r / k;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int q;
    std::cin >> q;
    while (q--) {
        int minx, maxx, miny, maxy;
        std::cin >> minx >> maxx >> miny >> maxy;
        auto m = std::max(maxx, maxy);
        auto ans = 1;
        for (auto k = 2; k <= int(std::sqrt(m)); k++) {
            if (check(k, minx, maxx) && check(k, miny, maxy))
                ans = k;
        }

        for (auto l = 1; l <= int(std::sqrt(m)); l++) {
            std::vector<int> v{maxx/l, maxy/l};
            for (auto k : v)
                if (check(k, minx, maxx) && check(k, miny, maxy))
                    ans = std::max(ans, k);
        }
        std::cout << ans << "\n";
    }
}

