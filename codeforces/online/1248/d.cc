// ml:run = $bin < input
#include <bits/stdc++.h>

auto constexpr maxn = 300007;
std::string s;
int n;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n;
    std::cin >> s;
    auto min = n;
    int p;
    auto sum = 0;
    for (auto i = 0; i < n; i++) {
        sum += (s[i] == '(') ? 1 : -1;
        if (sum < min) {
            min = sum;
            p = i;
        }
    }
    std::rotate(s.begin(), s.begin() + p + 1, s.end());
    std::cout << s << "\n";
}

