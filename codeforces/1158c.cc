// ml:run = $bin < input
// ml:std = c++14
#include <iostream>
#include <vector>
#include <cmath>

auto constexpr maxn = 500007;
int f[20][maxn];
std::vector<int> a;
std::vector<int> res;
int n;

int query(int l, int r)
{
    int k = std::log(r - l + 1) / std::log(2);
    if (a[f[k][l]] >= a[f[k][r - (1<<k) + 1]])
        return f[k][l];
    else
        return f[k][r - (1<<k) + 1];
}

template <class Vec>
bool reconstruct(Vec const& a, int l, int r, int numl, int numr)
{
    // std::cerr << l << " " << r << " " << numl << " " << numr << "\n";
    if (l > r)
        return true;
    auto pos = query(l, r);
    // std::cerr << "pos: " << pos << "\n";
    if (a[pos] > r + 1)
        return false;
    if (a[pos] == -1) {
        for (auto i = l; i <= r; i++)
            res[i] = numl + i - l;
        return true;
    }
    if (a[pos] != r + 1)
        pos = r;
    res[pos] = numr;
    if (!reconstruct(a, l, pos - 1, numl, numl + pos - 1 - l))
        return false;
    if (!reconstruct(a, pos + 1, r, numl + pos - l, numr - 1))
        return false;
    return true;
}

void init()
{
    for (auto i = 1; i <= n; i++)
        f[0][i] = i;
    for (auto l = 1; l < 20; l++)
        for (auto i = 1; i + (1<<l) - 1 <= n; i++)
            if (a[f[l - 1][i]] >= a[f[l - 1][i + (1<<(l-1))]])
                f[l][i] = f[l - 1][i];
            else
                f[l][i] = f[l - 1][i + (1<<(l-1))];
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        a.resize(n + 1);
        res.resize(n + 1);
        for (auto i = 1; i <= n; i++)
            std::cin >> a[i];
        init();
        if (reconstruct(a, 1, n, 1, n)) {
            for (auto i = 1; i <= n; i++)
                std::cout << res[i] << " ";
            std::cout << "\n";
        } else {
            std::cout << "-1\n";
        }
    }
}

