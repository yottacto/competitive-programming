// ml:run = time -p $bin < 4380/19.in > out
#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;

static auto constexpr maxn = 55;
static auto constexpr maxm = 5005;
int n, m;
ll f[maxm][maxn][maxn];
int k[maxm][maxn][maxn];
int from[maxm][maxn][maxn];
int a[maxn];

struct data
{
    int l, r, p;
};

std::istream& operator>>(std::istream& is, data& da)
{
    is >> da.l >> da.r >> da.p;
    return is;
}

std::vector<data> da;
std::vector<int> price;

int calc(int j, int l, int r, int p)
{
    return k[j][l][r] - k[j][l][p - 1] - k[j][p + 1][r];
}

void print(int j, int l, int r)
{
    if (l > r || !f[j][l][r])
        return;
    if (from[j][l][r] == -1)
        print(j + 1, l, r);
    auto p = from[j][l][r];
    a[p] = price[j];
    print(j, l, p - 1);
    print(j, p + 1, r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    da.resize(m);
    price.reserve(m);
    for (auto i = 0; i < m; i++) {
        std::cin >> da[i];
        price.emplace_back(da[i].p);
    }
    std::sort(price.begin(), price.end());
    price.erase(std::unique(price.begin(), price.end()), price.end());
    int tm = price.size();

    for (auto i = 0; i < m; i++) {
        auto id = std::lower_bound(price.begin(), price.end(), da[i].p) - price.begin();
        for (auto l = 1; l <= da[i].l; l++)
            for (auto r = da[i].r; r <= n; r++)
                k[id][l][r]++;
    }

    for (auto i = tm - 2; i >= 0; i--) {
        for (auto l = 1; l <= n; l++)
            for (auto r = l; r <= n; r++)
                k[i][l][r] += k[i + 1][l][r];
    }

    for (auto len = 1; len <= n; len++)
        for (auto l = 1; l + len - 1 <= n; l++) {
            auto r = l + len - 1;
            for (auto j = tm - 1; j >= 0; j--) {
                f[j][l][r] = f[j + 1][l][r];
                from[j][l][r] = -1;
                if (!k[j][l][r]) continue;
                for (auto p = l; p <= r; p++) {
                    auto tmp = f[j][l][p - 1] + f[j][p + 1][r]
                        + (ll)calc(j, l, r, p) * price[j];

                    if (f[j][l][r] < tmp) {
                        f[j][l][r] = tmp;
                        from[j][l][r] = p;
                    }
                }
            }
        }

    std::cout << f[0][1][n] << "\n";
    print(0, 1, n);
    for (auto i = 1; i <= n; i++) {
        if (!a[i])
            a[i] = price[tm - 1];
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

