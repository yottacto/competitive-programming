// ml:run = $bin < input
// ml:std = c++03
#include <iostream>
#include <algorithm>
#include <vector>

int const  inf = 1 << 29;
int const maxn = 200;
int f[maxn][maxn];
int n, size;
int ans = inf;

std::vector<std::vector<int> > g;

void add_edge(int x, int y)
{
    g[x].push_back(y);
    g[y].push_back(x);
}

void dp(int u, int parent)
{
    f[u][1] = 0;
    for (int t = 0; t < int(g[u].size()); t++) {
        int v = g[u][t];
        if (v == parent) continue;
        dp(v, u);
        for (int i = size; i >= 1; i--) {
            int tmp = f[u][i] + 1;
            for (int j = 1; j < i; j++)
                tmp = std::min(tmp, f[u][i - j] + f[v][j]);
            f[u][i] = tmp;
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> size;
    g.resize(n + 1);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= n; j++)
            f[i][j] = inf;

    for (int i = 1; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        add_edge(x, y);
    }

    dp(1, 0);
    int ans = f[1][size];
    for (int i = 2; i <= n; i++)
        ans = std::min(ans, f[i][size] + 1);

    std::cout << ans << "\n";
}

