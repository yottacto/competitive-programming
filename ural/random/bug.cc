// ml:run = cp $bin bug
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>

using ll = long long;

struct query
{
    ll t;
    ll x, y;
    bool save;
};

std::vector<query> queries;
std::vector<ll> disc;
int n, p;
int tot;

auto constexpr maxn = 40000000;

struct node
{
    double a0;
    double d;
    double sum;
    bool clear;
};

node tree[maxn];

auto sum_ap(double a0, double d, ll n)
{
    return (2 * a0 + (n - 1) * d) * n / 2.;
}

void push_up(int id)
{
    tree[id].sum = tree[id * 2].sum + tree[id * 2 + 1].sum;
}

void push_down_clear(int id)
{
    tree[id * 2].clear = tree[id * 2 + 1].clear = true;
    tree[id].a0         = tree[id].d         = tree[id].sum         = 0;
    tree[id * 2].a0     = tree[id * 2].d     = tree[id * 2].sum     = 0;
    tree[id * 2 + 1].a0 = tree[id * 2 + 1].d = tree[id * 2 + 1].sum = 0;
    tree[id].clear = false;
}

void push_down(int id, int l, int r)
{
    if (tree[id].clear) {
        tree[id * 2].clear = tree[id * 2 + 1].clear = true;
        tree[id].a0         = tree[id].d         = tree[id].sum         = 0;
        tree[id * 2].a0     = tree[id * 2].d     = tree[id * 2].sum     = 0;
        tree[id * 2 + 1].a0 = tree[id * 2 + 1].d = tree[id * 2 + 1].sum = 0;
        tree[id].clear = false;
        return;
    }
    if (tree[id * 2].clear)
        push_down_clear(id * 2);
    if (tree[id * 2 + 1].clear)
        push_down_clear(id * 2 + 1);

    auto mid = (l + r) / 2;
    auto& a0 = tree[id].a0;
    auto& d = tree[id].d;
    tree[id * 2].a0 += a0;
    tree[id * 2].d += d;
    tree[id * 2].sum += sum_ap(a0, d, disc[mid + 1] - disc[l]);
    tree[id * 2 + 1].a0 += a0 + (disc[mid + 1] - disc[l]) * d;
    tree[id * 2 + 1].d += d;
    tree[id * 2 + 1].sum += sum_ap(a0 + (disc[mid + 1] - disc[l]) * d, d, disc[r + 1] - disc[mid + 1]);
    a0 = d = 0;
}

void update(int id, int l, int r, int tl, int tr, double a0, double d)
{
    if (l != r)
        push_down(id, l, r);
    if (tl <= l && r <= tr) {
        if (tree[id].clear) {
            tree[id].a0 = tree[id].d = tree[id].sum = 0;
            tree[id].clear = false;
        }
        tree[id].a0 += a0;
        tree[id].d += d;
        tree[id].sum += sum_ap(a0, d, disc[r + 1] - disc[l]);
        return;
    }
    // push_down(id, l, r);
    auto mid = (l + r) / 2;
    if (tl <= mid)
        update(id * 2, l, mid, tl, tr, a0, d);
    if (tr > mid) {
        if (tl > mid)
            update(id * 2 + 1, mid + 1, r, tl, tr, a0, d);
        else
            update(id * 2 + 1, mid + 1, r, mid+1, tr, a0 + (disc[mid + 1] - disc[tl]) * d, d);
    }
    push_up(id);
}

auto sum(int id, int l, int r, int tl, int tr)
{
    if (tl <= l && r <= tr) {
        if (tree[id].clear)
            return 0.;
        return tree[id].sum;
    }
    push_down(id, l, r);
    auto mid = (l + r) / 2;
    auto ret = 0.;
    if (tl <= mid)
        ret += sum(id * 2, l, mid, tl, tr);
    if (tr > mid)
        ret += sum(id * 2 + 1, mid + 1, r, tl, tr);

    // TODO can remove?
    // push_up(id);
    return ret;
}

void clear(int id, int l, int r, int tl, int tr)
{
    if (tl <= l && r <= tr) {
        tree[id].clear = true;
        tree[id].a0 = tree[id].d = tree[id].sum = 0;
        return;
    }
    push_down(id, l, r);
    auto mid = (l + r) / 2;
    if (tl <= mid)
        clear(id * 2, l, mid, tl, tr);
    if (tr > mid)
        clear(id * 2 + 1, mid + 1, r, tl, tr);
    push_up(id);
}

auto bin_search(ll x)
{
    using std::begin;
    using std::end;
    return std::lower_bound(begin(disc), end(disc), x) - begin(disc);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> p;
    int q;
    std::cin >> q;
    queries.resize(q);
    disc.reserve(500100);
    disc.emplace_back(0);
    disc.emplace_back(1);
    disc.emplace_back(n);
    disc.emplace_back(n + 1);
    for (auto& i : queries) {
        std::string s;
        std::cin >> i.t >> s >> i.x >> i.y;
        i.save = (s == "save");

        if (s == "save") {
            disc.emplace_back(i.x);
            disc.emplace_back(i.y);
            disc.emplace_back(i.y + 1);
        } else {
            auto pi = i.x;
            auto d = i.y;
            disc.emplace_back(pi - d + 1);
            disc.emplace_back(pi - 1);
            disc.emplace_back(pi);
            disc.emplace_back(pi + d - 1);
            disc.emplace_back(pi + d);
        }
    }

    std::sort(std::begin(disc), std::end(disc));
    auto last = std::unique(std::begin(disc), std::end(disc));
    disc.erase(last, std::end(disc));
    tot = disc.size() - 2;

    // for (auto i : disc)
    //     std::cerr << i << " ";
    // std::cerr << "\n";

    auto last_time = 0ll;
    auto saved = 0.;
    for (auto const& q : queries) {
        auto t = q.t;
        update(1, 1, tot, 1, tot, (t - last_time) * p, 0);
        if (q.save) {
            auto l = bin_search(q.x);
            auto r = bin_search(q.y);
            saved += sum(1, 1, tot, l, r);
            std::cout << std::fixed << std::setprecision(10)
                << saved << "\n";
            clear(1, 1, tot, l, r);
        } else {
            auto i = q.x;
            auto d = q.y;
            auto x = saved / (d * d);
            saved = 0;

            // std::cerr << "enforece " << i << " " << d << " " << x << "\n";

            {
                auto l = bin_search(i - d + 1);
                auto r = bin_search(i - 1);
                if (l <= r)
                    update(1, 1, tot, l, r, x, +x);
            }
            {
                auto l = bin_search(i);
                auto r = bin_search(i + d - 1);
                update(1, 1, tot, l, r, x * d, -x);
            }
        }
        last_time = t;
    }
}

