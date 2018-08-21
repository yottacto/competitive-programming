// ml:run = $bin < B-small-attempt0.in > test.out
// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <cmath>
#include <set>
#include <unordered_set>

using ll = long long;
auto constexpr maxn = 2000;
int n, k;
ll p[maxn];
ll h[maxn];
ll x[maxn];
ll y[maxn];

struct pos
{
    ll x, y;
    bool t;
};

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

        std::vector<pos> all;
        all.reserve(n+k);
        for (auto i = 1; i <= n; i++)
            all.emplace_back(pos{p[i], h[i], true});
        for (auto i = 1; i <= k; i++)
            all.emplace_back(pos{x[i], y[i], false});
        std::sort(all.begin(), all.end(), [](pos const& lhs, pos const& rhs) {
            return lhs.x < rhs.x
                || (lhs.x == rhs.x && lhs.t);
        });

        auto cut = 0ll;
        std::unordered_set<int> ans;
        std::set<ll> s;
        s.insert(all[0].y);
        for (auto i = 1; i < n + k; i++) {
            auto delta = all[i].x - all[i-1].x;
            auto y = all[i].y;
            cut += delta;
            if (!all[i].t) {
                auto h = *std::prev(s.end());
                if (h - cut >= y)
                    ans.insert(i);
            }
            s.insert(y + cut);
        }
        s.clear();
        s.insert(all[n+k-1].y);
        for (auto i = n + k - 2; i >= 0; i--) {
            auto delta = all[i].x - all[i+1].x;
            auto y = all[i].y;
            cut += delta;
            if (!all[i].t) {
                auto h = *std::prev(s.end());
                if (h - cut >= y)
                    ans.insert(i);
            }
            s.insert(y + cut);
        }
        std::cout << ans.size() << "\n";
    }
}

