// ml:run = $bin < bfdiff.in
// ml:run = cp $bin std
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

auto constexpr maxn = 50;
int map[maxn][maxn];
int row[maxn];
int col[maxn];
int sum;
int n, m;

void print()
{
    for (auto i = 1; i <= m; i++) {
        for (auto j = 1; j <= m; j++)
            std::cerr << (map[i][j] == 1 ? '+' : '-');
        std::cerr << "\n";
    }
    std::cerr << "======================\n";
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

    std::ifstream fin{"bfdiff.out1"};
    std::string s;
    std::getline(fin, s);

    do {
        std::vector<int> v;
        std::getline(fin, s);
        std::stringstream buf{s};
        int x;
        while (buf >> x)
            v.emplace_back(x);
        if (v.empty())
            break;

        for (auto i = 0u; i < v.size(); i++)
            map[i + 1][v[i]] = -map[i + 1][v[i]];

        // print();

    } while (true);

    auto sum = 0;
    for (auto i = 1; i <= m; i++)
        for (auto j = 1; j <= m; j++)
            sum += (map[i][j] == 1);

    if (sum <= 2 * n)
        std::cout << "YES\n\n";
    else
        std::cout << "NO\n";
}

