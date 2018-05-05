// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <vector>

auto constexpr maxn = 20;
auto constexpr maxl = 16;

struct data
{
    int x, y, l;
};

int food[maxn][4][4];
bool down[maxn][4][4];
int f[maxn][4][4][maxl * maxn];
data from[maxn][4][4][maxl * maxn];
int max[maxn][16][16][maxl];
int n, r, c;

std::vector<std::vector<int>> dir{
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
};

auto inrange(int x) { return 0 <= x && x < 4; }

template <class T>
T abs(T x) { return x < 0 ? -x : x; }

void dfs(int floor, int start, int x1, int y1, int l, int st, int tot)
{
    max[floor][start][x1 * 4 + y1][l] = std::max(tot, max[floor][start][x1 * 4 + y1][l]);
    if (l == maxl - 1)
        return;
    for (auto const& d : dir) {
        auto x = x1 + d[0];
        auto y = y1 + d[1];
        if (!(inrange(x) && inrange(y)))
            continue;
        if (st & (1 << (x * 4 + y)))
            continue;
        dfs(floor, start, x, y, l + 1, st | (1 << (x * 4 + y)), tot + food[floor][x][y]);
    }
}

auto dir_char(std::vector<int> const& dir)
{
    if (dir[0] == 0) {
        if (dir[1] == 1)
            return 'E';
        else
            return 'W';
    } else {
        if (dir[0] == 1)
            return 'S';
        else
            return 'N';
    }
}

std::string path;
int target;

auto dfs_path(int floor, int x1, int y1, int x2, int y2, int l, int st, int tot, std::string const& p)
{
    if (!l) {
        if (x1 == x2 && y1 == y2 && tot == target) {
            path = p;
            return true;
        }
        return false;
    }
    for (auto const& d : dir) {
        auto x = x1 + d[0];
        auto y = y1 + d[1];
        auto ch = dir_char(d);
        if (!(inrange(x) && inrange(y)))
            continue;
        if (st & (1 << (x * 4 + y)))
            continue;
        if (dfs_path(floor, x, y, x2, y2, l - 1, st | (1 << (x * 4 + y)), tot + food[floor][x][y], p + ch))
            return true;
    }
    return false;
}

auto find_path(int floor, int x1, int y1, int x2, int y2, int l) -> std::string
{
    target = max[floor][x1 * 4 + y1][x2 * 4 + y2][l];
    if (!dfs_path(floor, x1, y1, x2, y2, l, (1 << (x1 * 4 + y1)), food[floor][x1][y1], ""))
        return "X";
    return path;
}

void print(data last)
{
    std::string path;
    for (auto i = n - 1; i > 0; i--) {
        auto x = last.x;
        auto y = last.y;
        auto l = last.l;
        auto up = from[i][x][y][l];
        path = 'D' + find_path(i, up.x, up.y, x, y, l - up.l - 1) + path;
        last = up;
    }
    path = find_path(0, r, c, last.x, last.y, last.l) + path;
    std::cout << path << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto floor = 0; floor < n; floor++) {
        for (auto i = 0; i < 4; i++)
            for (auto j = 0; j < 4; j++)
                std::cin >> food[floor][i][j];
        for (auto i = 0; i < 4; i++)
            for (auto j = 0; j < 4; j++)
                std::cin >> down[floor][i][j];
    }
    std::cin >> r >> c;
    r--; c--;

    for (auto floor = 0; floor < n; floor++)
        for (auto i = 0; i < 16; i++) {
            auto x1 = i / 4;
            auto y1 = i % 4;
            dfs(floor, i, x1, y1, 0, 1<<i, food[floor][x1][y1]);
        }

    for (auto x = 0; x < 4; x++)
        for (auto y = 0; y < 4; y++)
            for (auto l = 0; l < maxl; l++)
                f[0][x][y][l] = std::max(f[0][x][y][l], max[0][r * 4 + c][x * 4 + y][l]);

    for (auto floor = 1; floor < n; floor++) {
        for (auto x1 = 0; x1 < 4; x1++)
        for (auto y1 = 0; y1 < 4; y1++) {
            auto t1 = x1 * 4 + y1;
            for (auto len = 1; len < n * maxl; len++) {
                for (auto x2 = 0; x2 < 4; x2++)
                for (auto y2 = 0; y2 < 4; y2++) {
                    if (!down[floor - 1][x2][y2])
                        continue;
                    auto t2 = x2 * 4 + y2;
                    for (auto l = 0; l < maxl && len - l >= 1; l++) {
                        auto tf = f[floor - 1][x2][y2][len - 1 - l];
                        if (!tf || !max[floor][t1][t2][l]) continue;
                        if (f[floor][x1][y1][len] < tf + max[floor][t1][t2][l]) {
                            f[floor][x1][y1][len] = tf + max[floor][t1][t2][l];
                            from[floor][x1][y1][len] = {x2, y2, len - 1 - l};
                        }
                    }
                }
            }
        }
    }

    auto ans = 0.;
    data last;
    auto len = 0;
    for (auto x = 0; x < 4; x++)
    for (auto y = 0; y < 4; y++)
        for (auto l = 0; l < n * maxl; l++)
            if (f[n - 1][x][y][l] && f[n - 1][x][y][l] / double(l + 1) > ans)  {
                ans = f[n - 1][x][y][l] / double(l + 1);
                last = {x, y, l};
                len = l;
            }

    std::cout << std::fixed << std::setprecision(4)
        << ans << "\n";
    if (ans <= 1e-8) {
        std::cout << "0\n";
        return 0;
    }
    std::cout << len << "\n";
    if (len > 0)
        print(last);
}

