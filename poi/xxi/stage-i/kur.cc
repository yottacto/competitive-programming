// ml:run = $bin < input
#include <cstdio>
#include <algorithm>

auto constexpr maxn = 500007;

struct node
{
    int left;
    int right;
    int count;
    int max;
};

int root[maxn];
node t[40 * maxn];
int alloc;
int n;
int m;

void update(int pre, int& now, int p, int l = 1, int r = n)
{
    now = ++alloc;
    t[now] = t[pre];
    t[now].count++;
    if (l == r) {
        t[now].max = t[now].count;
        return;
    }
    auto mid = (l + r) / 2;
    if (p <= mid)
        update(t[pre].left, t[now].left, p, l, mid);
    else
        update(t[pre].right, t[now].right, p, mid + 1, r);
    t[now].max = std::max(t[t[now].left].max, t[t[now].right].max);
}

auto query(int pre, int now, int len, int l = 1, int r = n) -> int
{
    if (l == r) {
        auto count = t[now].count - t[pre].count;
        if (count <= len / 2)
            return 0;
        else
            return l;
    }
    auto mid = (l + r) / 2;
    auto lcount = t[t[now].left].count  - t[t[pre].left].count;
    auto rcount = t[t[now].right].count - t[t[pre].right].count;
    if (lcount > rcount)
        return query(t[pre].left, t[now].left, len, l, mid);
    else
        return query(t[pre].right, t[now].right, len, mid + 1, r);
}

int main()
{
    std::scanf("%d%d", &n, &m);
    for (auto i = 1; i <= n; i++) {
        int tmp;
        std::scanf("%d", &tmp);
        update(root[i - 1], root[i], tmp);
    }
    for (auto i = 0; i < m; i++) {
        int l, r;
        std::scanf("%d%d", &l, &r);
        std::printf("%d\n", query(root[l - 1], root[r], r - l + 1));
    }

}

