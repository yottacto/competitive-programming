// ml:run = $bin < input
#include <bits/stdc++.h>


std::vector<std::vector<char>> a;
std::vector<std::vector<char>> b;
std::vector<std::vector<int>> sum;
std::vector<std::vector<int>> tsum;
int n, m;
int tot;

template <class T>
bool has_empty(int x1, int y1, int x2, int y2, T const& sum)
{
    return sum[x2 + 1][y2 + 1] - sum[x1][y2 + 1] - sum[x2 + 1][y1]
        + sum[x1][y1];
}

bool check(int mid)
{
    auto ttot = tot;
    b = a;
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < m; j++) {
            if (b[i][j] == '.')
                continue;
            if (i < mid || j < mid || n - i - 1 < mid || m - j - 1 < mid
                    || has_empty(i - mid, j - mid, i + mid, j + mid, sum)) {
                b[i][j] = '.';
                ttot--;
            }
        }

    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < m; j++) {
            tsum[i + 1][j + 1] = tsum[i][j + 1] + tsum[i + 1][j] - tsum[i][j];
            if (b[i][j] == 'X')
                tsum[i + 1][j + 1]++;
        }

    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < m; j++) {
            if (a[i][j] == '.')
                continue;
            if (!has_empty(
                    std::max(0, i - mid),
                    std::max(0, j - mid),
                    std::min(n - 1, i + mid),
                    std::min(m - 1, j + mid),
                    tsum
            ))
                return false;
        }

    return ttot;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n >> m;
    a.resize(n, std::vector<char>(m));
    sum.resize(n + 1, std::vector<int>(m + 1));
    tsum.resize(n + 1, std::vector<int>(m + 1));
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < m; j++) {
            std::cin >> a[i][j];
            if (a[i][j] == 'X')
                tot++;
            sum[i + 1][j + 1] = sum[i][j + 1] + sum[i + 1][j] - sum[i][j];
            if (a[i][j] == '.')
                sum[i + 1][j + 1]++;
        }

    auto l = 0;
    auto r = std::min(n, m) / 2 + 2;
    while (l + 1 < r) {
        auto mid = (l + r) / 2;
        if (check(mid))
            l = mid;
        else
            r = mid;
    }

    if (check(r))
        l = r;

    std::cout << l << "\n";
    check(l);
    for (auto i = 0; i < n; i++) {
        for (auto j = 0; j < m; j++)
            std::cout << b[i][j];
        std::cout << "\n";
    }

}

