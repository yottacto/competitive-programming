// ml:run = $bin < input
#include <iostream>

auto constexpr maxn = 100007;
int a[maxn];
int root[maxn];
int prev[maxn];
int n;

struct node
{
    int l;
    int r;
    int count;
};

node tree[maxn * 40];
int alloc;

void update(int& now, int prev, int pos, int delta, int l = 1, int r = n)
{
    tree[now = ++alloc] = tree[prev];
    tree[now].count += delta;

    if (l == r)
        return;
    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(tree[now].l, tree[prev].l, pos, delta, l, mid);
    else
        update(tree[now].r, tree[prev].r, pos, delta, mid + 1, r);
}

auto kth(int now, int k, int l = 1, int r = n)
{
    if (k > tree[now].count)
        return n + 1;
    if (l == r) return l;

    auto left = tree[tree[now].l].count;
    auto mid = (l + r) / 2;
    if (k <= left)
        return kth(tree[now].l, k, l, mid);
    else
        return kth(tree[now].r, k - left, mid + 1, r);
}

auto min_squads(int k)
{
    auto count = 0;
    for (auto l = 1; l <= n; count++)
        l = kth(root[l], k + 1);
    return count;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto i = 1; i <= n; i++)
        std::cin >> a[i];

    for (auto i = n; i >= 1; i--) {
        update(root[i], root[i + 1], i, 1);
        if (prev[a[i]])
            update(root[i], root[i], prev[a[i]], -1);
        prev[a[i]] = i;
    }

    for (auto k = 1; k <= n; k++)
        std::cout << min_squads(k) << " ";
    std::cout << "\n";
}

