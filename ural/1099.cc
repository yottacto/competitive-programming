// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <vector>
#include <deque>

auto constexpr maxn = 300;
bool g[maxn][maxn];
std::vector<int> linked;
int n;

void init()
{
    std::cin >> n;
    for (int u, v; std::cin >> u >> v; ) {
        u--; v--;
        g[u][v] = g[v][u] = true;
    }
    linked.resize(n, -1);
}

template <
    class Vec,
    class Even,
    class Deque
>
void blossom(int u, int v, int lca, Vec& ptr, Even& even, Deque& dq)
{
    for (auto i = lca + 1; i < int(ptr[u].size()); i++) {
        auto w = ptr[u][i];
        if (!even[w]) {
            ptr[w] = ptr[v];
            ptr[w].insert(
                std::end(ptr[w]),
                std::rbegin(ptr[u]),
                std::rend(ptr[u]) - i
            );
            even[w] = true;
            dq.push_back(w);
        }
    }
}

bool bfs(int root)
{
    std::vector<char> even(n);
    std::vector<char> vis(n);
    std::vector<std::vector<int>> path_to_root(n);
    auto & ptr = path_to_root;
    std::deque<int> dq;
    dq.push_front(root);
    even[root] = true;
    vis[root] = true;
    ptr[root].emplace_back(root);
    while (!dq.empty()) {
        auto u = dq.front();
        dq.pop_front();
        // u -> v -> w
        for (auto v = 0; v < n; v++) {
            if (!g[u][v] || linked[v] == v) continue;
            if (!vis[v]) {
                if (linked[v] == -1) {
                    ptr[u].emplace_back(v);
                    for (auto it = std::begin(ptr[u]);
                            it != std::end(ptr[u]);
                            it += 2) {
                        linked[*it] = *(it + 1);
                        linked[*(it + 1)] = *it;
                    }
                    return true;
                } else {
                    auto w = linked[v];
                    ptr[w] = ptr[u];
                    ptr[w].emplace_back(v);
                    ptr[w].emplace_back(w);
                    even[v] = false;
                    even[w] = true;
                    vis[v] = vis[w] = true;
                    dq.push_back(w);
                }
            } else {
                // blossom
                if (even[v]) {
                    auto lca_id = 0u;
                    while (lca_id < ptr[u].size() && lca_id < ptr[v].size()
                            && ptr[u][lca_id] == ptr[v][lca_id])
                        lca_id++;
                    lca_id--;

                    blossom(u, v, lca_id, ptr, even, dq);
                    blossom(v, u, lca_id, ptr, even, dq);
                } else
                    ;
            }
        }
    }
    return false;
}

int maximum_match()
{
    auto match = 0;
    for (auto i = 0; i < n; i++)
        if (linked[i] == -1) {
            if (bfs(i))
                match++;
            else
                linked[i] = i;
        }
    return match;
}

int main()
{
    init();

    std::cout << maximum_match() * 2 << "\n";
    for (auto i = 0; i < n; i++)
        if (linked[i] > i)
            std::cout << i + 1 << " " << linked[i] + 1 << "\n";
}

