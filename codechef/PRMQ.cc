// ml:run = time -p $bin < input
#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;

auto constexpr maxn = 100007;
auto constexpr maxa = 1000007;
int root[maxn];
int n, q;

bool not_prime[maxa];
std::vector<int> primes;

struct node
{
    int l;
    int r;
    int sum;
};

node pst[maxn * 200];
int alloc;

void init()
{
    primes.reserve(78499);
    for (ll i = 2; i < maxa; i++) {
        if (not_prime[i]) continue;
        primes.emplace_back(i);
        for (ll j = i * i; j < maxa; j += i)
            not_prime[j] = true;
    }
    // std::cerr << "tot primes: " << primes.size() << "\n";
}

auto get_lower(int x)
{
    return std::lower_bound(primes.begin(), primes.end(), x) - primes.begin() + 1;
}

auto get_upper(int x)
{
    return std::upper_bound(primes.begin(), primes.end(), x) - primes.begin();
}

void update(int& now, int pre, int pos, int delta, int l = 1, int r = primes.size())
{
    pst[now = ++alloc] = pst[pre];
    pst[now].sum += delta;

    if (l == r) return;
    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(pst[now].l, pst[pre].l, pos, delta, l, mid);
    else
        update(pst[now].r, pst[pre].r, pos, delta, mid + 1, r);
}

auto query(int now, int pre, int tl, int tr, int l = 1, int r = primes.size())
{
    if (tl > tr) return 0;
    if (tl <= l && r <= tr)
        return pst[now].sum - pst[pre].sum;

    auto mid = (l + r) / 2;
    auto sum = 0;
    if (tl <= mid)
        sum += query(pst[now].l, pst[pre].l, tl, tr, l, mid);
    if (mid < tr)
        sum += query(pst[now].r, pst[pre].r, tl, tr, mid + 1, r);

    return sum;
}

int main()
{
    std::ios::sync_with_stdio(false);
    init();
    std::cin >> n;
    for (auto i = 1; i <= n; i++) {
        int a; std::cin >> a;
        auto pre = root[i - 1];
        for (auto p = 2; p * p <= a; p++) {
            if (a % p) continue;
            auto count = 0;
            for (; !(a % p); count++)
                a /= p;

            update(root[i], pre, get_lower(p), count);

            pre = root[i];
        }
        if (a > 1)
            update(root[i], pre, get_lower(a), 1);
    }

    std::cin >> q;
    for (int l, r, x, y; q--; ) {
        std::cin >> l >> r >> x >> y;
        x = get_lower(x);
        y = get_upper(y);
        std::cout << query(root[r], root[l - 1], x, y) << "\n";
    }
}

