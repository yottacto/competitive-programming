// ml:std = c++11
// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using pos_type = std::pair<int, int>;

auto constexpr maxn = 1007;
bool vis[maxn][maxn];
char g[maxn][maxn];
char stamp[maxn][maxn];
int n, m, a, b;

pos_type operator+(pos_type const& lhs, pos_type const& rhs)
{
    return {lhs.first + rhs.first, lhs.second + rhs.second};
}

pos_type operator-(pos_type const& lhs, pos_type const& rhs)
{
    return {lhs.first - rhs.first, lhs.second - rhs.second};
}

bool inrange(pos_type const& p)
{
    return 0 <= p.first && p.first < n
        && 0 <= p.second && p.second < m;
}

bool run()
{
    std::cin >> n >> m >> a >> b;
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < m; j++)
            std::cin >> g[i][j];

    std::vector<pos_type> pos;
    for (auto i = 0; i < a; i++)
        for (auto j = 0; j < b; j++) {
            std::cin >> stamp[i][j];
            if (stamp[i][j] == 'x')
                pos.emplace_back(i, j);
        }

    std::fill(&vis[0][0], &vis[0][0] + sizeof(vis) / sizeof(vis[0][0]), false);

    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < m; j++) {
            if (vis[i][j] || g[i][j] != 'x') continue;
            for (auto const& p : pos) {
                auto tp = pos_type{i, j} + p - pos[0];
                if (!inrange(tp) || g[tp.first][tp.second] != 'x' || vis[tp.first][tp.second])
                    return false;
                vis[tp.first][tp.second] = true;
            }
            if (!vis[i][j])
                return false;
        }
    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    while (T--)
        std::cout << (run() ? "TAK\n" : "NIE\n");
}

