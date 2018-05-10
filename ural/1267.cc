// ml:run = $bin < input
#include <iostream>
#include <cstring>

using ll = long long;
auto constexpr inf = (1ll)<<50;

ll f[1 << 17][17];
bool vis[1 << 17][17];
ll a[20];
ll sum[20];
int n;
int start;
int interval, left, right;

auto board_time(int departure, ll len, ll now)
{
    // d + l, d + l + i, d + l + i*2
    // d + l + i * k >= now
    // k >= (now - d - l) / i;
    auto k = (now - departure - len + interval - 1) / interval;
    k = std::max(0ll, k);
    return departure + len + interval * k;
}

auto calc(int from, int to, int t)
{
    ll bt;
    if (from < to) {
        bt = board_time(left, sum[from], t);
        bt += sum[to] - sum[from];
    } else {
        bt = board_time(right, sum[n - 1] - sum[from], t);
        bt += sum[from] - sum[to];
    }
    return bt + 1;
}

auto work(bool left)
{
    auto departure = 0;
    std::memset(vis, 0, sizeof(vis));
    f[1<<start][start] = 1;
    if (left) {
        departure = board_time(right, sum[n - 1] - sum[start], 1);
        for (auto i = 0; i < start; i++) {
            f[(1<<start) | (1<<i)][i] = calc(start, i, 1);
            vis[(1<<start) | (1<<i)][i] = true;
        }
    } else {
        departure = board_time(left, sum[start], 1);
        for (auto i = start + 1; i < n; i++) {
            f[(1<<start) | (1<<i)][i] = calc(start, i, 1);
            vis[(1<<start) | (1<<i)][i] = true;
        }
    }

    for (auto st = 1; st < (1<<n); st++) {
        if (!(st & (1<<start))) continue;
        for (auto i = 0; i < n; i++) {
            if (!(st & (1<<i))) continue;
            if (vis[st][i]) continue;
            auto tst = st ^ (1<<i);
            if (!(tst & (tst-1))) continue;
            for (auto j = 0; j < n; j++) {
                if (!(tst & (1<<j)) || !vis[tst][j])
                    continue;
                if (!vis[st][i]) {
                    vis[st][i] = true;
                    f[st][i] = inf;
                }
                f[st][i] = std::min(f[st][i], calc(j, i, f[tst][j]));
            }
        }
    }

    auto ans = inf;
    for (auto i = 0; i < n; i++) {
        if (!vis[(1<<n) - 1][i])
            continue;
        auto now = f[(1<<n) - 1][i];
        ans = std::min(ans, calc(i, start, now) - 1);
    }
    return ans - departure;
}


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;

    if (n == 1) {
        std::cout << "0\n";
        return 0;
    }

    for (auto i = 1; i < n; i++) {
        std::cin >> a[i];
        sum[i] = sum[i-1] + a[i];
    }
    std::cin >> start;
    start--;
    std::cin >> interval >> left >> right;

    std::cout << std::min(work(true), work(false)) << "\n";
}

