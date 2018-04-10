// ml:opt = 0
// ml:ccf += -g
// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <queue>

auto constexpr maxn = 101;
int dug[maxn][maxn];
int ids[maxn][maxn];
int n, m;

struct pos { int x; int y; };

auto operator<(pos const& lhs, pos const& rhs)
{
    return lhs.x > rhs.x || (lhs.x == rhs.x && lhs.y > rhs.y);
}

std::priority_queue<pos> available;

struct expiration_time
{
    pos p;
    int t;
};

auto operator<(expiration_time const& lhs, expiration_time const& rhs)
{
    return lhs.t > rhs.t;
}

std::priority_queue<expiration_time> expired;

void init()
{
    for (auto i = 1; i <= n; i++)
        for (auto j = 1; j <= m; j++)
            available.push(pos{i, j});
}

void clear(int cur)
{
    while (!expired.empty()) {
        auto top = expired.top();
        if (cur < top.t)
            break;
        expired.pop();
        auto x = top.p.x;
        auto y = top.p.y;
        if (top.t != dug[x][y])
            continue;
        available.push({x, y});
        // FIXME
        ids[x][y] = 0;
        dug[x][y] = 0;
    }
}

auto inrange(int x, int y)
{
    return 1 <= x && x <= n
        && 1 <= y && y <= m;
}

int main()
{
    std::cin >> n >> m;
    init();
    std::vector<pos> id_map(1);
    auto id = 1;
    auto ans = 0;
    for (int t; std::cin >> t; ) {
        clear(t);
        char ch;
        std::cin >> ch;
        if (ch == 'd') {
            if (available.empty()) {
                ans++;
                id_map.emplace_back(pos{0, 0});
                id++;
                continue;
            }

            auto top = available.top();
            available.pop();
            auto x = top.x;
            auto y = top.y;
            ids[x][y] = id++;
            id_map.emplace_back(pos{x, y});
            dug[x][y] = t + 1001;
            expired.push({{x, y}, dug[x][y]});
        } else {
            int tid;
            std::cin >> tid;
            auto x = id_map[tid].x;
            auto y = id_map[tid].y;
            if (x == 0 || ids[x][y] != tid)
                continue;

            dug[x][y] = t + 1001;
            expired.push({{x, y}, dug[x][y]});

            for (auto i = -1; i <= 1; i++)
            for (auto j = -1; j <= 1; j++) {
                auto tx = x + i;
                auto ty = y + j;
                if (!inrange(tx, ty) || (tx == x && ty == y))
                    continue;

                if (!ids[tx][ty]) continue;
                if (dug[tx][ty] < t + 101) {
                    dug[tx][ty] = t + 101;
                    expired.push({{tx, ty}, dug[tx][ty]});
                }
            }
        }
    }
    std::cout << ans << "\n";
}

