// ml:run = $bin < input
#include <iostream>
#include <algorithm>

auto constexpr maxn = 222;
char map[2][maxn][maxn];
int n, m;

// side 0 front, 1 back
int count(int x, int y, int side)
{
    return (map[side][x][y] == '\\')
        + (map[side][x][y + 1] == '/')
        + (map[side][x + 1][y] == '/')
        + (map[side][x + 1][y + 1] == '\\');
}

int main()
{
    std::cin >> n >> m;
    for (auto f = 0; f < 2; f++)
        for (auto i = 1; i <= n; i++)
            for (auto j = 1; j <= m; j++)
                std::cin >> map[f][i][j];

    auto front = 0;
    auto back = 0;
    for (auto i = 0; i <= n + 1; i++)
        for (auto j = 0; j <= m + 1; j++) {
            auto tmp = count(i, j, 0) - count(i, j, 1);
            if (tmp > 0)
                front += tmp;
            else
                back -= tmp;
        }

    std::cerr << front << " " << back << "\n";
    std::cout << std::min(front, back) + abs(front - back) / 2 << "\n";
}

