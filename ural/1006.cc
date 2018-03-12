// ml:run = $bin < input
// * indicates removed square
#include <iostream>
#include <cassert>
#include <iterator>
#include <vector>

auto constexpr maxn = 20;
auto constexpr maxm = 50;

char data[maxn][maxm];

struct square
{
    operator bool() const
    {
        return len > 0
            && 0 <= x && x < maxn
            && 0 <= y && y < maxm;
    }

    int x;
    int y;
    int len;
};

std::ostream& operator<<(std::ostream& os, square const& a)
{
    os << a.y << " " << a.x << " " << a.len;
    return os;
}

// upper left corner coordinate
bool check(int x, int y, int len) {
    if (!((data[x][y] == '*' || data[x][y] == char(218))
            && (data[x][y+len-1] == '*'       || data[x][y+len-1] == char(191))
            && (data[x+len-1][y] == '*'       || data[x+len-1][y] == char(192))
            && (data[x+len-1][y+len-1] == '*' || data[x+len-1][y+len-1] == char(217))
        ))
        return false;

    auto all = data[x][y] == '*'
        && data[x][y + len - 1] == '*'
        && data[x + len - 1][y] == '*'
        && data[x + len - 1][y + len - 1] == '*';

    for (auto i = 1; i < len - 1; i++) {
        if (!((data[x][y+i] == '*' || data[x][y+i] == char(196))
                && (data[x+len-1][y+i] == '*' || data[x+len-1][y+i] == char(196))
                && (data[x+i][y] == '*'       || data[x+i][y] == char(179))
                && (data[x+i][y+len-1] == '*' || data[x+i][y+len-1] == char(179))))
            return false;

        if (!(data[x][y + i] == '*'
                && data[x + len - 1][y + i] == '*'
                && data[x + i][y] == '*'
                && data[x + i][y + len - 1] == '*'))
            all = false;
    }
    return !all;
}

square find()
{
    for (auto i = 0; i < maxn; i++)
        for (auto j = 0; j < maxm; j++) {
            if (data[i][j] == '.') continue;
            for (auto l = 1; l <= std::min(maxn - i, maxm - j); l++) {
                if (check(i, j, l))
                    return {i, j, l};
            }
        }
    return {0, 0, 0};
}

void clear(square const& p)
{
    for (auto l = 0; l < p.len; l++) {
        data[p.x + l        ][p.y            ] = '*';
        data[p.x + l        ][p.y + p.len - 1] = '*';
        data[p.x            ][p.y + l        ] = '*';
        data[p.x + p.len - 1][p.y + l        ] = '*';
    }
}

int main()
{
    for (auto i = 0; i < maxn; i++)
        for (auto j = 0; j < maxm; j++)
            std::cin >> data[i][j];

    std::vector<square> ans;
    for (square i; (i = find()); ) {
        clear(i);
        ans.emplace_back(i);
    }

    std::cout << ans.size() << "\n";
    std::copy(
        ans.rbegin(),
        ans.rend(),
        std::ostream_iterator<square>{std::cout, "\n"}
    );
}

