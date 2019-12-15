// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr mo = 1000000007ll;

std::string s;
ll x;
ll res;

ll add(ll x, ll y)
{
    return (((x + y) % mo) + mo) % mo;
}

ll mul(ll x, ll y)
{
    return (x * y) % mo;
}

void append(ll l, ll r, ll times)
{
    for (auto i = 0; i < times && (ll)s.size() < x; i++)
        for (auto j = l; j < r && (ll)s.size() < x; j++)
            s += s[j];
    res = add(res, mul(times, r - l));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> x >> s;
        res = s.size();
        auto l = 0;
        for (; l < x; ) {
            if (l == res)
                break;
            l++;
            append(l, res, s[l - 1] - '0' - 1);
            // std::cout << l << " " << res << " " << s[l - 1] - '0' << "\n";
        }
        std::cout << res << "\n";
    }
}

