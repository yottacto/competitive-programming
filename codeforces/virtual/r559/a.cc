// ml:run = $bin < input
// ml:std = c++14
#include <iostream>
#include <algorithm>
#include <queue>

using ll = long long;

auto constexpr maxn = 100007;
ll b[maxn];
ll g[maxn];
int n, m;
ll res;
ll max;

struct data
{
    ll value;
    int count;
};

auto operator<(data const& a, data const& b)
{
    return a.value < b.value;
}

ll work()
{
    std::priority_queue<data> pq;
    for (auto i = 0; i < n; i++)
        pq.emplace(data{b[i], m - 1});

    std::sort(g, g + m);
    for (auto i = 0; i < m; i++) {
        auto top = pq.top();
        pq.pop();
        if (g[i] < max) {
            return -1;
        } else {
            if (g[i] != top.value)
                top.count--;
            res += g[i] - top.value;
            if (top.count)
                pq.emplace(top);
        }
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    for (auto i = 0; i < n; i++) {
        std::cin >> b[i];
        res += b[i] * m;
        max = std::max(max, b[i]);
    }
    for (auto i = 0; i < m; i++)
        std::cin >> g[i];

    std::cout << work() << "\n";
}

