// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>

auto constexpr maxn = 1500;

int n, m;
int a[maxn][maxn];
int less_row[maxn][maxn];
int less_col[maxn][maxn];
int large_row[maxn][maxn];
int large_col[maxn][maxn];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < m; j++)
            std::cin >> a[i][j];

    for (auto i = 0; i < n; i++) {
        std::vector<int> v;
        v.reserve(m);
        for (auto j = 0; j < m; j++)
            v.emplace_back(a[i][j]);
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        for (auto j = 0; j < m; j++) {
            less_row[i][j] = std::lower_bound(v.begin(), v.end(), a[i][j]) - v.begin();
            large_row[i][j] = v.size() - 1 - less_row[i][j];
        }
    }

    for (auto j = 0; j < m; j++) {
        std::vector<int> v;
        v.reserve(n);
        for (auto i = 0; i < n; i++)
            v.emplace_back(a[i][j]);
        std::sort(v.begin(), v.end());
        v.erase(std::unique(v.begin(), v.end()), v.end());
        for (auto i = 0; i < n; i++) {
            less_col[i][j] = std::lower_bound(v.begin(), v.end(), a[i][j]) - v.begin();
            large_col[i][j] = v.size() - 1 - less_col[i][j];
        }
    }

    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < m; j++) {
            auto max = std::max(less_row[i][j], less_col[i][j]);
            auto res = max + std::max(large_row[i][j], large_col[i][j]);
            std::cout << res + 1 << " ";
        }
        std::cout << "\n";
    }
}

