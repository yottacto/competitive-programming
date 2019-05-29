// ml:run = $bin < input
// ml:std = c++14
#include <iostream>

auto constexpr maxn = 300007;
auto constexpr maxl = 20;
auto constexpr  inf = 1<<30;
int a[maxn];
int f[maxn][maxl];
int last[maxl];
int n, q;

bool work(int l, int r)
{
    for (auto i = 0; i < maxl; i++) {
        if (!(a[r] & (1<<i)))
            continue;
        if (f[l][i] <= r)
            return true;
    }
    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> q;
    for (auto i = 1; i <= n; i++)
        std::cin >> a[i];
    for (auto i = 0; i < maxl; i++)
        last[i] = inf;
    for (auto i = n; i >= 1; i--) {
        for (auto k = 0; k < maxl; k++)
            f[i][k] = inf;
        for (auto j = 0; j < maxl; j++) {
            if (!(a[i] & (1<<j)) || last[j] == inf)
                continue;
            if (a[i] & a[last[j]])
                f[i][j] = std::min(f[i][j], last[j]);
            for (auto k = 0; k < maxl; k++)
                f[i][k] = std::min(f[i][k], f[last[j]][k]);
        }
        for (auto j = 0; j < maxl; j++)
            if (a[i] & (1<<j))
                last[j] = i;
    }
    for (auto i = 0; i < q; i++) {
        int l, r;
        std::cin >> l >> r;
        if (work(l, r))
            std::cout << "Shi\n";
        else
            std::cout << "Fou\n";
    }
}

