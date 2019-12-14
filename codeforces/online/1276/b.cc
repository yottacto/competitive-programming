// ml:run = $bin < input
#include <bits/stdc++.h>

int n, m, a, b;
std::vector<std::vector<int>> g;
std::vector<int> mark[2];

void add_edge(int x, int y)
{
    g[x].emplace_back(y);
    g[y].emplace_back(x);
}

void bfs(int start, int label)
{
    std::queue<int> q;
    for (auto v : g[start])
        if (v != a && v != b) {
            q.emplace(v);
            mark[label][v] = true;
        }

    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        for (auto v : g[u]) {
            if (v == a || v == b || mark[label][v])
                continue;
            mark[label][v] = true;
            q.emplace(v);
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n >> m >> a >> b;
        g.clear();
        g.resize(n + 1);
        for (auto i = 0; i < 2; i++) {
            mark[i].clear();
            mark[i].resize(n + 1);
        }
        for (auto i = 0; i < m; i++) {
            int x, y;
            std::cin >> x >> y;
            add_edge(x, y);
        }

        bfs(a, 0);
        bfs(b, 1);

        auto count0 = 0ll;
        auto count1 = 0ll;

        // for (auto i = 1; i <= n; i++)
        //     std::cout << mark[0][i] << " ";
        // std::cout << "\n";

        // for (auto i = 1; i <= n; i++)
        //     std::cout << mark[1][i] << " ";
        // std::cout << "\n";

        for (auto i = 1; i <= n; i++) {
            if (i == a || i == b || (mark[0][i] && mark[1][i]))
                continue;
            if (mark[0][i])
                count0++;
            if (mark[1][i])
                count1++;
        }
        // std::cout << count0 << " " << count1 << "\n";
        std::cout << count0 * count1 << "\n";
    }
}

