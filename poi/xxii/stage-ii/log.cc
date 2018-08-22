#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

using ll = long long;

auto constexpr maxn = 1000007;
ll a[maxn];
int n, m;
int len;

ll tree1[maxn * 4];
ll tree2[maxn * 4];

struct data
{
    char op;
    ll a, b;
};

std::vector<data> da;
std::vector<ll> dis;

ll lowbit(ll x)
{
    return x & -x;
}

void add(int p, ll delta, ll tree[])
{
    for (; p <= len; p += lowbit(p))
        tree[p] += delta;
}

int id(ll x)
{
    return std::lower_bound(std::begin(dis), std::end(dis), x) - std::begin(dis) + 1;
}

ll sum(int p, ll tree[])
{
    auto s = 0ll;
    for (; p > 0; p -= lowbit(p))
        s += tree[p];
    return s;
}

ll sum(int l, int r, ll tree[])
{
    return sum(r, tree) - sum(l-1, tree);
}

bool check(ll c, ll s)
{
    auto i = id(s);
    auto count = sum(i, len, tree1);
    if (count >= c)
        return true;
    auto rsum = sum(1, i-1, tree2);
    return rsum >= (c-count) * s;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    da.resize(m);
    for (auto i = 0; i < m; i++) {
        std::cin >> da[i].op >> da[i].a >> da[i].b;
        if (da[i].op == 'U')
            dis.emplace_back(da[i].b);
    }
    std::sort(std::begin(dis), std::end(dis));
    auto end = std::unique(std::begin(dis), std::end(dis));
    dis.erase(end, std::end(dis));
    len = dis.size();

    for (auto const& d : da) {
        if (d.op == 'U') {
            auto k = d.a;
            auto v = d.b;
            if (a[k]) {
                add(id(a[k]), -1,    tree1);
                add(id(a[k]), -a[k], tree2);
            }
            if (v) {
                add(id(v), +1, tree1);
                add(id(v), +v, tree2);
            }
            a[k] = v;
        } else {
            if (check(d.a, d.b))
                std::cout << "TAK\n";
            else
                std::cout << "NIE\n";
        }
    }
}

