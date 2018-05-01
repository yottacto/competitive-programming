// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <algorithm>

auto constexpr maxn = 100004;
int a[maxn];
int n, d, b;

int sum[maxn * 4];
int cover[maxn * 4];
bool all[maxn * 4];

void push(int id, int l, int r)
{
    if (!all[id]) return;
    all[id * 2] = all[id * 2 + 1] = true;
    cover[id * 2] = cover[id * 2 + 1] = cover[id];
    auto mid = (l + r) / 2;
    sum[id * 2]     = cover[id] * (mid - l + 1);
    sum[id * 2 + 1] = cover[id] * (r - mid);
    all[id] = false;
}

void combine(int id)
{
    sum[id] = sum[id * 2] + sum[id * 2 + 1];
}

void build_tree(int id, int l, int r)
{
    if (l == r) {
        sum[id] = a[l];
        return;
    }
    auto mid = (l + r) / 2;
    build_tree(id * 2, l, mid);
    build_tree(id * 2 + 1, mid + 1, r);
    combine(id);
}

void update(int id, int l, int r, int tl, int tr, int value)
{
    if (tl <= l && r <= tr) {
        all[id] = true;
        cover[id] = value;
        sum[id] = value * (r - l + 1);
        return;
    }

    push(id, l, r);
    auto mid = (l + r) / 2;
    if (tl <= mid)
        update(id * 2, l, mid, tl, tr, value);
    if (tr > mid)
        update(id * 2 + 1, mid + 1, r, tl, tr, value);
    combine(id);
}

auto get(int id, int l, int r, int p) -> int
{
    if (l == r)
        return sum[id];
    if (all[id])
        return cover[id];
    auto mid = (l + r) / 2;
    if (p <= mid)
        return get(id * 2, l, mid, p);
    else
        return get(id * 2 + 1, mid + 1, r, p);
}

auto get(int p)
{
    return get(1, 1, n, p);
}

auto get_sum(int id, int l, int r, int tl, int tr)
{
    if (tl <= l && r <= tr)
        return sum[id];
    push(id, l, r);
    auto mid = (l + r) / 2;
    auto ret = 0;
    if (tl <= mid)
        ret += get_sum(id * 2, l, mid, tl, tr);
    if (tr > mid)
        ret += get_sum(id * 2 + 1, mid + 1, r, tl, tr);
    return ret;
}

auto rgreater_equal(int id, int l, int r, int tl, int tr, int value) -> std::pair<int, int>
{
    if (l == r) {
        return {sum[id], sum[id] >= value ? l : -1};
    }
    push(id, l, r);
    auto mid = (l + r) / 2;
    if (tl <= mid) {
        auto lsum = get_sum(id * 2, l, mid, tl, tr);
        if (lsum >= value)
            return rgreater_equal(id * 2, l, mid, tl, tr, value);
        else {
            if (tr <= mid) return {lsum, -1};
            auto tright = rgreater_equal(id * 2 + 1, mid + 1, r, tl, tr, value - lsum);
            return {lsum + tright.first, tright.second};
        }
    } else {
        return rgreater_equal(id * 2 + 1, mid + 1, r, tl, tr, value);
    }
}

// (sum, pos), pos == -1 means no solutons, smallest pos [l, pos], sum > value
auto rgreater_equal(int l, int r, int value) -> std::pair<int, int>
{
    if (l > r) return {0, -1};
    auto tmp = rgreater_equal(1, 1, n, l, r, value);
    return tmp;
}

auto lgreater_equal(int id, int l, int r, int tl, int tr, int value) -> std::pair<int, int>
{
    if (l == r) {
        return {sum[id], sum[id] >= value ? l : -1};
    }
    push(id, l, r);
    auto mid = (l + r) / 2;
    if (tr > mid) {
        auto rsum = get_sum(id * 2 + 1, mid + 1, r, tl, tr);
        if (rsum >= value)
            return lgreater_equal(id * 2 + 1, mid + 1, r, tl, tr, value);
        else {
            if (tl > mid) return {rsum, -1};
            auto tleft = lgreater_equal(id * 2, l, mid, tl, tr, value - rsum);
            return {rsum + tleft.first, tleft.second};
        }
    } else {
        return lgreater_equal(id * 2, l, mid, tl, tr, value);
    }
}

// (sum, pos), pos == -1 means no solutons, largest  pos [pos, r], sum > value
auto lgreater_equal(int l, int r, int value) -> std::pair<int, int>
{
    if (l > r) return {0, -1};
    return lgreater_equal(1, 1, n, l, r, value);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> d >> b;
    for (auto i = 1; i <= n; i++)
        std::cin >> a[i];
    build_tree(1, 1, n);
    auto c1 = 0;
    auto c2 = 0;
    for (auto l = 1, r = n, i = 1; l <= r; l++, r--, i++) {
        // process l
        {
            auto now = get(l);
            auto remain = b - now;
            int tl = std::max<long long>(1, l - (long long)i * d);
            int tr = std::min<long long>(n, l + (long long)i * d);
            if (remain <= 0) {
                update(1, 1, n, l, l, -remain);
            } else {
                auto p = rgreater_equal(tl, tr, b);
                if (p.second == -1) {
                    c1++;
                } else {
                    auto right = get(p.second);
                    auto sum = p.first - right;
                    if (tl <= p.second - 1)
                        update(1, 1, n, tl, p.second - 1, 0);
                    auto delta = b - sum;
                    update(1, 1, n, p.second, p.second, right - delta);
                }
            }
        }

        // process r
        {
            if (l == r) continue;
            auto now = get(r);
            auto remain = b - now;
            int tl = std::max<long long>(1, r - (long long)i * d);
            int tr = std::min<long long>(n, r + (long long)i * d);
            if (remain <= 0) {
                update(1, 1, n, r, r, -remain);
            } else {
                auto p = lgreater_equal(tl, tr, b);
                if (p.second == -1) {
                    c2++;
                } else {
                    auto left = get(p.second);
                    auto sum = p.first - left;
                    if (p.second + 1 <= tr)
                        update(1, 1, n, p.second + 1, tr, 0);
                    auto delta = remain - sum;
                    update(1, 1, n, p.second, p.second, left - delta);
                }
            }
        }

        // std::cout << c1 << " " << c2 << "\n";
        // for (auto i = 1; i <= n; i++) std::cout << get(i) << " ";
        // std::cout << "\n";

    }
    std::cout << std::max(c1, c2) << "\n";
}

