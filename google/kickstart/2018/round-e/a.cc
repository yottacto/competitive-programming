// ml:run = $bin < A-large.in > a-large-1.out
// ml:run = $bin < A-small-attempt1.in > aa-small-1.out
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

auto work() -> int
{
    auto today = 1;
    auto ans = 0;
    for (auto i = 1; i <= n; today++) {
        for (auto j = 0; j < k; j++) {
            for (; i <= n; i++)
                if (expire[i] >= today) {
                    ans++;
                    i++;
                    break;
                }
        }
    }
    return ans;
}

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
        std::cout << work() << "\n";
    }
}

