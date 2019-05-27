// ml:run = $bin < input
// ml:std = c++14
#include <iostream>
#include <string>

auto constexpr maxl = 500;
using ll = long long;

int n, m;
std::string s;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> s;
    n = s.size();
    ll sum = 0;
    int minr = -1;
    int minl = -1;
    for (auto i = 0; i < n; i++) {
        if (minr != -1 && i > minl) {
            minr = minl = -1;
        }
        if (minr == -1) {
            for (auto j = i + 2; j <= std::min(n - 1, i + maxl); j++) {
                for (auto d = 1; j - 2 * d >= i; d++) {
                    if (s[j] == s[j - d] && s[j] == s[j - 2 * d]) {
                        minr = j;
                        minl = j - 2 * d;
                        break;
                    }
                }
                if (minr != -1)
                    break;
            }
        }
        // std::cout << i << " " << minl << " " << minr << "\n";
        if (minr != -1)
            sum += n - minr;
    }
    std::cout << sum << "\n";
}

