// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>

auto constexpr maxn = 100007;
int back[maxn], not_back[maxn];
int n, k;

std::vector<std::vector<std::pair<int, int>>> tree;

void add_edge(int u, int v, int w)
{
    tree[u].emplace_back(v, w);
    tree[v].emplace_back(u, w);
}

using pair_type = std::pair<int, int>;
using pq_type = std::priority_queue<
    pair_type,
    std::vector<pair_type>,
    std::greater<pair_type>
>;

void dfs(int u, int parent)
{
    pq_type pq;
    auto max_not_back = 0;
    auto max_back = 0;
    for (auto const& e : tree[u]) {
        auto [v, w] = e;
        if (v == parent)
            continue;
        dfs(v, u);
        pq.emplace(back[v] + w, not_back[v] + w);
        if ((int)pq.size() > k - 1) {
            max_not_back = std::max(max_not_back, pq.top().second);
            max_back = std::max(max_back, pq.top().first);
            pq.pop();
        }
    }
    auto sum = 0;
    auto max_delta = 0;
    while (!pq.empty()) {
        sum += pq.top().first;
        max_delta = std::max(max_delta, pq.top().second - pq.top().first);
        pq.pop();
    }
    back[u] = sum;
    not_back[u] = std::max(
        sum + max_not_back,
        sum + max_back + max_delta
    );
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> k;
    tree.resize(n);
    for (auto i = 1; i < n; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        add_edge(u, v, w);
    }
    dfs(0, -1);
    std::cout << not_back[0] << "\n";
}

