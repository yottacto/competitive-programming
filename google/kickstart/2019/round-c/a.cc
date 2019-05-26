// ml:run = $bin < input
// ml:std = c++14
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <unordered_map>
#include <set>
#include <map>
#include <cmath>

using pair = std::pair<int, int>;

int sr, sc;
int r, c;
int n;
std::string ins;

std::vector<std::pair<int, int>> d{
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1},
};

std::map<char, int> dir{
    {'N', 0},
    {'W', 1},
    {'S', 2},
    {'E', 3},
};

std::map<std::pair<int, int>, int> jump[4];
std::set<std::pair<int, int>> vis;

void init()
{
    for (auto i = 0; i < 4; i++)
        jump[i].clear();
    vis.clear();
}

void move_to(int& r, int& c, int jump, int d)
{
    if (d == 0)
        r -= jump;
    else if (d == 2)
        r += jump;
    else if (d == 1)
        c -= jump;
    else if (d == 3)
        c += jump;
}

int neg(int d)
{
    if (d == 0)
        return 2;
    if (d == 2)
        return 0;
    if (d == 1)
        return 3;
    return 1;
}

int distance(pair const& a, pair const& b)
{
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

void move(int d)
{
    auto p = std::make_pair(sr, sc);
    auto start = p;
    while (vis.count(p)) {
        auto j = 1;
        if (jump[d].count(p))
            j = jump[d][p];
        move_to(sr, sc, j, d);
        p = std::make_pair(sr, sc);

        // std::cerr << sr << " " << sc << "\n";
    }
    vis.emplace(p);
    auto dis = distance(start, p);
    jump[d][start] = dis + 1;
    jump[neg(d)][p] = dis + 1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n >> r >> c >> sr >> sc >> ins;
        init();
        vis.emplace(std::make_pair(sr, sc));
        for (auto i = 0; i < n; i++) {
            // std::cerr << "moving " << ins[i] << "\n";
            move(dir[ins[i]]);
        }
        std::cout << sr << " " << sc << "\n";
    }
}

