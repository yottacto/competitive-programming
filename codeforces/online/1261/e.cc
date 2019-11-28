// ml:run = $bin < input
#include <bits/stdc++.h>

auto constexpr maxn = 1007;
int res[maxn][maxn];
int a[maxn];
int n;

int fill(int cur, int row)
{
    if (!cur)
        return 0;
    auto max = 0;
    auto count = 0;
    auto need = 0;
    for (auto i = 0; i < n; i++) {
        if (a[i] > max) {
            max = a[i];
            count = 1;
        } else if (a[i] == max) {
            count++;
        }
    }
    auto first = true;
    if (max == cur && count > 1) {
        need = max + 1;
        for (auto i = 0; i < n; i++) {
            if (a[i] != max)
                continue;
            if (first) {
                for (auto k = 0; k < max; k++)
                    res[row + k + 1][i] = 1;
                first = false;
                a[i] = 0;
            } else {
                res[row][i] = 1;
                a[i]--;
            }
        }
    } else {
        need = max;
        for (auto i = 0; i < n; i++) {
            if (a[i] != max)
                continue;
            if (first) {
                res[row][i] = 1;
                for (auto k = 0; k < a[i] - 1; k++)
                    res[row + k + 1][i] = 1;
                first = false;
                a[i] = 0;
            }
        }
    }
    auto next = fill(cur - 1, row + 1);
    return std::max(need, next + 1);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n;
    auto max = 0;
    auto count = 0;
    for (auto i = 0; i < n; i++) {
        std::cin >> a[i];
        if (a[i] > max) {
            max = a[i];
            count = 1;
        } else if (a[i] == max) {
            count++;
        }
    }

    auto tot = fill(max, 0);

    std::cout << tot << "\n";
    for (auto i = 0; i < tot; i++) {
        for (auto j = 0; j < n; j++)
            std::cout << res[i][j];
        std::cout << "\n";
    }
}

