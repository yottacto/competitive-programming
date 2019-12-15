// ml:run = $bin < input
#include <bits/stdc++.h>

auto constexpr maxn = 100;
bool a[maxn][maxn];
int r, c;

bool corner()
{
    return a[0][0] || a[0][c - 1]
        || a[r - 1][0] || a[r - 1][c - 1];
}

bool full_row(int i)
{
    for (auto j = 0; j < c; j++)
        if (!a[i][j])
            return false;
    return true;
}

bool full_col(int j)
{
    for (auto i = 0; i < r; i++)
        if (!a[i][j])
            return false;
    return true;
}

bool full_edge()
{
    return full_row(0) || full_row(r - 1)
        || full_col(0) || full_col(c - 1);
}

bool full_line()
{
    for (auto i = 0; i < r; i++)
        if (full_row(i))
            return true;
    for (auto i = 0; i < c; i++)
        if (full_col(i))
            return true;
    return false;
}

bool edge_a()
{
    for (auto i = 0; i < r; i++)
        if (a[i][0] || a[i][c - 1])
            return true;

    for (auto j = 0; j < c; j++)
        if (a[0][j] || a[r - 1][j])
            return true;

    return false;
}

void work()
{
    std::cin >> r >> c;
    auto countp = 0;
    for (auto i = 0; i < r; i++)
        for (auto j = 0; j < c; j++) {
            char ch;
            std::cin >> ch;
            a[i][j] = ch == 'A';
            if (ch == 'P')
                countp++;
        }
    if (countp == r * c) {
        std::cout << "MORTAL\n";
        return;
    }
    if (!countp) {
        std::cout << "0\n";
        return;
    }
    auto res = 4;
    if (corner()) {
        res = 2;
        if (full_edge())
            res = 1;
    } else {
        if (full_line())
            res = 2;
        else if (edge_a())
            res = 3;
    }
    std::cout << res << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        work();
    }
}

