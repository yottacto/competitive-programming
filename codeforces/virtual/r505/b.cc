// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <set>

int n;
using pair = std::pair<int, int>;
std::vector<pair> da;

int gcd(int a, int b)
{
    return !b ? a : gcd(b, a % b);
}

void insert(std::set<int>& s, int a)
{
    if (a == 1) return;
    s.insert(a);
}

auto shrink(std::set<int> const& s)
{
    std::set<int> res;
    for (auto it = s.begin(); it != s.end(); ++it) {
        auto ins = true;
        for (auto it2 = std::next(it); it2 != s.end(); ++it2)
            if (*it2 % *it == 0) {
                ins = false;
                break;
            }
        if (ins)
            res.insert(*it);
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    da.reserve(n);
    for (auto i = 0; i < n; i++) {
        int a, b;
        std::cin >> a >> b;
        da.emplace_back(a, b);
    }
    std::set<int> ans;
    insert(ans, da[0].first);
    insert(ans, da[0].second);
    for (auto i = 1; i < n; i++) {
        std::set<int> tmp;
        for (auto j : ans) {
            insert(tmp, gcd(da[i].first, j));
            insert(tmp, gcd(da[i].second, j));
        }
        ans = shrink(tmp);
    }
    if (ans.empty())
        std::cout << "-1\n";
    else
        std::cout << *ans.begin() << "\n";
}

