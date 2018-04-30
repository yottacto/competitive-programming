// ml:run = time -p $bin < input > output
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#define DEBUG 0

using ll = long long;

auto constexpr maxn = 100004;

int n, k;
std::string s;

struct node
{
    // 0 means not covered
    char ch;
    ll count;
    std::string left;
    std::string right;
};

node tree[4 * maxn];

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
    tl.left = tl.right = std::string(std::min(lenl, k - 1), t.ch);

    auto lenr = r - mid;
    tr.count = all_same(lenr);
    tr.left = tr.right = std::string(std::min(lenr, k - 1), t.ch);

    t.ch = 0;
}

char tmp[400];
std::vector<int> p(400);

auto manacher(std::string const& s, int l) -> ll
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
    auto mlen = 0;
    auto mcenter = 0;
    auto count = 0ll;
    l = 2 * (l + 1);
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
        if (mlen < p[i]) {
            mlen = p[i];
            mcenter = i;
        }
        if (tmp[i] == '#') {
            if (i < l)
                count += std::max(0, i + std::min(p[i], (k - (k&1)) + 1) - l);
            else
                count += std::max(0, l - i + std::min(p[i], (k - (k&1)) + 1) - 2);
        } else {
            if (i < l)
                count += std::max(0, i + std::min(p[i], (k - !(k&1)) + 1) - l);
            else
                count += std::max(0, l - i + std::min(p[i], (k - !(k&1)) + 1) - 2);
        }
    }
    return count / 2;
}

auto calc(std::string const& a, int la, std::string const& b, int lb) -> ll
{
    if (la == 0 || lb == 0)
        return 0;
    return manacher(a.substr(a.size() - la, la) + b.substr(0, lb), la); // - manacher(sl) - manacher(sr);
    // auto ts = sl + sr;
    // auto count = 0ll;
    // for (auto i = 0; i < la + lb; i++) {
    //     auto j = 0;
    //     for (; i - j >= 0 && i + j < la + lb && ts[i - j] == ts[i + j]; j++)
    //         ;
    //     j = std::min(j, (k + 1)/2);
    //     if (i < la)
    //         count += std::max(0, i + j - la);
    //     else
    //         count += std::max(0, la - (i - j + 1));

    //     j = 0;
    //     for (; i - j >= 0 && i + j + 1 < la + lb && ts[i - j] == ts[i + j + 1]; j++)
    //         ;
    //     j = std::min(j, k/2);
    //     if (i < la)
    //         count += std::max(0, (i + j + 1 - 1) - la + 1);
    //     else
    //         count += std::max(0, la - (i - j + 1));
    // }
    // return count;
}

void push_up(int id, int l, int r)
{
    auto& t = tree[id];
    auto const& tl = tree[id * 2    ];
    auto const& tr = tree[id * 2 + 1];
    t.count = tl.count + tr.count
        + calc(tl.right, std::min(k-1, (int)tl.right.size()),
                tr.left, std::min(k-1, (int)tr.left.size()));

    auto mid = (l + r) / 2;
    auto lenl = mid - l + 1;
    t.left = tl.left;
    if ((int)tl.left.size() == lenl)
        t.left += tr.left.substr(0, k - 1 - t.left.size());

    auto lenr = r - mid;
    t.right = tr.right;
    if ((int)tr.right.size() == lenr) {
        auto len = std::min(k - 1 - t.right.size(), tl.right.size());
        t.right = tl.right.substr(tl.right.size() - len, len) + t.right;
    }
}

void build_tree(int id, int l, int r)
{
    auto& t = tree[id];
    if (l == r) {
        t.count = 1;
        t.ch = 0;
        t.left = t.right = s[l - 1];
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

    if (tree[id].ch)
        return all_same(tr - tl + 1);

    auto mid = (l + r) / 2;
    auto count = 0ll;
    auto const& left = tree[id * 2];
    auto const& right = tree[id * 2 + 1];

    if (tl <= mid)
        count += query(id * 2, l, mid, tl, std::min(tr, mid));
    if (tr > mid)
        count += query(id * 2 + 1, mid + 1, r, std::max(mid + 1, tl), tr);
    count += calc(
        left.right, std::min(std::min<int>(k - 1, left.right.size()), std::max(0, mid - tl + 1)),
        right.left, std::min(std::min<int>(k - 1, left.right.size()), std::max(0, tr - mid))
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
        t.left = t.right = std::string(std::min(len, k-1), ch);
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

    std::vector<ll> ans;
    int q;
    std::cin >> q;
    while (q--) {
        int id, l, r;
        std::cin >> id >> l >> r;
        if (id == 2) {
            ans.emplace_back(query(1, 1, n, l, r));
            // std::cout << query(1, 1, n, l, r) << "\n";
        } else {
            char ch;
            std::cin >> ch;
            cover(1, 1, n, l, r, ch);
        }

        // print(1, 1, n);
    }

    for (auto i : ans)
        std::cout << i << "\n";
}

