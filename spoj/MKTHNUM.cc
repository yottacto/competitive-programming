// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>

auto constexpr maxn = 100007;
int n, m;
int a[maxn];
int root[maxn];

struct node
{
    int left;
    int right;
    int count;
};

node t[40 * maxn];
int alloc;

std::vector<int> da;

void update(int pre, int& now, int pos, int l = 1, int r = n)
{
    now = ++alloc;
    t[alloc] = t[pre];
    t[alloc].count++;

    if (l == r) return;
    auto mid = (l + r) / 2;
    if (pos <= mid)
        update(t[pre].left, t[now].left, pos, l, mid);
    else
        update(t[pre].right, t[now].right, pos, mid + 1, r);
}

auto query(int pre, int now, int k, int l = 1, int r = n)
{
    if (l == r)
        return l;
    auto mid = (l + r) / 2;
    auto count = t[t[now].left].count - t[t[pre].left].count;
    if (count >= k)
        return query(t[pre].left, t[now].left, k, l, mid);
    else
        return query(t[pre].right, t[now].right, k - count, mid + 1, r);
}

auto id(int x)
{
    return std::lower_bound(da.begin(), da.end(), x) - da.begin() + 1;
}

auto value(int id)
{
    return da.at(id - 1);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    da.reserve(n);
    for (auto i = 0; i < n; i++) {
        std::cin >> a[i];
        da.emplace_back(a[i]);
    }
    std::sort(da.begin(), da.end());
    da.erase(std::unique(da.begin(), da.end()), da.end());

    for (auto i = 1; i <= n; i++)
        update(root[i - 1], root[i], id(a[i - 1]));

    for (auto i = 0; i < m; i++) {
        int l, r, k;
        std::cin >> l >> r >> k;
        std::cout << value(query(root[l - 1], root[r], k)) << "\n";
    }
}

