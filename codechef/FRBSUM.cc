// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <cstdio>
#include <utility>

auto constexpr maxn = 100007;
auto constexpr maxr = 1000000000;
int root [maxn];
int n, m;

struct node
{
    int l;
    int r;
    int count;
};

node tree[40 * maxn];
int alloc;

void update(int& now, int pre, int pos, int l = 1, int r = maxr)
{
    tree[now = ++alloc] = tree[pre];
    tree[now].count++;

    if (l == r) return;
    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(tree[now].l, tree[pre].l, pos, l, mid);
    else
        update(tree[now].r, tree[pre].r, pos, mid + 1, r);
}

auto get_kth(int now, int pre, int k, int l = 1, int r = maxr) -> std::pair<int, int>
{
    if (l == r)
        return {l, tree[now].count - tree[pre].count};
    auto mid = (l + r) / 2;
    auto left = tree[tree[now].l].count - tree[tree[pre].l].count;
    if (k <= left)
        return get_kth(tree[now].l, tree[pre].l, k, l, mid);
    else
        return get_kth(tree[now].r, tree[pre].r, k - left, mid + 1, r);
}

auto forbidden_sum(int l, int r) -> int
{
    auto sum = 0;
    for (auto i = 1; i <= r - l + 1; ) {
        auto kth = get_kth(root[r], root[l - 1], i);
        if (sum + 1 < kth.first)
            return sum + 1;
        sum += kth.first * kth.second;
        i += kth.second;
    }
    return sum + 1;
}

void read(int& x) { std::scanf("%d", &x); }
void write(int x) { std::printf("%d\n", x); }

int main()
{
    read(n);
    for (int i = 1, a; i <= n; i++) {
        read(a);
        update(root[i], root[i-1], a);
    }

    read(m);
    for (int l, r; m--; ) {
        read(l); read(r);
        write(forbidden_sum(l, r));
    }
}

