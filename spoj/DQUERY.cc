// ml:run = $bin < input
#include <iostream>

auto constexpr maxn = 30007;
auto constexpr maxa = 1000007;
int a[maxn];
int root[maxn];
int pre[maxa];
int n, q;

struct node
{
    int l;
    int r;
    int count;
};

node tree[40 * maxn];
int alloc;

void update(int& now, int pre, int pos, int delta, int l = 1, int r = n)
{
    now = ++alloc;
    tree[alloc] = tree[pre];
    tree[alloc].count += delta;

    if (l == r) return;
    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(tree[now].l, tree[pre].l, pos, delta, l, mid);
    else
        update(tree[now].r, tree[pre].r, pos, delta, mid + 1, r);
}

auto query(int now, int tl, int tr, int l = 1, int r = n) -> int
{
    if (tl <= l && r <= tr)
        return tree[now].count;
    auto mid = (l + r) / 2;
    auto sum = 0;
    if (tl <= mid)
        sum += query(tree[now].l, tl, tr, l, mid);
    if (tr > mid)
        sum += query(tree[now].r, tl, tr, mid + 1, r);
    return sum;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto i = 1; i <= n; i++) {
        std::cin >> a[i];
        update(root[i], root[i-1], i, 1);
        if (pre[a[i]])
            update(root[i], root[i], pre[a[i]], -1);
        pre[a[i]] = i;
    }

    std::cin >> q;
    for (int l, r; q--; ) {
        std::cin >> l >> r;
        std::cout << query(root[r], l, n) << "\n";
    }
}

