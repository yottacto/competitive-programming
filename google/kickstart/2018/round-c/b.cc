// ml:run = $bin < B-large.in > b-large0.out
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

auto constexpr maxn = 20;
bool vis[maxn];
int a[maxn][maxn];
int n;
int m;
int ans;

struct edge
{
    int u, v, len;
};

std::vector<edge> edges;

void dfs(int now, int sum, int count)
{
    for (auto i = now; i < m; i++) {
        auto const& e = edges[i];
        auto u = e.u;
        auto v = e.v;
        auto l = e.len;
        if (vis[u] | vis[v])
            continue;
        vis[u] = vis[v] = true;
        if (count >= 2 && sum > l)
            ans++;
        dfs(i + 1, sum + l, count + 1);
        vis[u] = vis[v] = false;
    }
}

int main()
{
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n;

        // init
        ans = 0;
        std::fill(vis, vis + n + 1, false);
        edges.clear();

        for (auto i = 1; i <= n; i++)
            for (auto j = 1; j <= n; j++)
                std::cin >> a[i][j];

        for (auto i = 1; i <= n; i++)
            for (auto j = i + 1; j <= n; j++)
                if (a[i][j])
                    edges.emplace_back(edge{i, j, a[i][j]});

        m = edges.size();
        std::sort(std::begin(edges), std::end(edges),
            [](auto const& lhs, auto const& rhs) {
                return lhs.len < rhs.len;
            });

        dfs(0, 0, 0);

        std::cout << ans << "\n";
    }
}

