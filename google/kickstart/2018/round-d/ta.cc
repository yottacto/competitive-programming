// ml:run = $bin < input
// ml:run = $bin < A-small-attempt3.in > a-small3.out
#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>

using ll = long long;
auto constexpr maxn = 500007;
auto constexpr inf = (1ll) << 44;
ll n, o, d;
ll x1, x2, a, b, c, m, l;
ll num[maxn];

int main()
{
    std::ios::sync_with_stdio(false);
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n >> o >> d;
        std::cin >> x1 >> x2 >> a >> b >> c >> m >> l;
        // if (d < 0) {
        //     std::cout << "IMPOSSIBLE\n";
        //     continue;
        // }
        ll sum = 0;
        ll count = 0;
        num[1] = x1 + l;
        num[2] = x2 + l;
        for (auto i = 3; i <= n; i++) {
            auto x3 = (a * x2 + b * x1 + c) % m;
            num[i] = x3 + l;
            x1 = x2;
            x2 = x3;
        }
        std::deque<ll> dq;
        ll ans = -inf;
        for (auto i = 1; i <= n; i++) {
            dq.emplace_back(num[i]);
            sum += num[i];
            count += num[i] & 1;
            while (!dq.empty() && (count > o || sum > d)) {
                auto t = dq.front();
                dq.pop_front();
                sum -= t;
                count -= t & 1;
            }
            if (!dq.empty())
                ans = std::max(ans, sum);
        }
        if (ans == -inf)
            std::cout << "IMPOSSIBLE\n";
        else
            std::cout << ans << "\n";
    }
}

