// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr mo = 1000000007ll;
auto constexpr maxn = 100007;
ll f[maxn];
ll sum[maxn];
ll n, m;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> m;
    f[1] = 1;
    f[2] = 2;
    for (auto i = 3; i < maxn; i++)
        f[i] = (f[i - 1] + f[i - 2]) % mo;
    ll res = (f[n] + f[m] - 1) * 2;
    res %= mo;
    std::cout << res << "\n";
}

