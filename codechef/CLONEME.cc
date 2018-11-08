// ml:run = $bin < input
#include <iostream>
#include <algorithm>

using ll = long long;

auto constexpr base = 7777ll;
auto constexpr mo = 100000007ll;
auto constexpr maxn = 100007;
int root[maxn];
int n, q;

ll pow[maxn];

struct node
{
    int l;
    int r;
    ll hash;
};

node pst[maxn * 40];
int alloc;

template <class T>
auto abs(T x) { return x < 0 ? -x : x; }
auto add(ll x, ll y) { return (x + y) % mo; }
auto mul(ll x, ll y) { return (x * y) % mo; }
auto minus(ll x, ll y) { return (((x - y) % mo) + mo) % mo; }

void merge(int now, int rlen)
{
    auto& t = pst[now];
    t.hash = add(mul(pst[t.l].hash, pow[rlen]), pst[t.r].hash);
}

void update(int& now, int pre, int pos, int l = 1, int r = maxn)
{
    pst[now = ++alloc] = pst[pre];
    if (l == r) {
        pst[now].hash++;
        return;
    }
    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(pst[now].l, pst[pre].l, pos, l, mid);
    else
        update(pst[now].r, pst[pre].r, pos, mid + 1, r);
    merge(now, r - mid);
}

void init()
{
    pow[0] = 1;
    for (auto i = 1; i < maxn; i++)
        pow[i] = mul(pow[i - 1], base);

    alloc = 0;
}

auto get_hash(int now, int pre, int tl = 1, int tr = maxn, int l = 1, int r = maxn)
{
    if (tl > tr) return 0ll;
    if (tl <= l && r <= tr)
        return minus(pst[now].hash, pst[pre].hash);
    auto mid = (l + r) / 2;
    auto hl = 0ll;
    auto hr = 0ll;
    if (tl <= mid)
        hl = get_hash(pst[now].l, pst[pre].l, tl, std::min(tr, mid), l, mid);
    if (mid < tr)
        hr = get_hash(pst[now].r, pst[pre].r, std::max(tl, mid + 1), tr, mid + 1, r);
    if (tr <= mid)
        return hl;
    if (mid < tl)
        return hr;
    return add(mul(hl, pow[tr - mid]), hr);
}

auto same(int now1, int pre1, int now2, int pre2, int tl = 1, int tr = maxn, int l = 1, int r = maxn)
{
    if (tl > tr) return true;
    if (tl <= l && r <= tr) {
        return minus(pst[now1].hash, pst[pre1].hash)
            == minus(pst[now2].hash, pst[pre2].hash);
    }
    auto mid = (l + r) / 2;
    auto res = true;
    if (tl <= mid)
        res &= same(pst[now1].l, pst[pre1].l, pst[now2].l, pst[pre2].l, tl, tr, l, mid);
    if (mid < tr)
        res &= same(pst[now1].r, pst[pre1].r, pst[now2].r, pst[pre2].r, tl, tr, mid + 1, r);
    return res;
}

auto first_l_diff(int now1, int pre1, int now2, int pre2, int l = 1, int r = maxn) -> int
{
    if (l == r) return l;
    auto mid = (l + r) / 2;
    auto h1 = minus(pst[pst[now1].l].hash, pst[pst[pre1].l].hash);
    auto h2 = minus(pst[pst[now2].l].hash, pst[pst[pre2].l].hash);
    if (h1 != h2)
        return first_l_diff(pst[now1].l, pst[pre1].l, pst[now2].l, pst[pre2].l, l, mid);
    else
        return first_l_diff(pst[now1].r, pst[pre1].r, pst[now2].r, pst[pre2].r, mid + 1, r);
}

auto first_r_diff(int now1, int pre1, int now2, int pre2, int l = 1, int r = maxn) -> int
{
    if (l == r) return l;
    auto mid = (l + r) / 2;
    auto h1 = minus(pst[pst[now1].r].hash, pst[pst[pre1].r].hash);
    auto h2 = minus(pst[pst[now2].r].hash, pst[pst[pre2].r].hash);
    if (h1 != h2)
        return first_r_diff(pst[now1].r, pst[pre1].r, pst[now2].r, pst[pre2].r, mid + 1, r);
    else
        return first_r_diff(pst[now1].l, pst[pre1].l, pst[now2].l, pst[pre2].l, l, mid);
}

auto plus_or_minus_one(int now1, int pre1, int now2, int pre2, int pos, int l = 1, int r = maxn) -> bool
{
    if (l == r) {
        auto v1 = pst[now1].hash - pst[pre1].hash;
        auto v2 = pst[now2].hash - pst[pre2].hash;
        return abs(v1 - v2) == 1;
    }
    auto mid = (l + r) / 2;
    if (pos <= mid)
        return plus_or_minus_one(pst[now1].l, pst[pre1].l, pst[now2].l, pst[pre2].l, pos, l, mid);
    else
        return plus_or_minus_one(pst[now1].r, pst[pre1].r, pst[now2].r, pst[pre2].r, pos, mid + 1, r);
}

auto check(int l1, int r1, int l2, int r2)
{
    if (same(root[r1], root[l1-1], root[r2], root[l2-1]))
        return true;

    auto l = first_l_diff(root[r1], root[l1-1], root[r2], root[l2-1]);
    auto r = first_r_diff(root[r1], root[l1-1], root[r2], root[l2-1]);


    if (!same(root[r1], root[l1-1], root[r2], root[l2-1], 1, l - 1)
        || !same(root[r1], root[l1-1], root[r2], root[l2-1], r + 1, maxn)
    )
        return false;

    // std::cerr << l << " " << r << "\n";
    // std::cerr << same(root[r1], root[l1-1], root[r2], root[l2-1], l + 1, r - 1) << "\n";
    // std::cerr << get_hash(root[r1], root[l1-1], l + 1, r - 1) << "\n";
    // std::cerr << get_hash(root[r2], root[l2-1], l + 1, r - 1) << "\n";

    if (!(same(root[r1], root[l1-1], root[r2], root[l2-1], l + 1, r - 1)
        && !get_hash(root[r1], root[l1-1], l + 1, r - 1))
    )
        return false;

    return plus_or_minus_one(root[r1], root[l1-1], root[r2], root[l2-1], l)
        && plus_or_minus_one(root[r1], root[l1-1], root[r2], root[l2-1], r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T; std::cin >> T;
    while (T--) {
        std::cin >> n >> q;
        init();
        for (auto i = 1; i <= n; i++) {
            int a; std::cin >> a;
            update(root[i], root[i - 1], a);
        }

        for (int l1, r1, l2, r2; q--; ) {
            std::cin >> l1 >> r1 >> l2 >> r2;
            std::cout << (check(l1, r1, l2, r2) ? "YES" : "NO") << "\n";
        }
    }
}

