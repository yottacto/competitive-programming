// ml:run = $bin < input
#include <bits/stdc++.h>

auto constexpr maxn = 200007;

int tree[maxn];
int value[maxn];

struct data
{
    int k;
    int p;
    int id;
};

int n, m;
std::vector<int> a;
std::vector<std::vector<data>> query;
std::vector<int> ans;
std::map<int, std::set<int>> all;

int lowbit(int x)
{
    return x & -x;
}

void update(int p, int d)
{
    for (; p <= n; p += lowbit(p))
        tree[p] += d;
}

int query_sum(int p)
{
    auto res = 0;
    for (; p > 0; p -= lowbit(p))
        res += tree[p];
    return res;
}

int search(int p)
{
    auto l = 1;
    auto r = n;
    while (l + 1 < r) {
        auto mid = (l + r) / 2;
        if (query_sum(mid) >= p)
            r = mid;
        else
            l = mid;
    }
    if (query_sum(l) == p)
        r = l;
    return value[r];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n;
    a.resize(n);
    for (auto i = 0; i < n; i++) {
        std::cin >> a[i];
        all[a[i]].emplace(i);
    }
    std::cin >> m;
    ans.resize(m);
    query.resize(n + 1);
    for (auto i = 0; i < m; i++) {
        int k, p;
        std::cin >> k >> p;
        query[k].emplace_back(data{k, p, i});
    }

    auto b = a;
    std::sort(b.begin(), b.end(), std::greater<int>{});
    auto cur = n;
    for (auto i = 0; i < n; i++) {
        int tp;
        auto p = all[b[i]].lower_bound(cur);
        if (p == all[b[i]].begin()) {
            tp = *all[b[i]].begin();
        } else {
            p = std::prev(p);
            tp = *p;
        }
        cur = std::min(cur, tp);
        all[b[i]].erase(tp);
        // std::cout << tp << " " << b[i] << "\n";
        value[tp + 1] = b[i];
        update(tp + 1, 1);

        for (auto const& q : query[i + 1]) {
            ans[q.id] = search(q.p);
        }
    }
    for (auto i : ans)
        std::cout << i << "\n";
}

