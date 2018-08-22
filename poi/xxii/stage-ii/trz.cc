// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

auto constexpr maxn = 1000010;
int sum[3][maxn];
// 'C', 'B', 'S'
std::string s;
std::map<char, int> table{
    {'C', 0},
    {'B', 1},
    {'S', 2},
};

int n;

struct data
{
    data(int s1, int s2, int s3, int id)
        : u(s1 - s2), v(s1 - s3 + n + 1), w(s2 - s3), id(id)
    {
    }

    int u, v, w, id;
};

struct node
{
    int w;
    int value{0};
    int w2;
    int second_value{0};
};

node node_max(node lhs, node rhs)
{
    if (lhs.value < rhs.value)
        std::swap(lhs, rhs);
    if (rhs.value > lhs.second_value && rhs.w != lhs.w) {
        lhs.second_value = rhs.value;
        lhs.w2 = rhs.w;
    } else if (rhs.second_value > lhs.second_value && rhs.w2 != lhs.w) {
        lhs.second_value = rhs.second_value;
        lhs.w2 = rhs.w2;
    }
    return lhs;
}

std::vector<node> tree[2];
int len;

int lowbit(int x)
{
    return x & -x;
}

int query(std::vector<node> const& tree, int p, int w)
{
    auto max = tree[p];
    for (; p > 0; p -= lowbit(p))
        max = node_max(max, tree[p]);

    if (max.w != w)
        return max.value;
    else
        return max.second_value;
}

int query(data const& da)
{
    auto v = da.v;
    auto p = std::max(
        query(tree[0], v - 1, da.w),
        query(tree[1], len - v, da.w)
    );
    return p;
}

void update(std::vector<node>& tree, int p, node const& a)
{
    for (; p <= len; p += lowbit(p))
        tree[p] = node_max(tree[p], a);
}

void update(data const& da)
{
    node a{};
    a.w = da.w;
    a.value = da.id;
    auto v = da.v;
    update(tree[0], v, a);
    update(tree[1], len - v + 1, a);
}

int same()
{
    auto max = 0;
    auto now = 1;
    for (auto i = 1; i < n; i++) {
        if (s[i] != s[i - 1]) {
            max = std::max(max, now);
            now = 1;
        } else
            now++;
    }
    return std::max(max, now);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> s;
    auto ans = same();
    for (auto i = 0; i < n; i++) {
        for (auto k = 0; k < 3; k++)
            sum[k][i + 1] = sum[k][i];
        sum[table[s[i]]][i + 1]++;
    }
    std::vector<data> da;

    da.reserve(n + 1);
    for (auto i = 0; i <= n; i++)
        da.emplace_back(sum[0][i], sum[1][i], sum[2][i], i);

    std::sort(da.begin(), da.end(), [](data const& lhs, data const& rhs) {
        return lhs.u < rhs.u;
    });

    len = 2 * n + 2;
    tree[0].resize(len + 1);
    tree[1].resize(len + 1);
    for (auto i = 0; i <= n; i++) {
        auto p = query(da[i]);
        // std::cerr << "i=" << i << " " << p << "\n";
        ans = std::max(ans, p - da[i].id);
        if (i == n || da[i].u != da[i + 1].u) {
            auto j = i;
            do {
                update(da[j--]);
            } while (j >= 0 && da[j].u == da[j + 1].u);
        }
    }

    for (auto i = 0; i < 2; i++) {
        tree[i].clear();
        tree[i].resize(len + 1);
    }
    for (auto i = n; i >= 0; i--) {
        auto p = query(da[i]);
        ans = std::max(ans, p - da[i].id);
        if (i == 0 || da[i].u != da[i - 1].u) {
            auto j = i;
            do {
                update(da[j++]);
            } while (j < n && da[j].u == da[j - 1].u);
        }
    }
    std::cout << ans << "\n";
}

