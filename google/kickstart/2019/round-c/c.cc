// ml:run = $bin < input
// ml:std = c++14
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

auto constexpr maxn = 1500;
auto constexpr  inf = 1<<30;
int p[maxn];
int a[maxn];
int f[2][maxn][2];
int n, k;

struct data
{
    int pos;
    int color;
};

int main()
{
    std::ios::sync_with_stdio(false);
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n >> k;
        for (auto i = 0; i < n; i++)
            std::cin >> p[i];

        std::vector<data> da;
        for (auto i = 0; i < n; i++) {
            std::cin >> a[i];
            da.emplace_back(data{p[i], a[i]});
        }
        std::sort(da.begin(), da.end(), [](auto const& a, auto const& b) {
            return a.pos < b.pos;
        });

        auto id = 0;
        std::map<int, int> color;
        std::vector<std::vector<data>> all;
        for (auto const& d : da) {
            if (!color.count(d.color)) {
                color[d.color] = id++;
                all.emplace_back();
            }
            auto tid = color[d.color];
            all[tid].emplace_back(d);
        }

        auto now = 1;
        auto prev = 0;
        // init f
        f[0][0][0] = f[1][0][1] = 0;
        for (auto i = 1; i <= k; i++)
            f[0][i][0] = f[1][i][0] = f[0][i][1] = f[1][i][1]
                = inf;

        for (auto i = 0; i < id; i++) {
            std::swap(now, prev);
            for (auto ki = 1; ki <= k; ki++) {
                f[now][ki][0] = f[prev][ki][0];
                f[now][ki][1] = f[prev][ki][1];
                for (auto j = 0; j < std::min<int>(all[i].size(), ki); j++) {
                    f[now][ki][0] = std::min(
                        f[now][ki][0],
                        f[prev][ki - j - 1][0] + all[i][j].pos * 2
                    );
                    f[now][ki][1] = std::min(
                        f[now][ki][1],
                        f[prev][ki - j - 1][0] + all[i][j].pos
                    );
                    f[now][ki][1] = std::min(
                        f[now][ki][1],
                        f[prev][ki - j - 1][1] + all[i][j].pos * 2
                    );
                }
            }
        }
        std::cout << f[now][k][1] << "\n";
    }
}

