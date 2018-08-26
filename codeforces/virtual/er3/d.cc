// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>

auto constexpr maxn = 200007;
auto constexpr inf = 1<<30;

using ll = long long;

int n, k, m, s;
ll dollar[maxn];
ll pound[maxn];
int type[maxn];
ll cost[maxn];
ll min_dollar[maxn];
ll min_pound[maxn];
int min_dollar_id[maxn];
int min_pound_id[maxn];

struct gadget
{
    auto cost_in_burles(ll pd, ll pp) const
    {
        if (type == 1)
            return pd * cost;
        else
            return pp * cost;
    }

    int type;
    ll cost;
    int id;
};

std::vector<gadget> g;

auto judge(int day)
{
    auto pd = min_dollar[day];
    auto pp = min_pound[day];
    std::sort(g.begin(), g.end(), [&](gadget const& lhs, gadget const& rhs) {
        return lhs.cost_in_burles(pd, pp) < rhs.cost_in_burles(pd, pp);
    });
    auto sum = 0ll;
    for (auto i = 0; i < k; i++)
        sum += g[i].cost_in_burles(pd, pp);
    return sum <= s;
}

void print(int day)
{
    auto did = min_dollar_id[day];
    auto pid = min_pound_id[day];
    for (auto i = 0; i < k; i++) {
        if (g[i].type == 1)
            std::cout << g[i].id << " " << did << "\n";
        else
            std::cout << g[i].id << " " << pid << "\n";
    }
}

void work()
{
    auto l = 1, r = n;
    while (l + 1 < r) {
        auto mid = (l + r) / 2;
        if (judge(mid))
            r = mid;
        else
            l = mid;
    }
    if (judge(l)) r = l;
    if (!judge(r)) {
        std::cout << "-1\n";
        return;
    }

    std::cout << r << "\n";
    print(r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> k >> s;
    min_dollar[0] = min_pound[0] = inf;
    for (auto i = 1; i <= n; i++) {
        std::cin >> dollar[i];
        if (dollar[i] < min_dollar[i - 1]) {
            min_dollar[i] = dollar[i];
            min_dollar_id[i] = i;
        } else {
            min_dollar[i] = min_dollar[i - 1];
            min_dollar_id[i] = min_dollar_id[i - 1];
        }
    }
    for (auto i = 1; i <= n; i++) {
        std::cin >> pound[i];
        if (pound[i] < min_pound[i - 1]) {
            min_pound[i] = pound[i];
            min_pound_id[i] = i;
        } else {
            min_pound[i] = min_pound[i - 1];
            min_pound_id[i] = min_pound_id[i - 1];
        }
    }

    g.resize(m);
    for (auto i = 0; i < m; i++) {
        std::cin >> g[i].type >> g[i].cost;
        g[i].id = i + 1;
    }

    work();
}

