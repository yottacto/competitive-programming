// ml:run = $bin < input
#include <iostream>

auto constexpr maxn = 30007;
auto constexpr maxa = 1'000'000'000;
int a[maxn];
int root[maxn];
int n, q;
int last_ans;

struct node
{
    int l;
    int r;
    int count;
};

node tree[40 * maxn];
int alloc;

void update(int pre, int& now, int pos, int l = 1, int r = maxa)
{
    now = ++alloc;
    tree[alloc] = tree[pre];
    tree[alloc].count++;

    if (l == r)
        return;

    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(tree[pre].l, tree[now].l, pos, l, mid);
    else
        update(tree[pre].r, tree[now].r, pos, mid + 1, r);
}

auto query(int now, int pre, int k, int l = 1, int r = maxa) -> int
{
    if (k <= l)
        return tree[now].count - tree[pre].count;
    if (!now && !pre) return 0;
    auto mid = (l + r) / 2;
    auto sum = 0;
    if (k <= mid)
        sum += query(tree[now].l, tree[pre].l, k, l, mid);
    sum += query(tree[now].r, tree[pre].r, k, mid + 1, r);
    return sum;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto i = 1; i <= n; i++) {
        std::cin >> a[i];
        update(root[i - 1], root[i], a[i]);
    }
    std::cin >> q;
    while (q--) {
        int a, b, c;
        std::cin >> a >> b >> c;
        auto i = a ^ last_ans;
        auto j = b ^ last_ans;
        auto k = c ^ last_ans;
        if (i < 1) i = 1;
        if (j > n) j = n;
        if (i > j)
            last_ans = 0;
        else
            last_ans = query(root[j], root[i - 1], k + 1);
        std::cout << last_ans << "\n";
    }
}

