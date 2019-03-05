// ml:run = $bin < input
#include <cstdio>
#include <algorithm>

auto constexpr maxn = 1000007;
int l[2 * maxn];
int dp[2 * maxn];
int start[2 * maxn];
int n, s, sum, max;

int main()
{
    std::scanf("%d%d", &n, &s);
    for (auto i = 1; i <= n; i++) {
        std::scanf("%d", &l[i]);
        l[n + i] = l[i];
        sum += l[i];
        start[i] = i;
        max = std::max(max, l[i]);
    }
    while (s--) {
        int d;
        std::scanf("%d", &d);
        if (max > d) {
            std::printf("NIE\n");
            continue;
        }
        auto dis = sum;
        auto last = 1;
        for (auto i = n + 1; i <= 2 * n; dis += l[i++]) {
            while (dis > d)
                dis -= l[last++];
            start[i] = start[last];
            dp[i] = dp[last] + 1;
            // nice property, we can break early
            if (i - start[i] >= n) {
                std::printf("%d\n", dp[i]);
                break;
            }
        }
    }
}

