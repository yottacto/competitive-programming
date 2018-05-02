// ml:run = $bin < input
#include <iostream>
#include <vector>

#define DEBUG 0

using ll = long long;

auto constexpr maxn = 12;
auto constexpr mo = 1'000'000'000ll;

char g[maxn][maxn];
int gid[maxn][maxn];
int n, m;
int tot;

std::vector<std::vector<int>> dir{
    {-1, 0}, {+1, 0},
    {0, -1}, {0, +1},
};

auto inrange(int x, int l, int r) { return (l <= x) && (x <= r); }
auto id(int x, int y) { return gid[x][y]; }
template <class T>
auto sub(T x, T y) { return (x - y) % mo; }
template <class T>
auto mul(T x, T y) { return (x * y) % mo; }

template <class Vec>
void print(Vec const& a)
{
    #if DEBUG
    int n = a.size();
    std::cerr << "n = " << n << "\n";
    for (auto const& v : a) {
        for (auto i : v)
            std::cout << i << " ";
        std::cout << "\n";
    }
    #endif
}

auto det(std::vector<std::vector<ll>>& a)
{
    print(a);

    for (auto& v : a)
        for (auto& i : v)
            i %= mo;

    int n = a.size();
    auto ret = 1ll;
    for (auto i = 0; i < n; i++) {
        for (auto j = i + 1; j < n; j++) {
            // like the process of gcd
            while (a[j][i]) {
                auto t = a[i][i] / a[j][i];
                for (auto k = i; k < n; k++)
                    a[i][k] = sub(a[i][k], mul(a[j][k], t));
                std::swap(a[i], a[j]);
                ret = -ret;
            }
        }
        if (!a[i][i])
            return 0ll;
        ret = mul(ret, a[i][i]);
    }
    if (ret < 0)
        ret += mo;
    return ret;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    for (auto i = 1; i <= n; i++)
        for (auto j = 1; j <= m; j++) {
            std::cin >> g[i][j];
            if (g[i][j] == '.') {
                gid[i][j] = tot++;
            }
        }
    if (!tot) {
        std::cout << "0\n";
        return 0;
    }
    std::vector<std::vector<ll>> a(tot - 1, std::vector<ll>(tot - 1));
    for (auto i = 1; i <= n; i++)
        for (auto j = 1; j <= m; j++) {
            auto u = id(i, j);
            if (g[i][j] == '*' || u == tot - 1)
                continue;
            auto degree = 0;
            for (auto d : dir) {
                auto x = i + d[0];
                auto y = j + d[1];
                if (!(inrange(x, 1, n) && inrange(y, 1, m)) || g[x][y] == '*')
                    continue;
                degree++;
                auto v = id(x, y);
                if (v != tot - 1)
                    a[u][v] = -1;
            }
            a[u][u] = degree;
        }

    std::cout << det(a) << "\n";
}

