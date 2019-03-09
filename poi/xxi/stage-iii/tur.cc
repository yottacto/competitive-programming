// ml:run = $bin < input
#include <cstdio>
#include <cstring>
#include <vector>

auto constexpr maxn = 20007;
auto constexpr maxd = 10;
auto constexpr maxs = 59049 + 7;
auto constexpr  inf = 0x3f3f3f3f;
bool vis[maxn];
int depth[maxn];
int connected[maxd];
int cost[maxn];
int dp[maxd][maxs];
int n, m;
int ans;

int power3[maxd];

std::vector<std::vector<int>> g;

auto max_state(int d)
{
    return power3[d];
    // return (1<<(2*d));
}

auto blank_state(int s)
{
    return false;
    // return (s+1) % 4 == 0;
}

auto ith_bit(int s, int i)
{
    return (s / power3[i]) % 3;
    // return (s >> (2 * i)) & 3;
}

auto ith_power(int i)
{
    return power3[i];
    // return 1 << (2*i);
}

void dfs(int u, int d = 0)
{
    depth[u] = d;
    vis[u] = true;

    std::memset(dp[d], 0x3f, sizeof(dp[d]));

    if (!d) {
        dp[0][0] = cost[u];
        dp[0][1] = 0;
        dp[0][2] = inf;
    } else {
        for (auto i = 0; i < d; i++)
            connected[i] = false;
        for (auto v : g[u])
            if (vis[v])
                connected[depth[v]] = true;
        for (auto s = 0; s < max_state(d); s++) {
            if (blank_state(s) || dp[d - 1][s] >= inf)
                continue;
            auto covered = false;
            auto new_state = s;
            for (auto i = 0; i < d; i++) {
                covered |= connected[i] && ith_bit(s, i) == 0;
                new_state += ith_power(i) * (connected[i] && ith_bit(s, i) == 1);
            }

            if (covered)
                dp[d][s + 2 * ith_power(d)] = std::min(
                    dp[d][s + 2 * ith_power(d)],
                    dp[d - 1][s]
                );
            else
                dp[d][s + ith_power(d)] = std::min(
                    dp[d][s + ith_power(d)],
                    dp[d - 1][s]
                );

            dp[d][new_state] = std::min(
                dp[d][new_state],
                dp[d - 1][s] + cost[u]
            );
        }
    }

    for (auto v : g[u]) {
        if (vis[v])
            continue;
        dfs(v, d + 1);
        for (auto s = 0; s < max_state(d + 1); s++)
            dp[d][s] = std::min(dp[d + 1][s], dp[d + 1][s + 2 * ith_power(d + 1)]);
    }
}

int main()
{
    power3[0] = 1;
    for (auto i = 1; i < maxd; i++)
        power3[i] = power3[i - 1] * 3;

    std::scanf("%d%d", &n, &m);
    g.resize(n + 1);
    for (auto i = 1; i <= n; i++)
        std::scanf("%d", &cost[i]);
    for (auto i = 0; i < m; i++) {
        int u, v;
        std::scanf("%d%d", &u, &v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }

    for (auto i = 1; i <= n; i++)
        if (!vis[i]) {
            dfs(i);
            ans += std::min(dp[0][0], dp[0][2]);
        }
    std::printf("%d\n", ans);
}

