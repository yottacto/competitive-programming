// ml:std = c++11
// ml:run = time -p $bin < input
#include <iostream>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <string>
#include <vector>
// in luogu, unordered_set mle
#include <set>

using ll = long long;
auto constexpr mo = 1000000007ll;
auto constexpr maxn = 1000100;
ll f[maxn];
ll g[maxn];

std::vector<std::set<int>> graph;
int n, k, p;

template <class T>
T abs(T x) { return x < 0 ? -x : x; }

template <class Vec>
void print(Vec const& v)
{
    for (auto i : v)
        std::cout << i << " ";
    std::cout << "\n";
}

bool check(std::vector<int> const& a, bool circle = false)
{
    if (circle && abs(a.back() - a[0]) > p)
        return false;
    for (auto i = 1u; i < a.size(); i++)
        if (abs(a[i] - a[i-1]) > p || graph[a[i - 1]].count(a[i]))
            return false;
    if (circle)
        return !graph[a.back()].count(a[0]);
    return true;
}

bool check(int base, std::string const& s)
{
    int n = s.size();
    for (auto i = 1; i < n; i++) {
        auto prev = base + s[i - 1] - '0';
        auto now = base + s[i] - '0';
        if (graph[prev].count(now))
            return false;
    }
    return true;
}

bool check(int i, std::string const& l, std::string const& r)
{
    return check(i, l) && check(i, r);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> k >> p;
    if (n == 1) { std::cout << "1\n"; return 0; }
    if (p == 0) { std::cout << "0\n"; return 0; }
    graph.resize(n + 1);
    for (auto i = 0; i < k; i++) {
        int a, b;
        std::cin >> a >> b;
        graph[a].insert(b);
    }
    if (p == 1 && n > 2) { std::cout << "0\n"; return 0; }

    if (p == 2) {
        std::vector<int> a(n);
        auto now = 3;
        auto i = 1;
        a[0] = 1;
        for (; now <= n; i++, now += 2)
            a.at(i) = now;
        if (now - 1 > n) now -= 2;
        for (now--; now > 1; i++, now -= 2)
            a.at(i) = now;
        int count = check(a, true);
        a[0] = 1;
        now = 2;
        i = 1;
        for (; now <= n; i++, now += 2)
            a.at(i) = now;
        if (now - 1 > n) now -= 2;
        for (now--; now > 1; i++, now -= 2)
            a.at(i) = now;
        count += check(a, true);
        if (n <= 2) count /= 2;
        std::cout << count << "\n";
        return 0;
    }

    if (n <= 7) {
        std::vector<int> v(n);
        std::iota(std::begin(v), std::end(v), 1);
        auto ans = 0;
        do {
            if (check(v, true))
                ans++;
        } while (std::next_permutation(std::next(std::begin(v)), std::end(v)));
        std::cout << (ans % mo) << "\n";
        return 0;
    }

    for (auto i = std::max(n - 7, 1); i < n; i++) {
        auto len = n - i + 1;
        std::vector<int> v(len);
        std::iota(std::begin(v), std::end(v), i+1);
        v[0] = i;
        v[len - 1] = i + 1;
        do {
            if (check(v)) f[i]++;
        } while (std::next_permutation(
            std::next(std::begin(v)),
            std::prev(std::end(v))
        ));
        f[i] %= mo;

        std::iota(std::begin(v), std::end(v), i+1);
        v[len - 1] = i;
        do {
            if (check(v)) g[i]++;
        } while (std::next_permutation(
            std::next(std::begin(v)),
            std::prev(std::end(v))
        ));
        g[i] %= mo;
    }

    for (auto i = std::max(n - 7, 1) - 1; i >= 1; i--) {
        f[i] = g[i + 1] * check(i, "1", "02")
            + g[i + 2] * check(i, "21", "03")
            + g[i + 4] * check(i, "41", "0325")
            + g[i + 5] * check(i, "5241", "036");
        f[i] %= mo;

        g[i] = f[i + 1] * check(i, "20", "1")
            + f[i + 2] * check(i, "30", "12")
            + f[i + 4] * check(i, "5230", "14")
            + f[i + 5] * check(i, "630", "1425");
        g[i] %= mo;
    }
    // end with 2
    auto ans = f[1] * check(1, "10");
    // end with 3
    ans += f[2] * check(1, "201")
        + f[4] * check(1, "41203")
        + f[5] * check(1, "520314");
    // end with 4
    ans += f[3] * check(1, "3012")
        + f[5] * check(1, "523014")
        + f[6] * check(1, "6301425")
        + g[4] * check(1, "30214")
        + g[5] * check(1, "413025");
    ans %= mo;
    std::cout << ans << "\n";
}

