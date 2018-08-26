// ml:run = $bin < input
// ml:run = $bin < B-small-attempt0.in > bb-small-0.out
// ml:run = $bin < B-large.in > b-large.out
#include <iostream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <string>
#include <map>

using pair = std::pair<int, int>;

auto constexpr maxn = 200;
std::string a[maxn];
int value[maxn];
pair pp[maxn];
int n, m, p;

auto calc(std::string const& s)
{
    auto res = 0;
    for (auto i = 1; i <= n; i++) {
        for (auto j = 0; j < p; j++)
            if (s[j] != a[i][j])
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
        for (auto i = 1; i <= n; i++)
            std::cin >> a[i];

        for (auto i = 1; i <= m; i++) {
            std::string s;
            std::cin >> s;
            value[i] = calc(s);
        }

        for (auto i = 0; i < p; i++) {
            pp[i].first = pp[i].second = 0;
            for (auto j = 1; j <= n; j++) {
                if (a[j][i] == '1')
                    pp[i].second++;
                else
                    pp[i].first++;
            }
        }

        std::vector<int> v{0};
        for (auto i = 0; i < p; i++) {
            std::vector<int> vv;
            vv.reserve(2 * m);
            for (auto& j : v) {
                vv.emplace_back(j + pp[i].first);
                vv.emplace_back(j + pp[i].second);
            }
            std::sort(vv.begin(), vv.end());
            if ((int)vv.size() >= 2 * m)
                vv.resize(2 * m);
            v = vv;
        }

        std::map<int, int> ans;
        for (auto i : v)
            ans[i]++;
        for (auto i = 1; i <= m; i++)
            if (ans.count(value[i]))
                ans[value[i]]--;

        for (auto const& p : ans) {
            if (p.second > 0) {
                std::cout << p.first << "\n";
                break;
            }
        }
    }
}

