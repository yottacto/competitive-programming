// ml:run = $bin < input
// ml:run = $bin < B-small-attempt0.in > b-small0.out
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using ll = long long;
auto constexpr maxn = 2000;
int n, k;
ll p[maxn];
ll h[maxn];
ll x[maxn];
ll y[maxn];

void gen(ll arr[], int n)
{
    ll a, b, c, m;
    std::cin >> arr[1] >> arr[2] >> a >> b >> c >> m;
    for (auto i = 3; i <= n; i++)
        arr[i] = (a * arr[i - 1] + b * arr[i - 2] + c) % m + 1;
}

bool collectable(int pos)
{
    auto px = x[pos];
    auto py = y[pos];
    for (auto i = 1; i <= n; i++) {
        auto th = std::abs(px - p[i]) + py;
        if (th <= h[i])
            return true;
    }
    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n >> k;
        gen(p, n);
        gen(h, n);
        gen(x, k);
        gen(y, k);

        auto ans = 0;
        for (auto i = 1; i <= k; i++)
            ans += collectable(i);
        std::cout << ans << "\n";
    }
}

