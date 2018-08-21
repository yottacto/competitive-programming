// ml:run = $bin < input
#include <iostream>
#include <vector>

int const maxn = 1000;
int a[maxn];
int n;
bool f[maxn][maxn][2];
bool vis[maxn][maxn][2];

int gcd(int a, int b)
{
    return !b ? a : gcd(b, a % b);
}

auto check(int l, int r, bool left)
{
    if (l > r) return true;
    if (vis[l][r][left]) return f[l][r][left];
    vis[l][r][left] = true;
    int root;
    if (left) root = a[r + 1];
    else root = a[l - 1];
    for (auto i = l; i <= r; i++) {
        if (gcd(root, a[i]) == 1) continue;
        if (check(l, i - 1, true) && check(i + 1, r, false))
            return f[l][r][left] = true;
    }
    return f[l][r][left] = false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto i = 1; i <= n; i++)
        std::cin >> a[i];

    for (auto i = 1; i <= n; i++) {
        if (check(1, i - 1, true) && check(i + 1, n, false)) {
            std::cout << "Yes\n";
            return 0;
        }
    }
    std::cout << "No\n";
}

