// ml:run = $bin < input
// ml:run = $bin < C-small-attempt0.in > c-small0.out
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

auto constexpr maxn = 200;
char a[maxn][maxn];
int b[maxn][maxn];
int sum[maxn][maxn];
bool words[30];
int n;
int r, c, w;

int gcd(int a, int b)
{
    return !b ? a : gcd(b, a % b);
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> r >> c >> w;
        for (auto i = 1; i <= r; i++)
            for (auto j = 1; j <= c; j++)
                std::cin >> a[i][j];
        for (auto i = 0; i < 30; i++)
            words[i] = false;
        for (auto i = 0; i < w; i++) {
            char ch; std::cin >> ch;
            words[ch - 'A'] = true;
        }
        for (auto i = 1; i <= r; i++)
            for (auto j = 1; j <= c; j++) {
                b[i][j] = words[a[i][j] - 'A'];
                sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1] + b[i][j];
            }

        auto as = -1;
        auto at = 1;
        auto count = 0;
        for (auto x1 = 1; x1 <= r; x1++)
        for (auto y1 = 1; y1 <= c; y1++)
            for (auto x2 = x1; x2 <= r; x2++)
            for (auto y2 = y1; y2 <= c; y2++) {
                auto s = sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
                s *= 4;
                auto t = x2 - x1 + 1 + y2 - y1 + 1;
                // std::cout << s << " " << t << " ::\n";
                auto g = gcd(s, t);
                s /= g;
                t /= g;
                if (s * at > as * t) {
                    count = 1;
                    as = s;
                    at = t;
                } else if (s * at == as * t)
                    count++;
            }
        std::cout << as << "/" << at << " " << count << "\n";
    }
}

