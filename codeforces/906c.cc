// ml:run = $bin < input
#include <iostream>
#include <unordered_map>
#include <vector>

std::unordered_map<int, int> left_most;

auto constexpr maxn = 23;
auto constexpr max_size = 1 << maxn;
bool connected[max_size];
int neighbor[maxn];
int neighbor_mask[max_size];
std::vector<std::vector<int>> g;
int n, m;

int lowbit(int x) { return x & -x; }

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;

    for (int i = 0; i <= n; i++)
        left_most[1 << i] = i;
    g.resize(n);

    for (int i = 0; i < m; i++) {
        int x, y;
        std::cin >> x >> y;
        x--; y--;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    // calc neighbor
    auto all = true;
    for (auto i = 0; i < n; i++) {
        neighbor[i] |= 1 << i;
        for (auto v : g[i])
            neighbor[i] |= 1 << v;
        if (neighbor[i] != (1 << n) - 1)
            all = false;
    }

    if (all) { std::cout << "0\n"; return 0; }

    auto ans = n;
    auto ans_state = (1 << n) - 1;
    for (int i = 0; i < n; i++)
        connected[1 << i] = true;
    for (auto state = 1; state < (1 << n); state++) {
        if (!connected[state]) continue;
        auto count = 0;
        for (auto ts = state; ts; ts ^= lowbit(ts), count++) {
            auto now = left_most[lowbit(ts)];
            neighbor_mask[state] |= neighbor[now];
        }
        for (auto ts = neighbor_mask[state] ^ state; ts; ts ^= lowbit(ts)) {
            auto now = left_most[lowbit(ts)];
            connected[state | (1 << now)] = true;
        }

        if (neighbor_mask[state] == (1 << n) - 1)
            if (count < ans) {
                ans = count;
                ans_state = state;
            }
    }

    std::cout << ans << "\n";
    for (int i = 0; i < n; i++)
        if (ans_state & (1 << i))
            std::cout << i + 1 << " ";
    std::cout << "\n";
}

