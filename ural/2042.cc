// ml:run = time -p $bin < input > output
// ml:opt = 3
#include <iostream>
#include <algorithm>
#include <string>

#define DEBUG 0

using ll = long long;

auto constexpr maxn = 100004;
auto constexpr maxk = 55;

int n, k;
std::string s;

struct node
{
    // 0 means not covered
    char ch;
    ll count;
    int lenl;
    int lenr;
    char left[maxk];
    char right[maxk];
};

node tree[4 * maxn];

void fill_same(char a[], int l, char ch)
{
    for (auto i = 0; i < l; i++)
        a[i] = ch;
}

void append(char a[], int la, char b[], int lb)
{
    for (auto i = 0; i < lb; i++)
        a[la + i] = b[i];
}

void shift_right(char a[], int len, int sl)
{
    for (auto i = len - 1; i >= 0; i--)
        a[i + sl] = a[i];
}

void copy(char from[], char to[], int len)
{
    std::copy(to, to + len, from);
}

// TODO test
auto all_same(ll len) -> ll
{
    if (len <= k)
        return (1ll + len) * len / 2ll;
    return (len - k) * k + (1ll + k) * k / 2ll;
}

void push_down(int id, int l, int r)
{
    auto& t = tree[id];
    if (!t.ch) return;
    auto& tl = tree[id * 2];
    auto& tr = tree[id * 2 + 1];
    tl.ch = tr.ch = t.ch;

    auto mid = (l + r) / 2;
    auto lenl = mid - l + 1;
    tl.count = all_same(lenl);
    auto tlen = std::min(lenl, k - 1);
    tl.lenl = tl.lenr = tlen;
    fill_same(tl.left, tlen, t.ch);
    fill_same(tl.right, tlen, t.ch);

    auto lenr = r - mid;
    tr.count = all_same(lenr);
    tlen = std::min(lenr, k - 1);
    fill_same(tr.left, tlen, t.ch);
    fill_same(tr.right, tlen, t.ch);

    t.ch = 0;
}

char ts[120];

auto calc(char a[], int lena, int la, char b[], int lenb, int lb) -> ll
{
    if (la == 0 || lb == 0)
        return 0;
    copy(a + lena - la, ts, la);
    copy(b, ts + la, lb);
    auto count = 0ll;
    for (auto i = 0; i < la + lb; i++) {
        auto j = 0;
        for (; i - j >= 0 && i + j < la + lb && ts[i - j] == ts[i + j]; j++)
            ;
        j = std::min(j, (k + 1)/2);
        if (i < la)
            count += std::max(0, i + j - la);
        else
            count += std::max(0, la - (i - j + 1));

        j = 0;
        for (; i - j >= 0 && i + j + 1 < la + lb && ts[i - j] == ts[i + j + 1]; j++)
            ;
        j = std::min(j, k/2);
        if (i < la)
            count += std::max(0, (i + j + 1 - 1) - la + 1);
        else
            count += std::max(0, la - (i - j + 1));
    }
    return count;
}

void push_up(int id, int l, int r)
{
    auto& t = tree[id];
    auto& tl = tree[id * 2    ];
    auto& tr = tree[id * 2 + 1];
    t.count = tl.count + tr.count
        + calc(tl.right, tl.lenr, std::min(tl.lenr, std::min(k-1, tl.lenr)),
                tr.left, tr.lenl, std::min(tr.lenl, std::min(k-1, tr.lenl)));

    auto mid = (l + r) / 2;
    auto lenl = mid - l + 1;
    copy(tl.left, t.left, tl.lenl);
    t.lenl = tl.lenl;
    if (tl.lenl == lenl) {
        auto remain = std::min(k - 1 - t.lenr, tr.lenl);
        append(t.left, t.lenl, tr.left, remain);
        t.lenl += remain;
    }

    auto lenr = r - mid;
    copy(tr.right, t.right, tr.lenr);
    t.lenr = tr.lenr;
    if (tr.lenr == lenr) {
        auto len = std::min(k - 1 - tr.lenr, tl.lenr);
        shift_right(t.right, t.lenr, len);
        t.lenr += len;
        copy(tl.right + tl.lenr - len, t.right, len);
    }
}

void build_tree(int id, int l, int r)
{
    auto& t = tree[id];
    if (l == r) {
        t.count = 1;
        t.ch = 0;
        t.lenl = t.lenr = 1;
        t.left[0] = t.right[0] = s[l - 1];
        return;
    }
    auto mid = (l + r) / 2;
    build_tree(id * 2,     l,       mid);
    build_tree(id * 2 + 1, mid + 1, r);
    push_up(id, l, r);
}

void print(int id, int l, int r)
{
    #if DEBUG
    auto& t = tree[id];
    std::cout << "tree[" << id << "] = {"
        << "l="     << l       << ", "
        << "r="     << r       << ", "
        << "count=" << t.count << ", "
        << "left=\""  << t.left  << "\", "
        << "right=\"" << t.right << "\", "
        << "ch=";

    if (t.ch)
        std::cout << t.ch;
    else
        std::cout << ".";
    std::cout << "}\n";

    if (l == r) {
        return;
    }
    auto mid = (l + r) / 2;
    print(id * 2,     l,       mid);
    print(id * 2 + 1, mid + 1, r);
    #endif
}

auto query(int id, int l, int r, int tl, int tr) -> ll
{
    if (tl <= l && r <= tr)
        return tree[id].count;

    push_down(id, l, r);

    auto mid = (l + r) / 2;
    auto count = 0ll;
    auto& left = tree[id * 2];
    auto& right = tree[id * 2 + 1];

    if (tl <= mid)
        count += query(id * 2, l, mid, tl, tr);
    if (tr > mid)
        count += query(id * 2 + 1, mid + 1, r, tl, tr);
    count += calc(
        left.right, left.lenr, std::min(k - 1, std::max(0, mid - tl + 1)),
        right.left, right.lenl, std::min(k - 1, std::max(0, tr - mid))
    );

    return count;
}

void cover(int id, int l, int r, int tl, int tr, char ch)
{
    auto& t = tree[id];
    if (tl <= l && r <= tr) {
        t.ch = ch;
        auto len = r - l + 1;
        t.count = all_same(len);
        auto tlen = std::min(len, k-1);
        t.lenl = t.lenr = tlen;
        fill_same(t.left, tlen, ch);
        fill_same(t.right, tlen, ch);
        return;
    }

    push_down(id, l, r);

    auto mid = (l + r) / 2;
    if (tl <= mid)
        cover(id * 2, l, mid, tl, tr, ch);
    if (tr > mid)
        cover(id * 2 + 1, mid + 1, r, tl, tr, ch);

    push_up(id, l, r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> s >> k;
    n = s.size();

    build_tree(1, 1, n);

    int q;
    std::cin >> q;
    while (q--) {
        int id, l, r;
        std::cin >> id >> l >> r;
        if (id == 2) {
            std::cout << query(1, 1, n, l, r) << "\n";
        } else {
            char ch;
            std::cin >> ch;
            cover(1, 1, n, l, r, ch);
        }

        print(1, 1, n);
    }
}

