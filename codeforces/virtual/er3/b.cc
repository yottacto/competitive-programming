// ml:run = $bin < input
#include <iostream>
#include <unordered_map>

using ll = long long;
ll n, m;

auto c2(ll n)
{
    return n * (n - 1) / 2;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    std::unordered_map<int, int> count;
    auto ans = c2(n);
    for (auto i = 0; i < n; i++) {
        int g;
        std::cin >> g;
        count[g]++;
    }
    for (auto const& p : count)
        ans -= c2(p.second);
    std::cout << ans << "\n";
}

