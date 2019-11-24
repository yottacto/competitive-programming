// ml:run = $bin < input
#include <bits/stdc++.h>

auto constexpr maxn = 200;
char a[maxn][maxn];
char res[maxn][maxn];
std::vector<char> all;
int r, c, k;
int tot;

void next(int& x, int& y, int& d)
{
    y += d;
    if (y == c + 1) {
        x++;
        y = c;
        d = -d;
    } else if (y == 0) {
        x++;
        y = 1;
        d = -d;
    }
}

void work()
{
    auto d = 1;
    auto x = 1;
    auto y = 1;
    auto avg = tot / k;
    auto remain = tot % k;
    for (auto i = 0; i < k - 1; i++) {
        auto target = avg;
        if (remain) {
            target++;
            remain--;
        }
        for (auto j = 0; j < target; j++) {
            while (a[x][y] != 'R') {
                res[x][y] = all[i];
                next(x, y, d);
            }
            res[x][y] = all[i];
            next(x, y, d);
        }
    }

    for (auto i = 1; i <= r; i++) {
        for (auto j = 1; j <= c; j++)
            std::cout << res[i][j];
        std::cout << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    for (auto i = '0'; i <= '9'; i++)
        all.emplace_back(i);
    for (auto i = 'a'; i <= 'z'; i++)
        all.emplace_back(i);
    for (auto i = 'A'; i <= 'Z'; i++)
        all.emplace_back(i);

    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> r >> c >> k;
        tot = 0;
        for (auto i = 1; i <= r; i++)
            for (auto j = 1; j <= c; j++) {
                std::cin >> a[i][j];
                if (a[i][j] == 'R')
                    tot++;
                res[i][j] = all[k - 1];
            }
        work();
    }

}

