// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;

auto constexpr maxn = 1000007;
auto constexpr inf = (1ll) << 60;
ll a[maxn];
ll b[maxn];
int n;
ll sum;

ll check(ll x)
{
    for (auto i = 0; i < n; i++)
        b[i] = a[i];
    auto move = 0ll;
    for (auto l = 0; l < n; ) {
        if (b[l] > x)
            b[l] %= x;
        auto r = l;
        auto tsum = 0ll;
        while (r < n && tsum < x) {
            tsum += b[r];
            r++;
        }
        if (!tsum)
            break;
        auto delta = tsum - x;
        b[r - 1] -= delta;

        auto half = (x + 1) / 2;
        auto mid = l;
        tsum = 0ll;
        while (mid < n && tsum < half) {
            tsum += b[mid];
            mid++;
        }
        mid--;

        for (auto i = l; i < r; i++)
            move += (ll)(std::abs(i - mid)) * b[i];

        b[r - 1] = delta;
        l = r - 1;

    }
    // std::cerr << "check [" << x << "] = " << move << "\n";
    return move;
}

ll work()
{
    auto ans = inf;
    auto tn = sum;
    for (auto i = 2ll; i * i <= tn; i++) {
        if (tn % i)
            continue;
        while (!(tn % i))
            tn /= i;
        ans = std::min(ans, check(i));
    }
    if (tn > 1)
        ans = std::min(ans, check(tn));
    if (ans == inf)
        return -1;
    return ans;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n;
    for (auto i = 0; i < n; i++) {
        std::cin >> a[i];
        sum += a[i];
    }

    std::cout << work() << "\n";
}

