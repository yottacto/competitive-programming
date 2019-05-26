// ml:run = $bin < input
// ml:std = c++14
#include <iostream>
#include <algorithm>
#include <deque>

auto constexpr maxn = 350;
int r, c, k;
int a[maxn][maxn];
int maxl[maxn][maxn];
int minl[maxn];

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> r >> c >> k;
        for (auto i = 0; i < r; i++)
            for (auto j = 0; j < c; j++)
                std::cin >> a[i][j];

        for (auto i = 0; i < r; i++) {
            std::deque<int> dq_small;
            std::deque<int> dq_big;
            auto front = 0;
            for (auto j = 0; j < c; j++) {
                while (!dq_big.empty() && a[i][j] >= a[i][dq_big.back()])
                    dq_big.pop_back();
                dq_big.emplace_back(j);
                while (!dq_small.empty() && a[i][j] <= a[i][dq_small.back()])
                    dq_small.pop_back();
                dq_small.emplace_back(j);
                while (a[i][dq_big.front()] - a[i][dq_small.front()] > k) {
                    if (dq_big.front() > dq_small.front()) {
                        front = dq_small.front() + 1;
                        dq_small.pop_front();
                    } else if (dq_big.front() < dq_small.front()) {
                        front = dq_big.front() + 1;
                        dq_big.pop_front();
                    } else {
                        front = dq_big.front() + 1;
                        dq_small.pop_front();
                        dq_big.pop_front();
                    }
                }
                maxl[i][j] = j - front + 1;
            }
        }

        // std::cout << "\n";
        // for (auto i = 0; i < r; i++) {
        //     for (auto j = 0; j < c; j++)
        //         std::cout << maxl[i][j] << " ";
        //     std::cout << "\n";
        // }

        auto res = 0;
        for (auto i = 0; i < r; i++) {
            for (auto k = 0; k < c; k++)
                minl[k] = maxl[i][k];
            for (auto j = i; j < r; j++) {
                for (auto k = 0; k < c; k++) {
                    minl[k] = std::min(minl[k], maxl[j][k]);
                    res = std::max(res, minl[k] * (j - i + 1));
                }
            }
        }
        std::cout << res << "\n";
    }
}

