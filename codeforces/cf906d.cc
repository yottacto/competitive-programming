// ml:run = $bin < input
#include <iostream>
#include <unordered_map>
#include <vector>

using ll = long long;
ll n, m;
std::unordered_map<ll, ll> phi;
std::vector<ll> a;

template <class T>
T mod(T x, T m) { return x < m ? x : x % m + m; }

ll quick(ll a, ll b, ll m)
{

    // if (b == 0) return 1;
    // auto ret = quick(a, b/2, m);
    // ret = mod(ret * ret, m);
    // if (ret > m) ret = ret % m + m;
    // if (b & 1) ret = mod(ret * a, m);
    // return ret;

    auto res = 1ll;
    for (; b; b /= 2) {
        if (b & 1) res = mod(res * a, m);
        a = mod(a * a, m);
    }
    return res;
}

ll calc_phi(ll m)
{
    if (phi.count(m)) return phi[m];
    auto ret = 1ll;
    auto tm = m;
    for (auto i = 2ll; i * i <= m; i++) {
        if (m % i) continue;
        auto prod = 1ll;
        for (; (m % i) == 0; m /= i)
            prod *= i;
        ret *= (prod / i) * (i - 1);
    }
    if (m > 1) ret *= m - 1;
    return phi[tm] = ret;
}

ll query(int l, int r, ll m)
{
    if (l == r || m == 1) return a[l] < m ? a[l] : a[l] % m + m;
    return quick(a[l], query(l + 1, r, calc_phi(m)), m);
}

int main()
{
    std::ios::sync_with_stdio(false);

    std::cin >> n >> m;
    a.resize(n);
    for (auto i = 0; i < n; i++)
        std::cin >> a[i];

    int q;
    std::cin >> q;
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << query(--l, --r, m) % m << "\n";
    }
}

