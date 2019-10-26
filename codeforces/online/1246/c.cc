// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr mo = 1000000007ll;
auto constexpr maxn = 2019;
bool a[maxn][maxn];
ll down[maxn][maxn];
ll right[maxn][maxn];
ll can_down[maxn][maxn];
ll can_right[maxn][maxn];
ll row_delta[maxn][maxn];
ll row_sum[maxn][maxn];
ll col_delta[maxn][maxn];
ll col_sum[maxn][maxn];
int n, m;

ll add(ll x, ll y)
{
    x += y;
    x %= mo;
    if (x < 0)
        x += mo;
    return x;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> m;
    for (auto i = 1; i <= n; i++)
        for (auto j = 1; j <= m; j++) {
            char ch;
            std::cin >> ch;
            a[i][j] = ch == '.';
        }

    for (auto i = 1; i <= n; i++) {
        auto sum_rock = 0;
        for (auto j = m; j >= 1; j--) {
            can_right[i][j] = m - j - sum_rock;
            if (!a[i][j])
                sum_rock++;
        }
    }

    for (auto j = 1; j <= m; j++) {
        auto sum_rock = 0;
        for (auto i = n; i >= 1; i--) {
            can_down[i][j] = n - i - sum_rock;
            if (!a[i][j])
                sum_rock++;
        }
    }

    col_delta[1][1] = 1;
    col_delta[1 + can_down[1][1] + 1][1] = -1 + mo;
    for (auto i = 1; i <= n; i++) {
        for (auto j = 1; j <= m; j++) {
            col_sum[i][j] = add(col_sum[i - 1][j], col_delta[i][j]);
            row_sum[i][j] = add(row_sum[i][j - 1], row_delta[i][j]);
            right[i][j] = row_sum[i][j];
            down[i][j] = col_sum[i][j];
            col_delta[i + 1][j] = add(col_delta[i + 1][j], right[i][j]);
            col_delta[i + can_down[i][j] + 1][j] = add(col_delta[i + can_down[i][j] + 1][j], -right[i][j]);

            row_delta[i][j + 1] = add(row_delta[i][j + 1], down[i][j]);
            row_delta[i][j + can_right[i][j] + 1] = add(row_delta[i][j + can_right[i][j] + 1], -down[i][j]);
        }
    }

    std::cout << add(right[n][m], down[n][m]) << "\n";
}

