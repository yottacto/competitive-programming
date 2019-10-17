// ml:run = $bin < input
#include <iostream>
#include <algorithm>

using ll = long long;

auto constexpr mo = 998244353ll;
auto constexpr maxn = 1000007;
ll f[maxn][2][2];
int n;

int level(int x)
{
    auto l = 0;
    for (; x; x /= 2, l++)
        ;
    return l;
}

int lowbit(int x)
{
    return x & -x;
}

bool check(int l, int r)
{
    auto hl = level(l);
    auto hr = level(r);
    if (hl == hr)
        return true;
    if (hl < hr)
        std::swap(hl, hr);
    if (hl != hr + 1)
        return false;
    return lowbit(hr) == hr;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    f[1][1][1] = 1;
    f[1][1][0] = 0;
    f[1][0][0] = 0;
    f[1][0][0] = 1;
    f[0][0][0] = f[0][0][1] = f[0][1][0] = f[0][1][1] = 1;
    for (auto i = 2; i <= n; i++)
        for (auto j = 0; j < 2; j++) {
            for (auto k = 0; k < 2; k++) {
                for (auto l = 0; l <= n - 1; l++) {
                    auto r = n - 1 - l;
                    if (check(l, r)) {
                        std::cout << i << " " << j << " " << k << " " << l << "\n";
                        f[i][j][k] += (f[l][j ^ 1][k] * f[r][j][k ^ !(l&1)]) % mo;
                        f[i][j][k] %= mo;
                    }
                }
            }
        }
    std::cout << f[2][0][1] << "\n";
    auto ans = (f[n][0][1] + f[n][1][1]) % mo;
    std::cout << ans << "\n";
}

