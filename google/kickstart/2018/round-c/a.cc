// ml:run = $bin < A-large.in > a-large0.out
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

auto constexpr maxn = 2000;
bool vis[maxn];
int dis[maxn];
int circle[maxn];
int len;
int n;

std::vector<std::vector<int>> g;

void init()
{
    g.clear();
    g.resize(n + 1);
    std::fill(vis, vis + n + 1, false);
    std::fill(dis, dis + n + 1, 0);
    len = 0;
}

bool dfs(int u, int parent)
{
    vis[u] = true;
    for (auto v : g[u]) {
        if (v == parent) continue;
        circle[++len] = v;
        if (vis[v]) return true;
        if (dfs(v, u)) return true;
        len--;
    }
    return false;
}

int main()
{
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n;
        init();
        for (auto i = 0; i < n; i++) {
            int x, y;
            std::cin >> x >> y;
            g[x].emplace_back(y);
            g[y].emplace_back(x);
        }

        circle[++len] = 1;
        dfs(1, -1);
        std::queue<int> q;
        std::fill(vis, vis + n + 1, false);

        auto last = circle[len];
        q.push(last);
        vis[last] = true;
        for (auto i = len - 1; i >= 1 && circle[i] != last; i--) {
            q.push(circle[i]);
            vis[circle[i]] = true;
        }

        while (!q.empty()) {
            auto u = q.front();
            q.pop();
            for (auto v : g[u]) {
                if (vis[v]) continue;
                vis[v] = true;
                q.push(v);
                dis[v] = dis[u] + 1;
            }
        }

        for (auto i = 1; i <= n; i++)
            std::cout << dis[i] << " ";
        std::cout << "\n";

    }
}

