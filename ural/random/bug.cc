// ml:run = cp $bin bug
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

auto constexpr maxn = 100004;
char str[4 * maxn];
int sum[4 * maxn];
int all[4 * maxn];
int right_k[maxn];

std::string s;
int n, k;

void build_string(int id, int l, int r)
{
    if (l == r) {
        str[id] = s[l - 1];
        return;
    }
    auto mid = (l + r) / 2;
    build_string(id * 2, l, mid);
    build_string(id * 2 + 1, mid + 1, r);
}

void build(int id, int l, int r)
{
    if (l == r) {
        sum[id] = right_k[l];
        return;
    }
    auto mid = (l + r) / 2;
    build(id * 2, l, mid);
    build(id * 2 + 1, mid + 1, r);
    sum[id] = sum[id * 2] + sum[id * 2 + 1];
}

auto get_char(int id, int l, int r, int p)
{
    if (l == r)
        return str[id];
    if (str[id]) {
        str[id * 2] = str[id * 2 + 1] = str[id];
        str[id] = 0;
    }
    auto mid = (l + r) / 2;
    if (p <= mid)
        return get_char(id * 2, l, mid, p);
    else
        return get_char(id * 2 + 1, mid + 1, r, p);
}

auto get_string(int id, int l, int r, int tl, int tr)
{
    if (l == r)
        return std::string{str[id]};
    if (str[id])
        return std::string(tr - tl + 1, str[id]);
    auto mid = (l + r) / 2;
    std::string ret;
    if (tl <= mid)
        ret += get_string(id * 2, l, mid, tl, std::min(tr, mid));
    if (tr > mid)
        ret += get_string(id * 2 + 1, mid + 1, r, std::max(tl, mid + 1), tr);
    return ret;
}

auto get_string(int l, int r)
{
    if (l > r) return std::string{""};
    return get_string(1, 1, n, l, r);

    // std::string ret;
    // for (auto i = l; i <= r; i++)
    //     ret += get_char(1, 1, n, i);
    // return ret;
}

void cover_string(int id, int l, int r, int tl, int tr, char ch)
{
    if (tl <= l && r <= tr) {
        str[id] = ch;
        return;
    }
    if (str[id]) {
        str[id * 2] = str[id * 2 + 1] = str[id];
        str[id] = 0;
    }
    auto mid = (l + r) / 2;
    if (tl <= mid)
        cover_string(id * 2, l, mid, tl, tr, ch);
    if (tr > mid)
        cover_string(id * 2 + 1, mid + 1, r, tl, tr, ch);
}

auto get_sum(int id, int l, int r, int tl, int tr)
{
    if (tl <= l && r <= tr)
        return sum[id];
    if (all[id])
        return (tr - tl + 1) * all[id];
    auto ret = 0;
    auto mid = (l + r) / 2;
    if (tl <= mid)
        ret += get_sum(id * 2, l, mid, tl, std::min(tr, mid));
    if (tr > mid)
        ret += get_sum(id * 2 + 1, mid + 1, r, std::max(mid + 1, tl), tr);
    return ret;
}

void cover(int id, int l, int r, int tl, int tr, int k)
{
    if (tl <= l && r <= tr) {
        all[id] = k;
        sum[id] = k * (r - l + 1);
        return;
    }
    auto mid = (l + r) / 2;
    if (all[id]) {
        all[id * 2] = all[id * 2 + 1] = all[id];
        all[id] = 0;
        sum[id * 2] = k * (mid - l + 1);
        sum[id * 2 + 1] = k * (r - mid);
    }
    if (tl <= mid)
        cover(id * 2, l, mid, tl, tr, k);
    if (tr > mid)
        cover(id * 2 + 1, mid + 1, r, tl, tr, k);
    sum[id] = sum[id * 2] + sum[id * 2 + 1];
}

void update(int id, int l, int r, int tl, int tr)
{
    if (l == r) {
        sum[id] = right_k[l];
        return;
    }
    auto mid = (l + r) / 2;
    if (all[id]) {
        all[id * 2] = all[id * 2 + 1] = all[id];
        all[id] = 0;
        sum[id * 2] = k * (mid - l + 1);
        sum[id * 2 + 1] = k * (r - mid);
    }
    if (tl <= mid)
        update(id * 2, l, mid, tl, tr);
    if (tr > mid)
        update(id * 2 + 1, mid + 1, r, tl, tr);
    sum[id] = sum[id * 2] + sum[id * 2 + 1];
}

char tmp[400];
std::vector<int> p(400);

auto manacher(std::string const& s)
{
    tmp[0] = '$';
    tmp[1] = '#';
    int n = 2;
    for (auto ch : s) {
        tmp[n++] = ch;
        tmp[n++] = '#';
    }
    tmp[n] = '!';

    auto mx = 0;
    auto id = 0;
    auto count = 0;
    for (auto i = 1; i < n; i++) {
        p[i] = mx > i
            ? std::min(p[2 * id - i], mx - i)
            : 1;
        while (tmp[i + p[i]] == tmp[i - p[i]])
            p[i]++;
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        count += i == p[i];
    }
    return count - 1;
}

auto query(int l, int r)
{
    auto sum = 0;
    if (l <= r - k + 1)
        sum = get_sum(1, 1, n, l, r - k + 1);
    auto tmp = get_string(std::max(l, r - k + 2), r);
    manacher(tmp);
    for (auto i = 0; i < (int)tmp.size(); i++) {
        auto t = 0;
        for (auto j = i * 2 + 2; j <= 2 * (int)tmp.size(); j++)
            if (p[j] >= j - (2 * i + 1))
                t++;
        sum += t;
    }
    return sum;
}

void update(int l, int r, char ch)
{
    cover_string(1, 1, n, l, r, ch);
    if (l <= r - k + 1)
        cover(1, 1, n, l, r - k + 1, k);
    // update interval before [l, r]
    auto ll = std::max(1, l - k + 1);
    auto rr = std::min(n, l - 1 + k - 1);
    auto tmp = get_string(ll, rr);
    manacher(tmp);
    rr = -1;
    for (auto i = 0; i < (int)tmp.size() && ll + i < l; i++) {
        auto t = 0;
        for (auto j = i * 2 + 2; j - (2 * i + 1) <= k; j++) {
            if (p[j] >= j - (2 * i + 1))
                t++;
        }
        right_k[ll + i] = t;
        rr = ll + i;
    }
    if (ll <= rr)
        update(1, 1, n, ll, rr);

    // update interval at the end of [l, r]
    ll = std::max(l, r - k + 2);
    rr = std::min(n, r + k - 1);
    tmp = get_string(ll, rr);
    manacher(tmp);
    rr = -1;
    for (auto i = 0; i < (int)tmp.size() && ll + i <= r; i++) {
        auto t = 0;
        for (auto j = i * 2 + 2; j - (2 * i + 1) <= k; j++) {
            if (p[j] >= j - (2 * i + 2) + 1)
                t++;
        }
        right_k[ll + i] = t;
        rr = ll + i;
    }
    if (ll <= rr)
        update(1, 1, n, ll, rr);
}

void init()
{
    n = s.size();
    build_string(1, 1, n);
    for (auto i = 0; i < n; i++) {
        auto len = std::min(k, n - i);
        right_k[i + 1] = manacher(s.substr(i, len));
    }
    build(1, 1, n);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> s >> k;
    init();

    int q;
    std::cin >> q;
    while (q--) {
        int opt, l, r;
        std::cin >> opt >> l >> r;
        if (opt == 1) {
            char ch;
            std::cin >> ch;
            update(l, r, ch);
        } else {
            std::cout << query(l, r) << "\n";
        }
    }
}

