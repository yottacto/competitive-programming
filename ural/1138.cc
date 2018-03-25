// ml:run = $bin < input
#include <iostream>

auto constexpr maxn = 10040;
int f[maxn];
int start, last;

int main()
{
    std::cin >> last >> start;
    f[start] = 1;
    auto ans = 1;
    for (auto i = start; i <= last; i++) {
        if (!f[i]) continue;
        for (auto k = 1; k <= 100; k++) {
            if ((i * k) % 100 != 0) continue;
            auto next = i * (100 + k) / 100;
            if (next > last) break;
            f[next] = std::max(f[next], f[i] + 1);
        }
        ans = std::max(ans, f[i]);
    }
    std::cout << ans << "\n";
}

