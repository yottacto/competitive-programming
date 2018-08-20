// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <string>

int n;
std::string s;

auto suffix(std::string const& s)
{
    auto res = 1;
    for (auto i = (int)s.size() - 2; i >= 0; i--, res++) {
        if (s[i] == s[i + 1])
            return res;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> s;
    n = s.size();
    auto now = suffix(s);
    auto ans = now;
    s = s[n - 1] + s;
    for (auto i = 1; i <= n; i++) {
        if (s[i] != s[i - 1])
            ans = std::max(ans, ++now);
        else
            now = 1;
    }
    std::cout << std::min(ans, n) << "\n";
}

