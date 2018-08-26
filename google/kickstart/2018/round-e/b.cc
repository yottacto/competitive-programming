// ml:run = $bin < input
// ml:run = $bin < B-small-attempt1.in > b-small-1.out
// ml:run = $bin < B-small-attempt0.in > b-small-0.out
#include <iostream>
#include <iterator>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <string>
#include <set>

auto constexpr maxn = 20;
int a[maxn];
std::set<int> forb;
int n, m, p;

auto trans(std::string s, int p)
{
    auto res = 0;
    for (auto i = 0; i < p; i++)
        if (s[i] == '1')
            res += 1<<i;
    return res;
}

auto calc(int way)
{
    auto res = 0;
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < p; j++) {
            auto l = a[i] & (1<<j);
            auto r = way & (1<<j);
            if (l != r)
                res++;
        }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n >> m >> p;
        for (auto i = 0; i < n; i++) {
            std::string s;
            std::cin >> s;
            a[i] = trans(s, p);
        }
        forb.clear();
        for (auto i = 0; i < m; i++) {
            std::string s;
            std::cin >> s;
            forb.insert(trans(s, p));
        }
        auto ans = n * p;
        for (auto i = 0; i < (1<<p); i++) {
            if (forb.count(i))
                continue;
            ans = std::min(ans, calc(i));
        }
        std::cout << ans << "\n";
    }
}

