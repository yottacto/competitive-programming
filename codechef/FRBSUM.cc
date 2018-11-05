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
    int sum;
};

node tree[40 * maxn];
int alloc;

void update(int& now, int pre, int pos, int l = 1, int r = maxr)
{
    tree[now = ++alloc] = tree[pre];
    tree[now].sum += pos;

    if (l == r) return;
    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(tree[now].l, tree[pre].l, pos, l, mid);
    else
        update(tree[now].r, tree[pre].r, pos, mid + 1, r);
}

auto get_sum(int now, int pre, int tl, int tr, int l = 1, int r = maxr) -> int
{
    if (tl <= l && r <= tr)
        return tree[now].sum - tree[pre].sum;
    auto mid = (l + r) / 2;
    auto sum = 0;
    if (tl <= mid)
        sum += get_sum(tree[now].l, tree[pre].l, tl, tr, l, mid);
    if (mid < tr)
        sum += get_sum(tree[now].r, tree[pre].r, tl, tr, mid + 1, r);
    return sum;
}

auto forbidden_sum(int l, int r) -> int
{
    auto sum = 0;
    for (int tsum; ; sum = tsum) {
        tsum = get_sum(root[r], root[l - 1], 1, sum + 1);
        if (tsum == sum)
            break;
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

