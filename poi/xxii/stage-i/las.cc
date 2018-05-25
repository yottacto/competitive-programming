// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <cstring>

auto constexpr maxn = 1000007;
long long c[maxn];
bool f[maxn][4];
int from[maxn][4];
int ans[maxn];
int n;

void dp(bool& f, int& from, bool v1, int p1, bool v2, int p2)
{
    f = v1 | v2;
    if (v1) from = p1;
    if (v2) from = p2;
}

int next(int i) { if (++i == n + 1) i = 1; return i; }
int prev(int i) { if (--i == 0) i = n; return i; }

void print(int p)
{
    for (auto i = n; i >= 1; p = from[i--][p])
        if (p == 1 || p == 3)
            ans[i] = i;
        else
            ans[i] = next(i);
    for (auto i = 1; i <= n; i++)
        std::cout << ans[i] << " ";
    std::cout << "\n";
    exit(0);
}

bool work()
{
    for (auto s = 0; s < 4; s++) {
        std::memset(f, 0, sizeof(f));
        f[1][s] = true;
        for (auto i = 2; i <= n; i++) {
            dp(f[i][0], from[i][0], (f[i - 1][1] && c[i-1] >= c[i]), 1, (f[i - 1][3] && c[i-1] >= c[i]*2), 3);
            dp(f[i][1], from[i][1], (f[i - 1][1] && c[i-1]*2 >= c[i]), 1, (f[i - 1][3] && c[i-1] >= c[i]), 3);
            dp(f[i][2], from[i][2], (f[i - 1][0] && c[i] >= c[i-1]), 0, (f[i - 1][2] && c[i]*2 >= c[i-1]), 2);
            dp(f[i][3], from[i][3], (f[i - 1][0] && c[i] >= c[i-1]*2), 0, (f[i - 1][2] && c[i] >= c[i-1]), 2);
        }

        if (f[n][0] && (f[1][2] | f[1][3]))
            if ((s == 2 && c[1] >= c[n]) | (s == 3 && c[1] >= c[n]*2))
                print(0);
        if (f[n][1] && (f[1][0] | f[1][1]))
            if ((s == 0 && c[n] >= c[1]) || (s == 1 && c[n]*2 >= c[1]))
                print(1);
        if (f[n][2] && (f[1][2] | f[1][3]))
            if ((s == 2 && c[1]*2 >= c[n]) || (s == 3 && c[1] >= c[n]))
                print(2);
        if (f[n][3] && (f[1][0] | f[1][1]))
            if ((s == 0 && c[n] >= c[1]*2) || (s == 1 && c[n] >= c[1]))
                print(3);
    }
    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto i = 1; i <= n; i++)
        std::cin >> c[i];

    if (!work())
        std::cout << "NIE\n";
}

