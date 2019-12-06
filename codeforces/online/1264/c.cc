// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr mo = 998244353ll;
auto constexpr maxn = 200008;
int n, q;
ll p[maxn];
ll sum[maxn];
ll prod[maxn];
bool check[maxn];
ll inv100;
ll res;

std::set<ll> all;
std::unordered_map<int, ll> dis;

ll mul(ll a, ll b)
{
    return (a * b) % mo;
}

ll add(ll a, ll b)
{
    return (a + b) % mo;
}

ll sub(ll a, ll b)
{
    return (((a - b) % mo) + mo) % mo;
}

ll quick(ll a, ll b)
{
    if (!b)
        return 1;
    auto tmp = quick(a, b / 2);
    tmp = mul(tmp, tmp);
    if (b & 1)
        tmp = mul(tmp, a);
    return tmp;
}

ll inverse(ll x)
{
    return quick(x, mo - 2);
}

ll calc(ll i, ll j)
{
    i--;
    j--;
    return mul(sub(sum[i], sum[j]), prod[j]);
}

void add(int x)
{
    auto next = *all.lower_bound(x);
    auto prev = *std::prev(all.lower_bound(x));
    res = sub(res, dis[prev]);
    dis[prev] = calc(prev, x);
    all.emplace(x);
    dis[x] = calc(x, next);
    res = add(res, add(dis[prev], dis[x]));
}

void remove(int x)
{
    auto next = *std::next(all.lower_bound(x));
    auto prev = *std::prev(all.lower_bound(x));
    res = sub(res, add(dis[prev], dis[x]));
    dis[prev] = calc(prev, next);
    all.erase(x);
    dis.erase(x);
    res = add(res, dis[prev]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> q;
    inv100 = inverse(100);
    for (auto i = 0; i < n; i++)
        std::cin >> p[i];
    prod[n] = 1;
    prod[n - 1] = mul(p[n - 1], inv100);
    sum[n - 1] = inverse(prod[n - 1]);
    for (auto i = n - 2; i >= 0; i--) {
        prod[i] = mul(prod[i + 1], mul(p[i], inv100));
        sum[i] = add(sum[i + 1], inverse(prod[i]));
    }

    check[1] = true;
    all.emplace(1);
    all.emplace(n + 1);
    res = dis[1] = calc(1, n + 1);
    for (auto i = 0; i < q; i++) {
        int x;
        std::cin >> x;
        if (check[x]) {
            check[x] = false;
            remove(x);
        } else {
            check[x] = true;
            add(x);
        }
        std::cout << res << "\n";
    }
}

