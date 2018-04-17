// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <utility>
#include <algorithm>
#include <functional>
#include <vector>

auto constexpr inf = 200001;
std::vector<int> a;
int n;
auto less = std::less<int>{};
auto greater = std::greater<int>{};

template <class Compare>
auto same_order(Compare comp)
{
    std::vector<int> ra{inf};
    std::vector<int> rb{inf};
    if (comp(0, ra[0]))
        ra[0] = 0;
    if (comp(0, rb[0]))
        rb[0] = 0;

    for (auto i : a) {
        // ensure when comp = less, ra.back() > rb.back()
        if (comp(ra.back(), rb.back()))
            std::swap(ra, rb);

        if (comp(ra.back(), i))
            ra.emplace_back(i);
        else if (comp(rb.back(), i))
            rb.emplace_back(i);
        else
            return false;
    }

    if (ra.size() > rb.size())
        std::swap(ra, rb);
    if (ra.size() == 1) {
        ra.emplace_back(rb.back());
        rb.pop_back();
    }

    std::cout << ra.size() - 1 << " " << rb.size() - 1 << "\n";
    for (auto i = 1u; i < ra.size(); i++)
        std::cout << ra[i] << " ";
    std::cout << "\n";
    for (auto i = 1u; i < rb.size(); i++)
        std::cout << rb[i] << " ";
    std::cout << "\n";
    return true;
}

// 0 means current i in inc seq
// 1 means current i in dec seq
int dp[100001][2];
std::pair<int, int> from[100001][2];

auto diff_order()
{
    dp[0][0] = inf;
    dp[0][1] = 0;
    from[0][0] = {-1, 0};
    from[0][1] = {-1, 0};
    for (auto i = 1; i < n; i++) {
        dp[i][0] = dp[i][1] = -1;
        if (a[i] > a[i - 1] && dp[i - 1][0] != -1) {
            dp[i][0] = dp[i - 1][0];
            from[i][0] = {i - 1, 0};
        }
        if (dp[i - 1][1] != -1 && a[i] > dp[i - 1][1]) {
            if (dp[i][0] == -1 || dp[i][0] < a[i - 1]) {
                dp[i][0] = a[i - 1];
                from[i][0] = {i - 1, 1};
            }
        }

        if (a[i] < a[i - 1] && dp[i - 1][1] != -1) {
            dp[i][1] = dp[i - 1][1];
            from[i][1] = {i - 1, 1};
        }
        if (dp[i - 1][0] != -1 && a[i] < dp[i - 1][0]) {
            if (dp[i][1] == -1 || dp[i][1] > a[i - 1]) {
                dp[i][1] = a[i - 1];
                from[i][1] = {i - 1, 0};
            }
        }
    }

    if (dp[n - 1][0] == -1 && dp[n - 1][1] == -1)
        return false;

    auto last = std::make_pair(n - 1, 0);
    if (dp[n - 1][1] != -1)
        last = {n - 1, 1};

    std::vector<int> ra;
    std::vector<int> rb;

    for (; last.first != -1; last = from[last.first][last.second])
        if (last.second)
            ra.emplace_back(a[last.first]);
        else
            rb.emplace_back(a[last.first]);

    std::reverse(std::begin(ra), std::end(ra));
    std::reverse(std::begin(rb), std::end(rb));

    if (ra.size() > rb.size())
        std::swap(ra, rb);
    if (ra.size() == 1) {
        ra.emplace_back(rb.back());
        rb.pop_back();
    }

    std::cout << ra.size() << " " << rb.size() << "\n";
    for (auto i = 0u; i < ra.size(); i++)
        std::cout << ra[i] << " ";
    std::cout << "\n";
    for (auto i = 0u; i < rb.size(); i++)
        std::cout << rb[i] << " ";
    std::cout << "\n";
    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    a.resize(n);
    for (auto& i : a)
        std::cin >> i;

    if (same_order(less)
        || same_order(greater)
        || diff_order()) {
        return 0;
    }
    std::cout << "Fail\n";
}

