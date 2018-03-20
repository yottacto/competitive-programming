// ml:run = $bin < input
#include <iostream>
#include <map>

auto constexpr maxn = 222;
int map[maxn][maxn][2];
// single stich only map
int sm[maxn][maxn];

std::map<char, int> const id{
    {'.', 0},
    {'/', 1},
    {'\\', 2},
    {'X', 3},
};

struct pos
{
    int x;
    int y;
    int f; // face
    int d; // direction of slash (slash or backslash)
};

std::ostream& operator<<(std::ostream& os, pos const& p)
{
    os << "(x, y) = (" << p.x << ", " << p.y << "), (face, dir) = " << p.f << ", " << p.d << ")";
    return os;
}

int n, m;

int constexpr opt[2][6][3] = {
    {
        {-1, +0, 1},
        {-1, +1, 0},
        {+0, +1, 1},
        {+1, +0, 1},
        {+1, -1, 0},
        {+0, -1, 1},
    },
    {
        {+0, -1, 0},
        {-1, -1, 1},
        {-1, +0, 0},
        {+0, +1, 0},
        {+1, +1, 1},
        {+1, +0, 0},
    }
};

pos next(pos p, int step)
{
    p.x += opt[p.d][step][0];
    p.y += opt[p.d][step][1];
    p.f  = 1 - p.f;
    p.d  = opt[p.d][step][2];
    return p;
}

template <class Predicate1, class Predicate2, class Predicate3>
bool dfs(pos const& p, Predicate1 pred1, Predicate2 pred2, Predicate3 remove, bool all = true)
{
    // std::cerr << "|\n" << p << "\n=>\n";
    remove(p);
    auto ret = false;
    for (auto i = 0; i < 6; i++) {
        auto next_p = next(p, i);
        // std::cerr << next_p << "\n";
        ret |= pred2(next_p);
        if (pred1(next_p))
            ret |= dfs(next_p, pred1, pred2, remove, all);
        if (!all && ret)
            return ret;
    }
    return !all | ret;
}

bool has_stich(pos const& p)
{
    return map[p.x][p.y][p.f] & (1 << p.d);
}

bool one_stich(pos const& p)
{
    return (map[p.x][p.y][p.f]     & (1 << p.d))
         ^ (map[p.x][p.y][1 - p.f] & (1 << p.d));
}

bool double_stiches(pos const& p)
{
    return (map[p.x][p.y][p.f]     & (1 << p.d))
        && (map[p.x][p.y][1 - p.f] & (1 << p.d));
}

void remove_double_stiches(pos const& p)
{
    map[p.x][p.y][p.f]     |= (1 << p.d);
    map[p.x][p.y][p.f]     ^= (1 << p.d);
    map[p.x][p.y][1 - p.f] |= (1 << p.d);
    map[p.x][p.y][1 - p.f] ^= (1 << p.d);
}

void remove_current_stich(pos const& p)
{
    map[p.x][p.y][p.f] |= (1 << p.d);
    map[p.x][p.y][p.f] ^= (1 << p.d);
}

int make_double()
{
    auto count = 0;
    for (auto i = 0; i < n; i++)
    for (auto j = 0; j < m; j++)
        for (auto f = 0; f < 2; f++)
        for (auto d = 0; d < 2; d++) {
                auto now = pos{i, j, f, d};
                if (!double_stiches(now)) continue;
                count += !dfs(now, [](pos const& p) {
                    return double_stiches(p);
                }, [](pos const& p) {
                    return one_stich(p);
                }, [](pos const& p) {
                    remove_double_stiches(p);
                });
            }
    return count;
}

int make_single()
{
    auto count = 0;
    for (auto i = 0; i < n; i++)
    for (auto j = 0; j < m; j++)
        for (auto f = 0; f < 2; f++)
        for (auto d = 0; d < 2; d++) {
                auto now = pos{i, j, f, d};
                if (!has_stich(now)) continue;

                // std::cout << now << "\n";

                count += dfs(now, [](pos const& p) {
                    return has_stich(p);
                }, [](pos const&) {
                    return false;
                }, [](pos const& p) {
                    remove_current_stich(p);
                }, false);
            }
    return count;
}

#define DEBUG 1

void print()
{
#if DEBUG
    std::cout << "\n==============================\n";
    for (auto f = 0; f < 2; f++) {
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < m; j++) {
                char ch = '.';
                if (map[i][j][f] == 1)
                    ch = '/';
                else if (map[i][j][f] == 2)
                    ch = '\\';
                else if (map[i][j][f] == 3)
                    ch = 'X';
                std::cout << ch;
            }
            std::cout << "\n";
        }
        if (!f) std::cout << "------------------------------\n";
    }
    std::cout << "==============================\n";
#else
#endif
}

int main()
{
    std::cin >> n >> m;
    for (auto f = 0; f < 2; f++) {
        for (auto i = 0; i < n; i++)
            for (auto j = 0; j < m; j++) {
                char ch;
                std::cin >> ch;
                map[i][j][f] |= id.at(ch);
            }
    }

    auto ans = make_double();

    std::cout << ans << "\n";
    print();

    ans += make_single();

    print();

    std::cout << ans << "\n";
}

