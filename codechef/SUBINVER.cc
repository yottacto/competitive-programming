// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <algorithm>

using ll = long long;
auto constexpr maxn = 100007;
auto constexpr base = 100001ll;
auto constexpr mo = 2038072819ll;
int root[maxn];
int n, u;

ll pow[maxn];
ll full[maxn];

struct node
{
    int l;
    int r;
    bool tag;
    ll hash;
};

auto& operator<<(std::ostream& os, node const& n)
{
    os << "{ "
        << "l=" << n.l << ", "
        << "r=" << n.r << ", "
        << "tag=" << n.tag << ", "
        << "hash=" << n.hash;
    return os;
}

node tree[maxn * 40];
int alloc;

auto mul(ll x, ll y) { return (x * y) % mo; }
auto add(ll x, ll y) { return (x + y) % mo; }

void reverse_hash(ll& v, int len)
{
    v = (full[len] - v) % mo;
    v = (v + mo) % mo;
}

void alloc_lazy_child(int& now, int pre, int len)
{
    tree[now = ++alloc] = tree[pre];
    if (tree[now].tag) {
        tree[now].tag = false;
    } else {
        tree[now].tag = true;
        reverse_hash(tree[now].hash, len);
    }
}

void propagate(int now, int l, int r, int mid)
{
    auto& t = tree[now];
    if (!t.tag) return;
    alloc_lazy_child(t.l, t.l, mid - l + 1);
    alloc_lazy_child(t.r, t.r, r - mid);
    t.tag = false;
}

void merge(int now, int rlen)
{
    auto& t = tree[now];
    t.hash = add(
        mul(tree[t.l].hash, pow[rlen]),
        tree[t.r].hash
    );
}

void inverse(int& now, int pre, int tl, int tr, int l = 1, int r = n)
{
    if (!now) tree[now = ++alloc] = tree[pre];
    if (tl <= l && r <= tr) {
        auto& t = tree[now];
        t.tag ^= 1;
        reverse_hash(t.hash, r - l + 1);
        return;
    }
    auto mid = (l + r) / 2;
    propagate(now, l, r, mid);
    if (tl <= mid)
        inverse(tree[now].l, tree[pre].l, tl, tr, l, mid);
    if (tr > mid)
        inverse(tree[now].r, tree[pre].r, tl, tr, mid + 1, r);
    merge(now, r - mid);
}

auto cmp_impl(int pre, int now, int l = 1, int r = n) -> int
{
    if (pre == now) return 0;
    if (l == r) {
        if (!tree[pre].tag && tree[now].tag)
            return -1;
        else if (tree[pre].tag && !tree[now].tag)
            return +1;
        else
            return 0;
    }
    auto mid = (l + r) / 2;
    propagate(now, l, r, mid);
    propagate(pre, l, r, mid);
    if (tree[tree[pre].l].hash != tree[tree[now].l].hash)
        return cmp_impl(tree[pre].l, tree[now].l, l, mid);
    else
        return cmp_impl(tree[pre].r, tree[now].r, mid + 1, r);
}

auto cmp(int pre, int now)
{
    return cmp_impl(pre, now) < 0;
}

void print(int now, int l = 1, int r = n)
{
    // std::cerr << "[" << l << ", " << r << "] " << tree[now] << "\n";

    if (l == r) {
        std::cout << (
            tree[now].tag
            ? "1"
            : "0"
        );
        return;
    }
    auto mid = (l + r) / 2;

    propagate(now, l, r, mid);

    print(tree[now].l, l, mid);
    print(tree[now].r, mid + 1, r);
}

void build(int& now, int l = 1, int r = n)
{
    now = ++alloc;
    if (l == r) return;
    auto mid = (l + r) / 2;
    build(tree[now].l, l, mid);
    build(tree[now].r, mid + 1, r);
}

void init()
{
    pow[0] = 1;
    for (auto i = 1; i <= n; i++) {
        pow[i] = mul(pow[i-1], base);
        full[i] = add(full[i-1], pow[i-1]);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> u;
    init();
    build(root[0]);
    for (int l, r, i = 1; i <= u; i++) {
        std::cin >> l >> r;
        inverse(root[i], root[i - 1], l, r);
    }
    auto id = std::max_element(root + 1, root + u + 1, cmp) - root;
    print(root[id]); std::cout << "\n";

    std::cerr << "===========================================\n";
    std::cerr << "id=" << id << "\n";
    // std::cerr << cmp(root[2], root[3]) << "\n";
    print(root[1]); std::cerr << "\n";
    print(root[2]); std::cerr << "\n";
    print(root[3]); std::cerr << "\n";
    print(root[4]); std::cerr << "\n";
    print(root[5]); std::cerr << "\n";
    print(root[6]); std::cerr << "\n";
    print(root[7]); std::cerr << "\n";
    print(root[8]); std::cerr << "\n";
    print(root[9]); std::cerr << "\n";
    print(root[10]); std::cerr << "\n";

    // std::cerr << tree[root[2]].left_continuous[0] << "\n";
    // std::cerr << tree[root[2]].left_continuous[1] << "\n";
    // std::cerr << tree[tree[root[2]].r].left_continuous[0] << "\n";
    // std::cerr << tree[tree[root[2]].r].left_continuous[1] << "\n";

}

