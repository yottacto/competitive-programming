// ml:run = $bin < input
#include <iostream>
#include <vector>

auto constexpr maxn = 1000007;
int color[maxn];
int color_pa[maxn];
int color_pb[maxn];
int a[maxn];
int b[maxn];
int max_left[maxn];
int max_right[maxn];
int left[maxn];
int right[maxn];
// same_color[i] means the largest index have same color with some color in
// interval [1, i]
int same_color[maxn];
int last_color[maxn];
int n, k, m, l;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> k;
    for (auto i = 1; i <= n; i++) {
        std::cin >> color[i];
        last_color[color[i]] = i;
    }
    std::cin >> m >> l;
    for (auto i = 1; i <= m; i++) {
        std::cin >> a[i];
        color_pa[a[i]] = i;
    }
    for (auto i = 1; i <= l; i++) {
        std::cin >> b[i];
        color_pb[b[i]] = i;
    }

    for (auto i = 1; i <= n; i++) {
        auto p = color_pa[color[i]];
        if (p)
            max_left[p] = p == 1 ? i : max_left[p - 1];
        left[i] = max_left[m];
    }

    for (auto i = n; i >= 1; i--) {
        auto p = color_pb[color[i]];
        if (p)
            max_right[p] = p == 1 ? i : max_right[p - 1];
        right[i] = max_right[l];
    }

    for (auto i = 1; i <= n; i++)
        same_color[i] = std::max(same_color[i - 1], last_color[color[i]]);

    std::vector<int> ans;
    for (auto i = 1; i <= n; i++) {
        if (color[i] != a[m] || !left[i] || !right[i])
            continue;
        if (same_color[left[i] - 1] > right[i])
            ans.emplace_back(i);
    }

    std::cout << ans.size() << "\n";
    for (auto i : ans)
        std::cout << i << " ";
    std::cout << "\n";
}

