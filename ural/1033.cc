// ml:run = $bin < input
#include <iostream>
#include <queue>

int const maxn = 100;
bool wall[maxn][maxn];
bool vis[maxn][maxn];
int n;

struct pos
{
    int x;
    int y;
};

int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

bool inrange(pos const& pos)
{
    return (0 < pos.x && pos.x <= n)
        && (0 < pos.y && pos.y <= n);
}

template <class Que>
auto bfs(Que& q)
{
    auto count = 0;
    while (!q.empty()) {
        auto now = q.front();
        q.pop();

        for (auto i = 0; i < 4; i++) {
            pos next{now.x + dir[i][0], now.y + dir[i][1]};
            if (wall[next.x][next.y]) {
                count++;
            } else {
                if (vis[next.x][next.y] || !inrange(next)) continue;
                q.push(next);
                vis[next.x][next.y] = true;
            }
        }
    }
    return count;
}

int main()
{
    std::cin >> n;
    for (auto i = 2; i <= n + 1; i++)
        wall[i][0]
            = wall[n + 1 - i][n + 1]
            = wall[0][i]
            = wall[n + 1][n + 1 - i]
            = true;

    for (auto i = 1; i <= n; i++)
        for (auto j = 1; j <= n; j++) {
            char ch; std::cin >> ch;
            wall[i][j] = ch == '#';
        }

    std::queue<pos> q;
    q.push({1, 1});
    vis[1][1] = true;
    auto count = bfs(q);
    if (!vis[n][n]) {
        vis[n][n] = true;
        q.push({n, n});
        count += bfs(q);
    }

    std::cout << count * 9 << "\n";
}

