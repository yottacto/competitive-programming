// ml:run = $bin < input
#include <iostream>
#include <bitset>
#include <algorithm>
#include <vector>

auto constexpr maxn = 256;
using matrix_type = std::vector<std::bitset<maxn>>;

matrix_type mat;
std::bitset<maxn> ans;
int n;

bool gaussian_elimination()
{
    for (int i = 0; i < n; i++) {
        auto p = i;
        for (; p < n; p++)
            if (mat[p][i]) break;
        if (p >= n)
            return false;
        std::swap(mat[i], mat[p]);

        for (int j = i + 1; j < n; j++) {
            if (!mat[j][i]) continue;
            mat[j] ^= mat[i];
        }
    }

    // it's assured that there's only one solution
    // for (int i = 0; i < n; i++) {
    //     if (!mat[i][n]) continue;
    //     mat[i][n] = 0;
    //     if (mat[i].none())
    //         return false;
    //     mat[i][n] = 1;
    // }

    for (int i = n - 1; i >= 0; i--) {
        if (!mat[i][i]) continue;
        bool right = mat[i][n];
        mat[i] &= ans;
        auto tmp = mat[i].count() & 1;
        ans[i] = right ^ tmp;
    }
    return true;
}

int main()
{
    std::cin >> n;
    mat.resize(n);
    for (int i = 0; i < n; i++) {
        mat[i][n] = 1;
        for (int j; std::cin >> j && j != -1; )
            mat[j - 1][i] = 1;
    }

    if (gaussian_elimination()) {
        auto first = true;
        for (auto i = 0; i < n; i++)
            if (ans[i]) {
                if (first)
                    first = false;
                else
                    std::cout << " ";
                std::cout << i + 1;
            }
        std::cout << "\n";
    } else {
        std::cout << "No solution\n";
    }
}

