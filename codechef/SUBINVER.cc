// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <algorithm>

auto constexpr maxn = 100007;
int root[maxn];
int n, u;

struct node
{
    int l;
    int r;
    bool tag;
    int left_continuous[2];
};

auto& operator<<(std::ostream& os, node const& n)
{
    os << "{ "
        << "l=" << n.l << ", "
        << "r=" << n.r << ", "
        << "tag=" << n.tag << ", "
        << "lc[0]=" << n.left_continuous[0] << ", "
        << "lc[0]=" << n.left_continuous[1] << " }";
    return os;
}

node tree[maxn * 40];
int alloc;

void alloc_lazy_child(int& now, int pre)
{
    tree[now = ++alloc] = tree[pre];
    if (tree[now].tag) {
        tree[now].tag = false;
    } else {
        tree[now].tag = true;
        std::swap(tree[now].left_continuous[0], tree[now].left_continuous[1]);
    }
}

void propagate(int now)
{
    auto& t = tree[now];
    if (!t.tag) return;
    alloc_lazy_child(t.l, t.l);
    alloc_lazy_child(t.r, t.r);
    t.tag = false;
}

void merge(int now, int llen)
{
    auto& t = tree[now];
    for (auto i = 0; i < 2; i++) {
        t.left_continuous[i] = tree[t.l].left_continuous[i];
        if (t.left_continuous[i] == llen)
            t.left_continuous[i] += tree[t.r].left_continuous[i];
    }
}

void inverse(int& now, int pre, int tl, int tr, int l = 1, int r = n)
{
    tree[now = ++alloc] = tree[pre];
    if (tl <= l && r <= tr) {
        auto& t = tree[now];
        t.tag = true;
        std::swap(t.left_continuous[0], t.left_continuous[1]);
        return;
    }
    auto mid = (l + r) / 2;
    propagate(now);
    if (tl <= mid)
        inverse(tree[now].l, tree[pre].l, tl, tr, l, mid);
    if (tr > mid)
        inverse(tree[now].r, tree[pre].r, tl, tr, mid + 1, r);
    merge(now, mid - l + 1);
}

auto cmp_impl(int pre, int now, int l = 1, int r = n) -> int
{
    if (pre == now) return 0;
    auto pre_lc1 = tree[pre].left_continuous[1];
    auto now_lc1 = tree[now].left_continuous[1];
    if (pre_lc1 < now_lc1)
        return -1;
    else if (pre_lc1 > now_lc1)
        return 1;
    else {
        auto pre_lc0 = tree[pre].left_continuous[0];
        auto now_lc0 = tree[now].left_continuous[0];
        if (pre_lc0 > now_lc0)
            return -1;
        else if (pre_lc0 < now_lc0)
            return 1;
    }
    if (l == r)
        return 0;
    propagate(now);
    propagate(pre);
    auto mid = (l + r) / 2;
    auto cmp_l = cmp_impl(tree[pre].l, tree[now].l, l, mid);
    if (cmp_l) return cmp_l;
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
            tree[now].left_continuous[1]
            ? "1"
            : "0"
        );
        return;
    }
    propagate(now);
    auto mid = (l + r) / 2;
    print(tree[now].l, l, mid);
    print(tree[now].r, mid + 1, r);
}

void build(int& now, int l = 1, int r = n)
{
    now = ++alloc;
    tree[now].left_continuous[0] = r - l + 1;
    if (l == r) return;
    auto mid = (l + r) / 2;
    build(tree[now].l, l, mid);
    build(tree[now].r, mid + 1, r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> u;
    build(root[0]);
    // tree[0].left_continuous[0] = n;
    for (int l, r, i = 1; i <= u; i++) {
        std::cin >> l >> r;
        inverse(root[i], root[i - 1], l, r);
    }
    auto id = std::max_element(root + 1, root + u + 1, cmp) - root;
    print(root[id]); std::cout << "\n";

    std::cerr << cmp(root[2], root[3]) << "\n";

    std::cerr << "===========================================\n";
    std::cerr << "id=" << id << "\n";
    print(root[1]); std::cerr << "\n";
    print(root[2]); std::cerr << "\n";
    print(root[3]); std::cerr << "\n";

    // std::cerr << tree[root[2]].left_continuous[0] << "\n";
    // std::cerr << tree[root[2]].left_continuous[1] << "\n";
    // std::cerr << tree[tree[root[2]].r].left_continuous[0] << "\n";
    // std::cerr << tree[tree[root[2]].r].left_continuous[1] << "\n";

}

