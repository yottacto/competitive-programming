// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <numeric>

using ll = long long;

static auto constexpr maxn = 2000007;
ll a[maxn];
ll w[maxn];
ll sum[maxn];
ll q[maxn];
int n, p, d;
int qhead{1};
int qtail{0};

auto empty()
{
    return qhead > qtail;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> p >> d;
    for (auto i = 1; i <= n; i++)
        std::cin >> a[i];
    std::partial_sum(a + 1, a + n + 1, sum + 1);

    for (auto i = 1; i + d - 1 <= n; i++)
        w[i] = sum[i + d - 1] - sum[i - 1];

    auto tail = 1;
    auto ans = 0;
    for (auto i = 1; i <= n; i++) {
        for (; tail <= n; tail++) {
            if (tail - i + 1 <= d)
                continue;
            auto tmp = w[tail - d + 1];
            if (!empty())
                tmp = std::max(tmp, q[qhead]);
            if (sum[tail] - sum[i - 1] - tmp > p)
                break;

            q[++qtail] = w[tail - d + 1];
            for (; qhead < qtail && q[qtail] > q[qtail - 1]; qtail--)
                q[qtail - 1] = q[qtail];
        }
        ans = std::max(ans, tail - i);
        if (w[i] == q[qhead])
            qhead++;
    }
    std::cout << ans << "\n";
}

