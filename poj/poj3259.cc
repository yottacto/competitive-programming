// ml:run = $bin < input
// ml:std = c++03
#include <iostream>
#include <vector>
#include <deque>

struct edge
{
    edge(int u, int v, int w) : u(u), v(v), w(w) {}
    int u, v, w;
};

int const maxn = 505;
int const  inf = 1 << 28;
int n, m, w;

std::vector<std::vector<edge> > g;
std::deque<int> relax;
int count[maxn];
bool vis[maxn];
bool inqueue[maxn];

void add_edge(int u, int v, int w)
{
    g[u].push_back(edge(u, v, w));
}

int dist[maxn];

bool spfa_negative_circle(int s)
{
    dist[s] = 0;
    vis[s] = true;
    count[s] = 1;
    relax.push_back(s);
    while (!relax.empty()) {
        int now = relax.front();
        relax.pop_front();

        for (int i = 0; i < int(g[now].size()); i++) {
            int v = g[now][i].v;
            int w = g[now][i].w;
            if (dist[now] + w < dist[v]) {
                dist[v] = dist[now] + w;
                vis[v] = true;
                if (!inqueue[v]) {
                    count[v]++;
                    if (count[v] > n)
                        return true;
                    if (!relax.empty() && dist[v] < dist[relax.front()])
                        relax.push_front(v);
                    else
                        relax.push_back(v);
                    inqueue[v] = true;
                }
            }
        }

        inqueue[now] = false;
    }
    return false;
}

void init()
{
    g.clear();
    g.resize(n + 1);
    relax.clear();
    for (int i = 1; i <= n; i++) {
        dist[i] = inf;
        count[i] = 0;
        inqueue[i] = vis[i] = false;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    int f; std::cin >> f;
    while (f--) {
        std::cin >> n >> m >> w;
        init();
        for (int i = 0; i < m; i++) {
            int x, y, z;
            std::cin >> x >> y >> z;
            add_edge(x, y, z);
            add_edge(y, x, z);
        }
        for (int i = 0; i < w; i++) {
            int x, y, z;
            std::cin >> x >> y >> z;
            add_edge(x, y, -z);
        }

        bool neg = false;
        for (int i = 1; i <= n; i++)
            if (!vis[i] && spfa_negative_circle(i)) {
                neg = true;
                break;
            }
        std::cout << (neg ? "YES" : "NO") << "\n";
    }
}

