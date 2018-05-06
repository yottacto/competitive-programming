// ml:run = $bin < input
#include <iostream>

auto constexpr maxn = 202;

int f[maxn][1200];
bool vis[maxn][1200];
int mo, all, n, m;
int uncommon[11];

int dp(int all, int st)
{
    if (!all)
        return 1;
    if (vis[all][st])
        return f[all][st];
    vis[all][st] = true;
    auto sum = 0;
    for (auto i = 2; i <= all; i += 2) {
        for (auto j = 0; j < n; j++) {
            if (uncommon[j] & st)
                continue;
            sum += dp(all - i, st) * dp(i - 2, st | (1 << j));
            sum %= mo;
        }
    }
    return f[all][st] = sum;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> mo >> all >> n >> m;
    for (auto i = 0; i < m; i++) {
        int u, v;
        std::cin >> u >> v;
        uncommon[v - 1] |= 1 << (u - 1);
    }

    std::cout << dp(all, 0) << "\n";
}

