// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

#define DEBUG 0

using ll = long long;

auto constexpr maxn = 2000;
auto constexpr inf  = 1ll << 50;

struct node
{
    bool none;
    ll sum;
    ll max; ll lmax; ll rmax;
    int l;
    int r;
    int lmax_r;
    int rmax_l;
};

node tree[maxn * 6];
int n;
int tot;

struct data
{
    ll x;
    ll y;
    ll value;
};

std::vector<data> a;

void build(int id, int l, int r)
{
    tree[id].none = true;
    if (l == r) return;
    auto mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
}

void push_up(int id)
{
    auto& t  = tree[id];
    auto& tl = tree[id * 2];
    auto& tr = tree[id * 2 + 1];
    auto sl = tl.none;
    auto sr = tr.none;
    if (sl && sr)
        return;
    if (sl ^ sr) {
        t.none = false;
        if (!sl) {
            t.sum    = tl.sum;
            t.max    = tl.max;
            t.lmax   = tl.lmax;
            t.lmax_r = tl.lmax_r;
            t.rmax   = -inf;
            t.l      = tl.l;
            t.r      = tl.r;
        } else {
            t.sum    = tr.sum;
            t.max    = tr.max;
            t.lmax   = -inf;
            t.rmax   = tr.rmax;
            t.rmax_l = tr.rmax_l;
            t.l      = tr.l;
            t.r      = tr.r;
        }
        return;
    }

    t.none = false;
    t.sum = tl.sum + tr.sum;
    t.lmax = tl.lmax;
    t.lmax_r = tl.lmax_r;
    if (tl.lmax == tl.sum)
        if (tl.sum + tr.lmax > t.lmax) {
            t.lmax = tl.sum + tr.lmax;
            t.lmax_r = tr.lmax_r;
        }

    t.rmax = tr.rmax;
    t.rmax_l = tr.rmax_l;
    if (tr.rmax == tr.sum)
        if (tr.sum + tl.rmax > t.rmax) {
            t.rmax = tr.sum + tl.rmax;
            t.rmax_l = tl.rmax_l;
        }

    t.max = tl.max;
    t.l = tl.l;
    t.r = tl.r;
    if (tr.max > t.max) {
        t.max = tr.max;
        t.l = tr.l;
        t.r = tr.r;
    }
    if (tl.rmax + tr.lmax > t.max) {
        t.max = tl.rmax + tr.lmax;
        t.l = tl.rmax_l;
        t.r = tr.lmax_r;
    }
}

// struct node { bool none; ll sum; ll max; ll lmax; ll rmax; int l; int r; };

void update(int id, int l, int r, int p, ll delta)
{
    if (l == r && l == p) {
        auto& t = tree[id];
        if (t.none) {
            t.none = false;
            t.sum = 0;
        }
        t.sum += delta;
        t.max = t.lmax = t.rmax = t.sum;
        t.l = t.r = t.lmax_r = t.rmax_l = p;
        return;
    }
    auto mid = (l + r) / 2;
    if (p <= mid)
        update(id * 2,     l,       mid, p, delta);
    else
        update(id * 2 + 1, mid + 1, r,   p, delta);

    push_up(id);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    a.resize(n);
    std::vector<ll> disc;
    for (auto& i : a) {
        std::cin >> i.x >> i.y >> i.value;
        disc.emplace_back(i.y);
    }
    std::sort(std::begin(disc), std::end(disc));
    auto last = std::unique(std::begin(disc), std::end(disc));
    disc.erase(last, std::end(disc));

    tot = disc.size();
    for (auto& i : a)
        i.y = std::lower_bound(std::begin(disc), std::end(disc), i.y) - std::begin(disc) + 1;

    std::sort(std::begin(a), std::end(a), [](data const& lhs, data const& rhs) {
        return lhs.x < rhs.x
            || (lhs.x == rhs.x && lhs.y < rhs.y);
    });

    auto single_max = -inf;
    std::for_each(std::begin(a), std::end(a), [&](data const& x) {
        single_max = std::max(single_max, x.value);
    });

    auto ans = -inf;
    int xl, xr;
    int yl, yr;

    for (auto i = 0; i < n; i++) {
        build(1, 1, tot);
        for (auto j = i; j < n; j++) {
            update(1, 1, tot, a[j].y, a[j].value);
            for (j++; j < n && a[j].y == a[j - 1].y; j++)
                update(1, 1, tot, a[j].y, a[j].value);
            j--;

            if (tree[1].max > ans) {
                ans = tree[1].max;
                xl = a[i].x;
                xr = a[j].x;
                yl = disc[tree[1].l - 1];
                yr = disc[tree[1].r - 1];
            }

            #if DEBUG
            if (i == 2) {
                std::cerr << j << " " << tree[1].max << "\n";
            }
            #endif
        }
    }

    if (ans == single_max) {
        ans = -inf;
        for (auto i = 0; i < n; i++) {
            auto ymax = -inf;
            auto ymin = +inf;
            for (auto j = i + 1; j < n; j++) {
                if (a[j].y >= a[i].y) {
                    if (ymin > a[j].y && a[j].value + a[i].value > ans) {
                        ans = a[j].value + a[i].value;
                        xl = a[i].x;
                        xr = a[j].x;
                        yl = disc[a[i].y - 1];
                        yr = disc[a[j].y - 1];
                    }
                    ymin = std::min(ymin, a[j].y);
                }
                if (a[j].y <= a[i].y) {
                    if (ymax < a[j].y && a[j].value + a[i].value > ans) {
                        ans = a[j].value + a[i].value;
                        xl = a[i].x;
                        xr = a[j].x;
                        yl = disc[a[j].y - 1];
                        yr = disc[a[i].y - 1];
                    }
                    ymax = std::max(ymax, a[j].y);
                }
            }
        }
    }

    #if DEBUG
    for (auto const& i : a)
        std::cerr << i.y << " ";
    std::cerr << "\n";
    std::cerr << ans << "\n";
    #endif

    std::cout << xl << " " << xr << "\n";
    std::cout << yl << " " << yr << "\n";
}

