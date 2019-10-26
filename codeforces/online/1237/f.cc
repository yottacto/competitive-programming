// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr mo = 998244353ll;
auto constexpr maxn = 4000;
bool rows[maxn];
bool cols[maxn];
ll f[maxn][maxn];
ll g[maxn][maxn];
ll choose[maxn][maxn];
ll frac[maxn];
ll h, w, remain_h, remain_w;
int n;

void init()
{
    choose[0][0] = 1;
    for (auto i = 1; i < maxn; i++) {
        choose[i][0] = 1;
        for (auto j = 1; j <= i; j++)
            choose[i][j] = (choose[i - 1][j] + choose[i - 1][j - 1]) % mo;
    }

    frac[0] = 1;
    for (auto i = 1; i < maxn; i++)
        frac[i] = (frac[i - 1] * i) % mo;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    init();
    std::cin >> h >> w >> n;
    rows[0] = cols[0] = true;
    for (auto i = 0; i < n; i++) {
        int r, c;
        std::cin >> r >> c;
        rows[r] = true;
        cols[c] = true;
        std::cin >> r >> c;
        rows[r] = true;
        cols[c] = true;
    }

    for (auto i = 1; i <= h; i++)
        if (!rows[i])
            remain_h++;

    for (auto i = 1; i <= w; i++)
        if (!cols[i])
            remain_w++;

    f[0][0] = 1;
    for (auto i = 1; i <= h; i++) {
        f[i][0] = 1;
        for (auto j = 1; 2 * j <= i; j++) {
            f[i][j] = f[i - 1][j];
            if (!rows[i] && !rows[i - 1]) {
                f[i][j] += f[i - 2][j - 1];
                f[i][j] %= mo;
            }
        }
    }

    g[0][0] = 1;
    for (auto i = 1; i <= w; i++) {
        g[i][0] = 1;
        for (auto j = 1; 2 * j <= i; j++) {
            g[i][j] = g[i - 1][j];
            if (!cols[i] && !cols[i - 1]) {
                g[i][j] += g[i - 2][j - 1];
                g[i][j] %= mo;
            }
        }
    }

    auto ans = 0ll;
    for (auto i = 0; i <= remain_w / 2; i++)
        for (auto j = 0; j <= remain_h / 2; j++) {
            auto ti = (f[h][j] * choose[remain_h - 2*j][i]) % mo;
            auto tj = (g[w][i] * choose[remain_w - 2*i][j]) % mo;
            auto tmp = (ti * tj) % mo;
            ans += (((frac[i] * frac[j]) % mo) * tmp) % mo;
            ans %= mo;
        }
    std::cout << ans << "\n";

}

