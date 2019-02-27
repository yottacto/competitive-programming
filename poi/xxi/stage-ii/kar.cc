// ml:run = cp $bin random/kar
// ml:run = $bin < input
#include <cstdio>
#include <algorithm>

auto constexpr maxn = 200007;

// actually, this flag can be optimized to the right value directly

// flag[0][]: interval start (left) with small value
// flag[1][]: interval start (left) with big value
// flag[][] = 0: can't make the seq to the right
// flag[][] = 1: seq end (right side) with small value
// flag[][] = 2: seq end (right side) with big value
int flag[2][8 * maxn];

int big[maxn];
int small[maxn];
int n, m;

void combine(int id, int l, int r)
{
    auto mid = (l + r) / 2;
    for (auto i = 0; i < 2; i++) {
        if (!flag[i][id * 2]) {
            flag[i][id] = 0;
        } else if (flag[i][id * 2] == 1) {
            if (small[mid + 1] >= small[mid])
                flag[i][id] = flag[0][id * 2 + 1];
            else if (big[mid + 1] >= small[mid])
                flag[i][id] = flag[1][id * 2 + 1];
            else
                flag[i][id] = 0;
        } else {
            if (small[mid + 1] >= big[mid])
                flag[i][id] = flag[0][id * 2 + 1];
            else if (big[mid + 1] >= big[mid])
                flag[i][id] = flag[1][id * 2 + 1];
            else
                flag[i][id] = 0;
        }
    }
}

void build_tree(int id, int l, int r)
{
    if (l == r) {
        flag[0][id] = 1;
        flag[1][id] = 2;
        return;
    }
    auto mid = (l + r) / 2;
    build_tree(id * 2, l, mid);
    build_tree(id * 2 + 1, mid + 1, r);
    combine(id, l, r);
}

void update(int id, int l, int r, int p, int small_v, int big_v)
{
    if (l == r) {
        small[p] = small_v;
        big[p] = big_v;
        return;
    }
    auto mid = (l + r) / 2;
    if (p <= mid)
        update(id * 2, l, mid, p, small_v, big_v);
    else
        update(id * 2 + 1, mid + 1, r, p, small_v, big_v);
    combine(id, l, r);
}

int main()
{
    std::scanf("%d", &n);
    for (auto i = 1; i <= n; i++) {
        std::scanf("%d%d", &small[i], &big[i]);
        if (small[i] > big[i])
            std::swap(small[i], big[i]);
    }

    build_tree(1, 1, n);

    std::scanf("%d", &m);
    for (auto i = 0; i < m; i++) {
        int l, r;
        std::scanf("%d%d", &l, &r);
        auto ts = small[l];
        auto tb = big[l];
        update(1, 1, n, l, small[r], big[r]);
        update(1, 1, n, r, ts, tb);
        if (flag[0][1])
            std::printf("TAK\n");
        else
            std::printf("NIE\n");
    }
}

