// ml:run = $bin < input
#include <iostream>
#include <unordered_map>
#include <vector>

using ll = long long;

std::vector<ll> a;
ll n, m;

template <class T>
T mod(T x, T mo) { return x < mo ? x : x % mo + mo; }

std::unordered_map<ll, ll> m_phi;

ll phi(ll x)
{
    if (m_phi.count(x)) return m_phi[x];
    ll tx = x;
    ll res = x;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i) continue;
        res = (res / i) * (i - 1);
        while (x % i == 0) x /= i;
    }
    if (x > 1) res = (res / x) * (x - 1);
    return m_phi[tx] = res;
}

ll quick(ll a, ll b, ll mo)
{
    ll res = 1;
    for (; b; b /= 2) {
        if (b & 1) res = mod(res * a, mo);
        a = mod(a * a, mo);
    }
    return res;
}

ll query(ll l, ll r, ll mo)
{
    if (l == r || mo == 1) return mod(a[l], mo);
    return quick(a[l], query(l + 1, r, phi(mo)), mo);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    a.resize(n + 1);
    for (int i = 1; i <= n; i++) std::cin >> a[i];

    int q; std::cin >> q;
    while (q--) {
        int l, r; std::cin >> l >> r;
        std::cout << query(l, r, m) % m << "\n";
    }
}

