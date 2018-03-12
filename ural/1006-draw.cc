#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <iterator>

std::string map[20][50];

int main()
{
    std::ifstream fin{"output"};
    std::ofstream fout{"input"};

    std::fill(&map[0][0], &map[0][0] + sizeof(map) / sizeof(map[0][0]), ".");

    {
        int n;
        fin >> n;
        for (auto i = 0; i < n; i++) {
            int row;
            int col;
            int len;
            fin >> col >> row >> len;
            for (int i = 0; i < len; i++) {
                map[row + i][col]
                    = map[row + i][col + len - 1]
                    = "│";

                map[row][col + i]
                    = map[row + len - 1][col + i]
                    = "─";

                map[row          ][col]           = "┌";
                map[row + len - 1][col]           = "└";
                map[row          ][col + len - 1] = "┐";
                map[row + len - 1][col + len - 1] = "┘";
            }
        }
    }

    std::map<std::string, char> m{
        {"┌", char(218)},
        {"┐", char(191)},
        {"└", char(192)},
        {"┘", char(217)},
        {"│", char(179)},
        {"─", char(196)},
        {".", char('.')},
    };

    for (auto i = 0; i < 20; i++) {
        std::copy(map[i], map[i + 1], std::ostream_iterator<std::string>{fout});
        // for (auto j = 0; j < 50; j++) fout << m[map[i][j]];
        fout << "\n";
    }
}

