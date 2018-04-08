// ml:run = cp $bin bug
#include <iostream>
#include <vector>

auto constexpr maxn = 50;
int map[maxn][maxn];
int row[maxn];
int col[maxn];
int sum;
int n, m;

std::vector<std::vector<int>> ans;

void print()
{
    std::cerr << "sum = " << sum << "\n";
    for (auto i = 1; i <= m; i++) {
        for (auto j = 1; j <= m; j++)
            std::cerr << (map[i][j] == 1 ? '+' : '-');
        std::cerr << "\n";
    }
    std::cerr << "======================\n";
}


template <int N>
int find(int (&a)[N])
{
    for (auto i = 1; i <= m; i++)
        if (a[i] >= 2)
            return i;
    return -1;
}

void get_two_plus_in_row(int p, int& p1, int& p2)
{
    p1 = p2 = -1;
    auto i = 1;
    for (; i <= m; i++)
        if (map[p][i] == 1) {
            p1 = i++;
            break;
        }
    for (; i <= m; i++)
        if (map[p][i] == 1) {
            p2 = i;
            break;
        }
}

void get_two_plus_in_col(int p, int& p1, int& p2)
{
    p1 = p2 = -1;
    auto i = 1;
    for (; i <= m; i++)
        if (map[i][p] == 1) {
            p1 = i++;
            break;
        }
    for (; i <= m; i++)
        if (map[i][p] == 1) {
            p2 = i;
            break;
        }
}

void opt_on_rect(int r1, int r2, int c1, int c2)
{
    // std::cerr << "= " << r1 << " " << r2 << " " << c1 << " " << c2 << "\n";

    std::vector<int> a(m + 1);
    a[r1] = c1;
    a[r2] = c2;

    auto now = 1;
    for (auto i = 1; i <= m; i++) {
        if (a[i]) continue;
        while (now == c1 || now == c2)
            now++;
        a[i] = now++;
    }

    ans.emplace_back(std::move(a));
}

void plus_rect(int r1, int r2, int c1, int c2)
{
    // std::cerr << ":: " << r1 << " " << r2 << " " << c1 << " " << c2 << "\n";

    row[r1] -= map[r1][c1] + map[r1][c2];
    row[r2] -= map[r2][c1] + map[r2][c2];
    col[c1] -= map[r1][c1] + map[r2][c1];
    col[c2] -= map[r1][c2] + map[r2][c2];
    sum -= map[r1][c1] + map[r1][c2] + map[r2][c1] + map[r2][c2];
    map[r1][c1] = -map[r1][c1];
    map[r1][c2] = -map[r1][c2];
    map[r2][c1] = -map[r2][c1];
    map[r2][c2] = -map[r2][c2];

    opt_on_rect(r1, r2, c1, c2);
    opt_on_rect(r1, r2, c2, c1);
}

void adjust_row()
{
    for (auto i = 1; i <= m; i++) {
        while (row[i] > 2) {
            auto empty = 1;
            for (; empty <= m; empty++)
                if (!row[empty])
                    break;
            int c1, c2;
            get_two_plus_in_row(i, c1, c2);
            plus_rect(i, empty, c1, c2);
        }
    }
}

void adjust_col()
{
    for (auto i = 1; i <= m; i++) {
        while (col[i] > 2) {
            auto empty = 1;
            for (; empty <= m; empty++)
                if (!col[empty])
                    break;
            int r1, r2;
            get_two_plus_in_col(i, r1, r2);
            plus_rect(r1, r2, i, empty);
        }
    }
}

// row i1 i2
// col j1 j2
void transform()
{
    auto prow = find(row);
    auto pcol = find(col);
    int c1, c2;
    get_two_plus_in_row(prow, c1, c2);
    int r1, r2;
    get_two_plus_in_col(pcol, r1, r2);

    if (r1 == prow) {
        if (c1 == pcol)
            plus_rect(r1, r2, c2, pcol);
        else
            plus_rect(r1, r2, c1, pcol);
        return;
    } else if (r2 == prow) {
        if (c1 == pcol)
            plus_rect(r1, r2, c2, pcol);
        else
            plus_rect(r1, r2, c1, pcol);
        return;
    } else if (c1 == pcol) {
        plus_rect(r1, prow, c2, pcol);
        return;
    } else if (c2 == pcol) {
        plus_rect(r1, prow, c1, pcol);
        return;
    }

    plus_rect(r1, r2, c1, pcol);
    plus_rect(prow, r1, c1, c2);
}

void transform_last()
{
    std::vector<char> vis_row(m + 1);
    std::vector<char> vis_col(m + 1);
    std::vector<int> a(m + 1);

    for (auto i = 1; i <= m; i++) {
        int c1, c2;
        get_two_plus_in_row(i, c1, c2);
        if (c1 == -1)
            continue;
        if (vis_col[c1]) {
            if (c2 == -1 || vis_col[c2])
                continue;
            vis_col[c2] = vis_row[i] = true;
            a[i] = c2;
        } else {
            vis_col[c1] = vis_row[i] = true;
            a[i] = c1;
        }
    }

    std::vector<int> unvis;
    for (auto i = 1; i <= m; i++)
        if (!vis_col[i])
            unvis.emplace_back(i);

    for (auto i = 1; i <= m; i++) {
        if (vis_row[i])
            continue;
        a[i] = unvis.back();
        unvis.pop_back();
    }
    ans.emplace_back(std::move(a));
}

auto transform_able()
{
    auto prow = find(row);
    auto pcol = find(col);
    return prow != -1 && pcol != -1;
}

int main()
{
    std::cin >> n;
    m = 2 * n + 1;
    for (auto i = 1; i <= m; i++)
        for (auto j = 1; j <= m; j++) {
            char ch;
            std::cin >> ch;
            if (ch == '+') {
                map[i][j] = 1;
                row[i]++;
                col[j]++;
                sum++;
            } else
                map[i][j] = -1;
        }

    while (sum > m || (sum == m && transform_able())) {
        // print();
        transform();
        // print();
    }

    if (sum == m) {
        adjust_row();
        // print();
        adjust_col();
        // print();
        transform_last();
    }

    std::cout << "There is solution:\n";
    for (auto const& vec : ans) {
        for (auto i = 1u; i < vec.size(); i++)
            std::cout << vec[i] << " ";
        std::cout << "\n";
    }
}

