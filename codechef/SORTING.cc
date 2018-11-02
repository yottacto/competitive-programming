// ml:run = $bin < input
#include <iostream>

using ll = long long;

auto constexpr maxn = 500007;
int a[maxn];
int index[maxn];
int root[maxn];
int n;

struct node
{
    int l;
    int r;
    int count;
};

node tree[40 * maxn];
int alloc;

void update(int& now, int pre, int pos, int l = 1, int r = n)
{
    now = ++alloc;
    tree[alloc] = tree[pre];
    tree[alloc].count++;

    if (l == r) return;

    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(tree[now].l, tree[pre].l, pos, l, mid);
    else
        update(tree[now].r, tree[pre].r, pos, mid + 1, r);
}

auto get(int now, int pre, int k, int l = 1, int r = n) -> int
{
    auto count = tree[tree[now].l].count - tree[tree[pre].l].count;
    // std::cerr << ":: l=" << l << ", r=" << r << " count=" << count << " " << k << "\n";
    auto mid = (l + r) / 2;
    if (l == r) return l;
    if (count >= k)
        return get(tree[now].l, tree[pre].l, k, l, mid);
    else
        return get(tree[now].r, tree[pre].r, k - count,  mid + 1, r);
}

auto qsort(int l, int r) -> ll
{
    if (l >= r) return 0;
    auto tot = tree[root[r]].count - tree[root[l-1]].count;
    if (tot == 1) return 0;
    auto mid = a[get(root[r], root[l-1], (tot+1)/2)];
    // std::cerr << "qsort [" << l << ", " << mid << ", " << r << "] : tot=" << tot << ", index=" << get(root[r], root[l-1], (tot+1)/2) << "\n";
    return tot + qsort(l, mid - 1) + qsort(mid + 1, r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto i = 1; i <= n; i++) {
        std::cin >> a[i];
        index[a[i]] = i;
    }
    for (auto i = 1; i <= n; i++)
        update(root[i], root[i - 1], index[i]);
    // std::cerr << get(root[7], root[3], 2) << "\n";
    std::cout << qsort(1, n) << "\n";
}

