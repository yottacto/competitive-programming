// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>

auto constexpr maxn = 1000007;
int sum[maxn];
int dp[maxn];
int q[maxn];

int n, nq;
int max_depth;
std::vector<std::vector<int>> tree;

void dfs(int u, int depth = 1)
{
    max_depth = std::max(max_depth, depth);
    sum[depth]++;
    for (auto v : tree[u])
        dfs(v, depth + 1);
}


auto coord_y(int i) { return sum[i + 1]; }
auto coord_x(int i) { return i; }
auto slope_y(int i, int j) { return coord_y(i) - coord_y(j); }
auto slope_x(int i, int j) { return coord_x(i) - coord_x(j); }

auto slope_less(int i, int j, int k)
{
    return slope_y(i, j) * slope_x(j, k) > slope_x(i, j) * slope_y(j, k);
}

auto calc(int i, int j)
{
    return i * j + sum[j + 1];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> nq;
    std::vector<int> query;
    for (auto i = 0; i < nq; i++) {
        int t;
        std::cin >> t;
        query.emplace_back(std::min(n, t));
    }

    tree.resize(n + 1);
    for (auto i = 2; i <= n; i++) {
        int parent;
        std::cin >> parent;
        tree[parent].emplace_back(i);
    }

    dfs(1);
    for (auto i = max_depth - 1; i >= 1; i--)
        sum[i] += sum[i + 1];

    auto head = 1;
    auto tail = 0;
    for (auto i = 0; i <= max_depth; i++) {
        while (head < tail && slope_less(i, q[tail], q[tail - 1]))
            tail--;
        q[++tail] = i;
    }

    for (auto i = 1; i <= n; i++) {
        while (head < tail && calc(i, q[head]) < calc(i, q[head + 1]))
            head++;
        dp[i] = q[head] + (sum[q[head] + 1] + i - 1) / i;
    }

    for (auto i : query)
        std::cout << dp[i] << " ";
    std::cout << "\n";
}

