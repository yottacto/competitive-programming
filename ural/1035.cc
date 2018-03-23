// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <tuple>

int const maxn = 300 * 300;
int parent[maxn];
bool vis[maxn];
std::tuple<int, int> ans[maxn];
int g[2][4][maxn];
char data[2][maxn];
int n, m;

template <class T> T abs(T x) { return x < 0 ? -x : x; }

int get_parent(int x)
{
    return x == parent[x]
        ? x
        : parent[x] = get_parent(parent[x]);
}

void set_union(int u, int v)
{
    parent[get_parent(u)] = get_parent(v);
}

enum dir { ul, ur, dr, dl };
int count(int id, int side)
{
    return g[side][ul][id] + g[side][ur][id]
        + g[side][dl][id] + g[side][dr][id];
}

int main()
{
    std::cin >> n >> m;
    auto tot = (n + 1) * (m + 1);

    for (auto i = 0; i <= tot; i++)
        parent[i] = i;

    for (auto s = 0; s < 2; s++)
        for (auto i = 1; i <= n; i++)
            for (auto j = 1; j <= m; j++) {
                auto id = (i - 1) * (m + 1) + (j - 1);
                char ch;
                std::cin >> ch;
                data[s][id] = ch;
                if (ch == 'X' || ch == '\\') {
                    set_union(id, id + m + 2);
                    g[s][dr][id] = 1;
                    g[s][ul][id + m + 2] = 1;
                }
                if (ch == 'X' || ch == '/') {
                    set_union(id + 1, id + m + 1);
                    g[s][dl][id + 1] = 1;
                    g[s][ur][id + m + 1] = 1;
                }
            }

    for (auto i = 0; i <= tot; i++) {
        auto pi = get_parent(i);
        if (count(i, 0) || count(i, 1))
            vis[pi] = true;
        auto diff = count(i, 0) - count(i, 1);
        if (diff > 0)
            std::get<0>(ans[pi]) += diff;
        else
            std::get<1>(ans[pi]) -= diff;
    }

    auto res = 0;
    for (auto i = 0; i <= tot; i++) {
        if (!vis[i]) continue;
        auto front = std::get<0>(ans[i]);
        auto back  = std::get<1>(ans[i]);
        auto tmp = std::min(front, back) + abs(front - back) / 2;
        res += tmp ? tmp : 1;
    }
    std::cout << res << "\n";
}

