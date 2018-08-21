// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

struct pos
{
    pos() = default;
    pos(int x, int y): x{x}, y{y} {}

    int x;
    int y;
};

auto const maxn = 60;
int now[maxn][maxn];
int target[maxn][maxn];
int n, m;
pos cubes[maxn];
std::vector<pos> ans;

void move_up(int row, int col, int step)
{
    if (!step) return;
    auto dir = step > 0 ? -1 : +1;
    step = std::abs(step);
    while (step--) {
        cubes[now[row][col]].x += dir;
        assert(!now[row + dir][col]);
        now[row + dir][col] = now[row][col];
        now[row][col] = 0;
        ans.emplace_back(row, col);
        ans.emplace_back(row + dir, col);
        row += dir;
    }
}

void move_left(int row, int col, int step)
{
    if (!step) return;
    auto dir = step > 0 ? -1 : +1;
    step = std::abs(step);
    while (step--) {
        cubes[now[row][col]].y += dir;
        assert(!now[row][col + dir]);
        now[row][col + dir] = now[row][col];
        now[row][col] = 0;
        ans.emplace_back(row, col);
        ans.emplace_back(row, col + dir);
        col += dir;
    }
}

void move_left_space(int row, int col, int step)
{
    if (!step) return;
    auto dir = step > 0 ? -1 : +1;
    step = std::abs(step);
    while (step--) {
        move_left(row, col + dir, dir);
        col += dir;
    }
}

void move_top()
{
    for (auto col = 1; col <= n; col++) {
        auto above = 0;
        for (auto row = 1; row <= n; row++) {
            if (!now[row][col]) continue;
            move_up(row, col, row - above - 1);
            above++;
        }
    }
}

auto find_space_on_topline(int col)
{
    for (auto i = col; i >= 1; i--)
        if (!now[1][i])
            return i;
    for (auto i = col + 1; i <= n; i++)
        if (!now[1][i])
            return i;
     assert(false);
}

void leave_space_on_topline(int col)
{
    auto p = find_space_on_topline(col);
    move_left_space(1, p, p - col);
}

void spread_on_topline()
{
    for (auto col = 1; col <= n; col++)
        for (auto row = 2; row <= n; row++) {
            if (!now[row][col]) continue;
            leave_space_on_topline(col);
            move_up(row, col, row - 1);
        }
}

void sort_down()
{
    auto full = false;
    for (auto col = 1; col <= n; col++) {
        auto down = 0;
        for (auto row = n; row >= 1; row--) {
            if (!target[row][col]) continue;
            auto id = target[row][col];
            auto prow = cubes[id].x;
            auto pcol = cubes[id].y;
            assert(prow == 1);
            if (full) {
                move_left(prow, pcol, pcol - col);
                move_up(prow, col, (prow - (n - down)));
            } else {
                move_up(prow, pcol, -1);
                move_left(prow + 1, pcol, pcol - col);
                move_up(prow + 1, col, (prow + 1 - (n - down)));
            }
            down++;
            if (down == n - 1)
                full = true;
        }
    }
}

void move_up_to_target()
{
    for (auto col = 1; col <= n; col++)
        for (auto row = 1; row <= n; row++) {
            if (!target[row][col]) continue;
            auto id = target[row][col];
            auto prow = cubes[id].x;
            auto pcol = cubes[id].y;
            assert(pcol == col);
            move_up(prow, pcol, prow - row);
        }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    if (n == 1) {
        std::cout << "0\n";
        return 0;
    }

    for (auto i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        now[x][y] = i + 1;
        cubes[i + 1] = {x, y};
    }

    for (auto i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        target[x][y] = i + 1;
    }

    move_top();
    spread_on_topline();
    sort_down();
    move_up_to_target();

    std::cout << ans.size() / 2 << "\n";
    for (auto i = 0u; i < ans.size(); i += 2)
        std::cout << ans[i].x << " " << ans[i].y << " "
            << ans[i + 1].x << " " << ans[i + 1].y << "\n";
}

