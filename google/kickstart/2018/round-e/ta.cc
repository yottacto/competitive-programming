// ml:run = $bin < input
#include <iostream>
#include <queue>
#include <iterator>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

auto constexpr maxn = 6000;
int expire[maxn];
int n, k;

int main()
{
    std::ios::sync_with_stdio(false);
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n >> k;
        for (auto i = 1; i <= n; i++)
            std::cin >> expire[i];
        std::sort(expire + 1, expire + n + 1);
        auto today = 1;
        auto ans = 0;
        for (auto i = 1; i <= n; today++) {
            auto j = 0;
            for (; j < k && i + j <= n; j++) {
                if (expire[i + j] >= today)
                    ans++;
            }
            i += j;
        }
        std::cout << ans << "\n";
    }
}

