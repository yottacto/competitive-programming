// ml:run = $bin < input
#include <cstdio>

auto constexpr maxn = 500007;
auto constexpr maxl = 19;

int root[maxn];
int n, m;

struct node
{
    int l;
    int r;
    int count;
};

node tree[40 * maxn];
int alloc;

void update(int& now, int pre, int x, int depth = maxl)
{
    tree[now = ++alloc] = tree[pre];
    tree[now].count++;

    if (!depth) return;

    auto bit = (x >> (depth - 1)) & 1;
    if (bit)
        update(tree[now].r, tree[pre].r, x, depth - 1);
    else
        update(tree[now].l, tree[pre].l, x, depth - 1);
}

auto query_max(int now, int pre, int x, int depth = maxl) -> int
{
    if (!depth) return 0;

    auto bit = (x >> (depth - 1)) & 1;
    auto left = tree[tree[now].l].count - tree[tree[pre].l].count;
    auto right = tree[tree[now].r].count - tree[tree[pre].r].count;
    if (bit) {
        if (left)
            return query_max(tree[now].l, tree[pre].l, x, depth - 1);
        else
            return (1<<(depth-1)) | query_max(tree[now].r, tree[pre].r, x, depth - 1);
    } else {
        if (right)
            return (1<<(depth-1)) | query_max(tree[now].r, tree[pre].r, x, depth - 1);
        else
            return query_max(tree[now].l, tree[pre].l, x, depth - 1);
    }
}

auto query_le(int now, int pre, int x, int depth = maxl) -> int
{
    if (!depth) return tree[now].count - tree[pre].count;

    auto bit = (x >> (depth - 1)) & 1;
    auto left = tree[tree[now].l].count - tree[tree[pre].l].count;
    auto right = tree[tree[now].r].count - tree[tree[pre].r].count;

    if (bit)
        return left +
            (right
                ? query_le(tree[now].r, tree[pre].r, x, depth - 1)
                : 0);
    else
        return (left
                ? query_le(tree[now].l, tree[pre].l, x, depth - 1)
                : 0);
}

auto query_kth(int now, int pre, int k, int depth = maxl) -> int
{
    auto left = tree[tree[now].l].count - tree[tree[pre].l].count;

    if (!depth) return 0;

    if (k <= left)
        return query_kth(tree[now].l, tree[pre].l, k, depth - 1);
    else
        return (1<<(depth-1)) | query_kth(tree[now].r, tree[pre].r, k-left, depth-1);
}

void read(int& x) { std::scanf("%d", &x); }
void write(int x) { std::printf("%d\n", x); }

int main()
{
    read(m);
    for (int opt, l, r, x, k; m--; ) {
        read(opt);
        if (opt == 0) {
            read(x);
            n++;
            update(root[n], root[n - 1], x);
        } else if (opt == 1) {
            read(l); read(r); read(x);
            write(query_max(root[r], root[l - 1], x));
        } else if (opt == 2) {
            read(k);
            n -= k;
            // memeory reuse
            alloc = root[n + 1];
        } else if (opt == 3) {
            read(l); read(r); read(x);
            write(query_le(root[r], root[l - 1], x));
        } else if (opt == 4) {
            read(l); read(r); read(k);
            write(query_kth(root[r], root[l - 1], k));
        }
    }
}

